/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:00:03 by ohayek            #+#    #+#             */
/*   Updated: 2023/07/16 18:54:29 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_add_file(char *av,char **cmd1)
{
	size_t	i;
	char	**new_cmd;

	i = 0;
	while (cmd1[i])
		i++;
	new_cmd = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd1[i])
	{
		new_cmd[i] = cmd1[i];
		i++;
	}
	new_cmd[i] = ft_strdup(av);
	new_cmd[++i] = NULL;
	free(cmd1);
	return (new_cmd);
}

char	*ft_complete(char *av, char **paths)
{
	size_t	i;
	char	**splitted_av;
	char	*complete;
	char	*to_check;

	i = 0;
	splitted_av = ft_split(av, ' ');
	while (paths[i])
	{
		to_check = ft_strjoin(paths[i], "/");
		complete = ft_strjoin(to_check, splitted_av[0]);
		if (!access(complete, F_OK & X_OK))
		{
			free(to_check);
			free(splitted_av);
			return (complete);
		}
		free(to_check);
		free(complete);
		i++;
	}
	free(splitted_av);
	return (NULL);
}

char    *ft_path(char *av, char **ev)
{
    char    *path_var;
    char    **paths;
	char	*complete_path;
    size_t  i;

    i = 0;
    while (ev[i])
    {
        if (!ft_strncmp("PATH=", ev[i], 5))
        {
            path_var = &ev[i][5];
            break;
        }
        i++;
    }
    paths = ft_split(path_var, ':');
    complete_path = ft_complete(av, paths);
	return (complete_path);
}

void	ft_fork(char *path_name_1, char *path_name_2, char **cmd1, char **cmd2)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path_name_1, cmd1, NULL);
	}
	pid2 = fork();
	if (!pid2)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path_name_2, cmd2, NULL);
	}
	close(fd[1]);
	close(fd[2]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void    ft_pipe(char **av, char **ev)
{
    //execve(path_name(ok), arg("ls", "-l", NULL), {NULL}(ok))
    char    *path_name_1;
    char    *path_name_2;
	char	**cmd1;
	char	**cmd2;
	
    path_name_1 = ft_path(av[2], ev);
    path_name_2 = ft_path(av[3], ev);
	cmd1 = ft_split(av[2], ' ');
	cmd1 = ft_add_file(av[1], cmd1);
	cmd2 = ft_split(av[3], ' ');
	ft_fork(path_name_1, path_name_2, cmd1, cmd2);
}