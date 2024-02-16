/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/16 18:16:01 by descamil         ###   ########.fr       */
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
	names->entire_comm1 = ft_split(argv[2], ' ');
	if (names->entire_comm1 == NULL)
		ft_error("Bad split");
	names->route = ft_validate_comm(names, 1);
	if (fd == -1 && names->route != NULL)
	{
		perror("Failed open input");
		exit(1);
	}
	else if (fd == -1 && names->route == NULL)
		write (2, "Command not found\n", 19);
	execve(names->route, names->entire_comm1, envp);
}

void	ft_child2(t_names *names, char **argv, int *fd_pipe, char **envp)
{
	int	fd;

	fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(fd_pipe[0]);
		ft_error("Error open input");
	}
	dup2(fd, STDOUT_FILENO);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	names->entire_comm2 = ft_split(argv[3], ' ');
	if (names->entire_comm2 == NULL)
		ft_error("Bad split");
	names->route = ft_validate_comm(names, 2);
	execve(names->route, names->entire_comm2, envp);
}

void	ft_child(t_names names, char **argv, char **envp, int *fd_pipe)
{
	names.child1 = fork();
	if (names.child1 == -1)
		ft_error("Child error");
	if (names.child1 == 0)
		ft_child1(&names, argv, fd_pipe, envp);
	names.child2 = fork();
	if (names.child2 == -1)
		ft_error("Child2 error");
	if (names.child2 == 0)
		ft_child2(&names, argv, fd_pipe, envp);
}

static void	ft_free_path(t_names *names)
{
	int	i;

	i = 0;
	while (names->path[i])
	{
		free(names->path[i++]);
	}
	free(names->path);
}

int	main(int argc, char **argv, char **envp)
{
	t_names	names;
	int		fd;
	int		fd_pipe[2];

	fd = 0;
	if (argc != 5)
	{
		write (2, "Error\n", 6);
		return (1);
	}
	ft_setnames(&names, argv);
	if (dup2(names.fd, STDOUT_FILENO) == -1)
		ft_error("Failed redirecting");
	names.path = ft_create_path(envp);
	if (pipe(fd_pipe) == -1)
		ft_error("Pipe error");
	ft_child(names, argv, envp, fd_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(names.child1, NULL, 0);
	waitpid(names.child2, NULL, 0);
	ft_free_path(&names);
	return (0);
}
