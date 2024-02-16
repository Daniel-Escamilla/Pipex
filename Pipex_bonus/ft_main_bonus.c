/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/16 19:24:18 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_setnames_bonus(t_names *names, char **argv)
{
	names->input = argv[1];
	if (argv[4] != NULL)
		names->output = (void *)argv[4];
}

// void	ft_child(t_names names, char **argv, char **envp, int *fd_pipe)
// {

// }

// void	ft_child1(t_names *names, char **argv, int *fd_pipe, char **envp)
// {
	
// }

// void	ft_child2(t_names *names, char **argv, int *fd_pipe, char **envp)
// {
	
// }

// int argc, char **argv, char **envp
int	main(void)
{
	printf("PRINTEADO DESDE MAIN_BONUS\n");
	return (0);
}
