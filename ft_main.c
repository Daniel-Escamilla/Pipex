/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/06/27 17:40:44 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_names *names, char **argv, int *fd_pipe, char **envp)
{
	int	fd;

	fd = open(names->input, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	names->entire_comm = ft_split(argv[2], ' ');
	if (names->entire_comm == NULL)
		ft_error("Bad split", 1);
	names->route = ft_validate_comm(names);
	if (fd == -1 && names->route != NULL)
		ft_error("Failed open Input", 1);
	else if (fd == -1 && names->route == NULL)
		ft_error("Command not found", 127);
	execve(names->route, names->entire_comm, envp);
}

void	ft_child2(t_names *names, char **argv, int *fd_pipe, char **envp)
{
	int	fd;

	fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(fd_pipe[0]);
		ft_error("Error open Output", 1);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	names->entire_comm = ft_split(argv[3], ' ');
	if (names->entire_comm == NULL)
		ft_error("Bad split", 1);
	names->route = ft_validate_comm(names);
	execve(names->route, names->entire_comm, envp);
}

void	ft_child(t_names *names, char **argv, char **envp, int *fd_pipe)
{
	int	fork_pid;

	fork_pid = fork();
	if (fork_pid > 0)
		names->child1 = fork_pid;
	if (fork_pid == -1)
		ft_error("Child error", 1);
	if (fork_pid == 0)
		ft_child1(names, argv, fd_pipe, envp);
	fork_pid = fork();
	if (fork_pid > 0)
		names->child2 = fork_pid;
	if (fork_pid == -1)
		ft_error("Child2 error", 1);
	if (fork_pid == 0)
		ft_child2(names, argv, fd_pipe, envp);
}

static void	ft_free_path(t_names *names, int i)
{
	while (names->path[i])
		free(names->path[i++]);
	free(names->path);
}

int	main(int argc, char **argv, char **envp)
{
	t_names	names;
	int		fd_pipe[2];
	int		status;

	if (argc != 5)
		ft_error("Few args", 1);
	ft_setnames(&names, argv);
	if (dup2(names.fd, STDOUT_FILENO) == -1)
		ft_error("Failed redirecting", 1);
	names.path = ft_create_path(envp);
	if (pipe(fd_pipe) == -1)
		ft_error("Pipe error", 1);
	ft_child(&names, argv, envp, fd_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(names.child1, NULL, 0);
	waitpid(names.child2, &status, 0);
	ft_free_path(&names, 0);
	return (WEXITSTATUS(status));
}
