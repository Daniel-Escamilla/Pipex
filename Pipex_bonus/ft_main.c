/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/16 18:43:11 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_setnames(t_names *names, char **argv)
{
	names->input = argv[1];
	if (argv[4] != NULL)
		names->output = (void *)argv[4];
}

// void	ft_child1(t_names *names, char **argv, int *fd_pipe, char **envp)
// {
	
// }

// void	ft_child2(t_names *names, char **argv, int *fd_pipe, char **envp)
// {
	
// }

// void	ft_child(t_names names, char **argv, char **envp, int *fd_pipe)
// {

// }

int	main(int argc, char **argv, char **envp)
{
	return (0);
}
