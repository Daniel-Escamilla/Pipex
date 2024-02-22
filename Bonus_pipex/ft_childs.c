/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:34:29 by descamil          #+#    #+#             */
/*   Updated: 2024/02/22 12:13:50 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_first_comm(t_names *names)
{
	int	fd;

	/* Creamos el primer pipe */
	if (pipe(names->fd_pipe) == -1)
		ft_error_bonus("Pipe error");
	
	/* Creamos children */
	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()");
	if (names->proc[names->index] == 0)
	{
		close(names->fd_pipe[0]);
		fd = open(names->input, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		dup2(names->fd_pipe[1], STDOUT_FILENO);
		close(names->fd_pipe[1]);
		close(fd);
		ft_execute_bonus(names, names->argv[2]);
	}
	close(names->fd_pipe[1]);
	names->fd_tmp = names->fd_pipe[0];
	names->index++;
}

void	ft_midd_comm(t_names *names)
{
	/* Tenemos un temporal que lo habiamos guardado despues del primer comando */
	if (pipe(names->fd_pipe) == -1)
		ft_error_bonus("Pipe Error");
	
	names->proc[names->index] = fork();
	printf("\n\tPROC->Index\t%d\n", names->proc[names->index]);
	printf("\tFD_PIPE[0] = \t%d\n\n", names->fd_pipe[0]);
	if (names->proc[names->index] == -1)
		ft_error_bonus("Failed in Fork()");
	if (names->proc[names->index] == 0)
	{
		dup2(names->fd_tmp, STDIN_FILENO);
		dup2(names->fd_pipe[1], STDOUT_FILENO);
		close(names->fd_tmp);
		close(names->fd_pipe[1]);
		close(names->fd_pipe[0]);
		ft_execute_bonus(names, names->argv[names->comm_midd]);
	}
	/* Cerramos la parte de escritura y actualizamos el temporal */
	close(names->fd_pipe[1]);
	names->fd_tmp = names->fd_pipe[0];
	names->index++;
	names->comm_midd++;
}

void	ft_last_comm(t_names *names)
{
	int		fd;
	
	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()");
	if (names->proc[names->index] == 0)
	{
		fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			close(names->fd_tmp);
			ft_error_bonus("Error open input");
		}
		dup2(names->fd_tmp, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		close(names->fd_tmp);
		ft_execute_bonus(names, names->argv[names->argc - 2]);
	}
	names->index++;
}