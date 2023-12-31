/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:32:00 by ohayek            #+#    #+#             */
/*   Updated: 2023/07/16 17:25:53 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static inline
char	*ft_check_files(char **av)
{
	int		fd1;
	int		fd2;

	fd1 = open(av[1], O_RDONLY);
	if (fd1 < 0)
		return ("Error because of the files please check them again!\n");
	if (access(av[4], F_OK) != 0)
	{
		fd2 = open(av[4], O_CREAT);
		if (fd2 < 0)
			return ("Cannot create the file :(");
		unlink(av[4]);
		return (NULL);
	}
	fd2 = open(av[4], O_WRONLY);
	if (fd2 < 0)
		return ("Error because of the files please check them again!\
 chmod 777\n");
	close(fd1);
	close(fd2);
	return (NULL);
}

static inline
char	*ft_get_path(char **ev)
{
	size_t	i;

	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp("PATH=", ev[i], 5))
			return (&ev[i][5]);
		i++;
	}
	return (NULL);
}

static inline
char	*ft_check_paths(char **paths, char *av) // av[2] av[3]
{
	char	*complete_path;
	char	*with_av;
	char	**to_check;
	size_t	i;

	i = 0;
	to_check = ft_split(av, ' ');
	while (paths[i])
	{
		complete_path = ft_strjoin(paths[i], "/");
		with_av = ft_strjoin(complete_path, to_check[0]);
		if (!access(with_av, F_OK & X_OK))
		{
			free(complete_path);
			free(with_av);
			return (NULL);
		}
		free(complete_path);
		free(with_av);
		i++;
	}
	free(to_check);
	return ("Error in your commands please check them again!\n");
}

static inline
char	*ft_check_commands(char **av, char **ev)
{
	char	*error;
	char	*path;
	char	**paths;

	path = ft_get_path(ev);
	if (!path)
	{
		ft_putstr_fd("There is no PATH var in your machine!\n", 2);
		return (NULL);
	}
	paths = ft_split(path, ':');
	error = ft_check_paths(paths, av[2]);
	if (!error)
		error = ft_check_paths(paths, av[3]);
	free(paths);
	return (error);
}

char	*ft_check_error(char **av, char **ev)
{
	char	*error;

	error = ft_check_files(av);
	if (error)
		return (error);
	error = ft_check_commands(av, ev);
	return (error);
}
