/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:18:26 by ohayek            #+#    #+#             */
/*   Updated: 2023/07/16 16:25:45 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **ev)
{
	char	*error_massage;
	
	if (ac == 5)
	{
		error_massage = ft_check_error(av, ev);
		ft_putstr_fd(error_massage, 2);
				
	}
	else
	{
		ft_putstr_fd("Usage: ./pipex <input_file> <cmd1> <cmd2> <output_file>\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);	
}