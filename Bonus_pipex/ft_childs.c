/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:34:29 by descamil          #+#    #+#             */
/*   Updated: 2024/02/23 19:15:02 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_first_comm(t_names *names)
{
	if (pipe(names->fd_pipe) == -1)
		ft_error_bonus("Pipe error", 1);
	close(names->fd_pipe[1]);
	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (names->proc[names->index] == 0)
	{
		close(names->fd_pipe[0]);
		names->fd_infile = open(names->input, O_RDONLY);
		dup2(names->fd_infile, STDIN_FILENO);
		dup2(names->fd_pipe[1], STDOUT_FILENO);
		close(names->fd_infile);
		close(names->fd_pipe[1]);
		ft_execute_bonus(names, names->argv[2]);
	}
	names->fd_tmp = names->fd_pipe[0];
	names->index++;
}

void	ft_midd_comm(t_names *names)
{
	if (pipe(names->fd_pipe) == -1)
		ft_error_bonus("Pipe Error", 1);
	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Failed in Fork()", 1);
	if (names->proc[names->index] == 0)
	{
		close(names->fd_pipe[0]);
		dup2(names->fd_tmp, STDIN_FILENO);
		dup2(names->fd_pipe[1], STDOUT_FILENO);
		close(names->fd_tmp);
		close(names->fd_pipe[1]);
		ft_execute_bonus(names, names->argv[names->comm_midd]);
	}
	names->fd_tmp = names->fd_pipe[0];
	names->index++;
	names->comm_midd++;
	close(names->fd_pipe[1]);
}

void	ft_last_comm(t_names *names)
{
	int		fd;

	names->fd_outfile = fork();
	if (names->fd_outfile == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (names->fd_outfile == 0)
	{
		fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			close(names->fd_tmp);
			ft_error_bonus("Error open input", 1);
		}
		dup2(fd, STDOUT_FILENO);
		dup2(names->fd_tmp, STDIN_FILENO);
		close(fd);
		close(names->fd_tmp);
		ft_execute_bonus(names, names->argv[names->argc - 2]);
	}
	names->index++;
}
