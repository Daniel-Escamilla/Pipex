/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/12/04 15:42:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_child1(t_names *names, char **argv, int *fd_pipe, char **env)
{
	close(fd_pipe[0]);
	dup2(names->fd_infile, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(names->fd_infile);
	close(names->fd_outfile);
	names->entire_comm = ft_split(argv[2], ' ');
	if (names->entire_comm == NULL)
		ft_error("Bad split", 1);
	names->route = ft_validate_comm(names);
	if (names->route == NULL)
		ft_error("Command not found", 127);
	execve(names->route, names->entire_comm, env);
}

void	ft_child2(t_names *names, char **argv, int *fd_pipe, char **env)
{
	close(fd_pipe[1]);
	dup2(names->fd_outfile, STDOUT_FILENO);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	close(names->fd_infile);
	close(names->fd_outfile);
	names->entire_comm = ft_split(argv[3], ' ');
	if (names->entire_comm == NULL)
		ft_error("Bad split", 1);
	names->route = ft_validate_comm(names);
	execve(names->route, names->entire_comm, env);
}

int	ft_open_fds(t_names *names)
{
	names->fd_infile = open(names->input, O_RDONLY);
	names->fd_outfile = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (names->fd_infile == -1 && names->fd_outfile != -1)
		close (names->fd_outfile);
	if (names->fd_outfile == -1 && names->fd_infile != -1)
		close (names->fd_infile);
	if (names->fd_infile == -1)
		perror(names->input);
	if (names->fd_infile == -1)
		return (-1);
	if (names->fd_outfile == -1)
		perror(names->output);
	if (names->fd_outfile == -1)
		return (-1);
	return (0);
}

void	ft_child(t_names *names, char **argv, char **env, int *fd_pipe)
{
	int	fork_pid;

	if (ft_open_fds(names) == -1)
		return ;
	fork_pid = fork();
	if (fork_pid > 0)
		names->child1 = fork_pid;
	if (names->child1 == -1)
		ft_error("Child error", 1);
	if (names->child1 == 0)
		ft_child1(names, argv, fd_pipe, env);
	fork_pid = fork();
	if (fork_pid > 0)
		names->child2 = fork_pid;
	if (names->child2 == -1)
		ft_error("Child2 error", 1);
	if (names->child2 == 0)
		ft_child2(names, argv, fd_pipe, env);
	close(names->fd_infile);
	close(names->fd_outfile);
}

static void	ft_free_path(t_names *names, int i)
{
	while (names->path && names->path[i])
		free(names->path[i++]);
	free(names->path);
}

int	main(int argc, char **argv, char **env)
{
	t_names	names;
	int		fd_pipe[2];
	int		status;

	status = 1;
	if (argc < 5)
		ft_error("Few arguments", 1);
	if (argc > 5)
		ft_error("Too many arguments", 1);
	ft_setnames(&names, argv);
	if (dup2(names.fd, STDOUT_FILENO) == -1)
		ft_error("Failed redirecting", 1);
	names.path = ft_create_path(env);
	if (pipe(fd_pipe) == -1)
		ft_error("Pipe error", 1);
	ft_child(&names, argv, env, fd_pipe);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	if (names.fd_outfile != -1 || names.fd_infile != -1)
	{
		waitpid(names.child1, NULL, 0);
		waitpid(names.child2, &status, 0);
	}
	ft_free_path(&names, 0);
	return (WEXITSTATUS(status));
}
