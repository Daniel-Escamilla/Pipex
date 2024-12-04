/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:34:29 by descamil          #+#    #+#             */
/*   Updated: 2024/12/04 15:09:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_setvalues(t_names *names, char **argv, char **env, int argc)
{
	names->index = 0;
	names->argc = argc;
	names->argv = argv;
	names->env = env;
	names->path = ft_create_path_bonus(names);
	names->output = names->argv[names->argc - 1];
	names->fd_infile = 0;
	if (names->value == 'M')
	{
		names->fd = 0;
		names->comm_midd = 3;
		names->input = names->argv[1];
		names->num_comm = names->argc - 3 + 1;
		names->proc = malloc(names->num_comm * sizeof(int));
	}
	else if (names->value == 'H')
	{
		names->proc = malloc(2 * sizeof(int));
		names->limiter = argv[2];
	}
}

void	ft_first_comm(t_names *names)
{
	names->fd_infile = open(names->input, O_RDONLY);
	if (names->fd_infile == -1)
	{
		perror(names->input);
		return ;
	}
	if (pipe(names->fd_pipe) == -1)
		ft_error_bonus("Pipe error", 1);
	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (names->proc[names->index] == 0)
	{
		close(names->fd_pipe[0]);
		dup2(names->fd_infile, STDIN_FILENO);
		dup2(names->fd_pipe[1], STDOUT_FILENO);
		close(names->fd_infile);
		close(names->fd_pipe[1]);
		ft_execute_bonus(names, names->argv[2]);
	}
	names->fd_tmp = names->fd_pipe[0];
	names->index++;
	if (names->fd_infile != -1)
		close(names->fd_infile);
	close(names->fd_pipe[1]);
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
	close(names->fd_tmp);
	names->fd_tmp = names->fd_pipe[0];
	names->index++;
	names->comm_midd++;
	close(names->fd_pipe[1]);
}

void	ft_last_comm(t_names *names)
{
	int		fd;

	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (names->proc[names->index] == 0)
	{
		fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			close(names->fd_tmp);
			ft_error_bonus(names->output, 1);
		}
		dup2(names->fd_tmp, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(names->fd_tmp);
		close(fd);
		ft_execute_bonus(names, names->argv[names->argc - 2]);
	}
	names->index++;
}
