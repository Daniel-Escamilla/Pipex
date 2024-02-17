/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/17 17:17:21 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_setvalues_bonus(t_names *names, char **argv, char **envp, int argc)
{
	names->fd = 0;
	names->index = 0;
	names->argc = argc;
	names->argv = argv;
	names->envp = envp;
	names->input = names->argv[1];
	names->num_comm = names->argc - 3;
	names->path = ft_create_path_bonus(names);
	names->output = names->argv[names->argc - 1];
	names->proc = malloc(names->num_comm * sizeof(int));
}

void	ft_make_first(t_names *names)
{
	int	fd;

	fd = open(names->input, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	dup2(names->fd_pipe[1], STDOUT_FILENO);
	close(names->fd_pipe[0]);
	
	names->entire_comm = ft_split_bonus(names->argv[2], ' ');
	if (names->entire_comm == NULL)
		ft_error_bonus("Bad split");
	names->route = ft_validate_comm_bonus(names, 1);
	if (fd == -1 && names->route != NULL)
	{
		perror("Failed open input");
		exit(1);
	}
	else if (fd == -1 && names->route == NULL)
		write(2, "Command not found\n", 19);
	execve(names->route, names->entire_comm, names->envp);
}

void	ft_make_last(t_names *names)
{
	int	fd;

	fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(names->fd_pipe[0]);
		ft_error_bonus("Error open input");
	}
	dup2(fd, STDOUT_FILENO);
	dup2(names->fd_pipe[0], STDIN_FILENO);
	close(names->fd_pipe[1]);
	names->entire_comm = ft_split_bonus(names->argv[3], ' ');
	if (names->entire_comm == NULL)
		ft_error_bonus("Bad split");
	names->route = ft_validate_comm_bonus(names, 2);
	execve(names->route, names->entire_comm, names->envp);
}

// void	ft_make_midd(t_names *names)
// {
	
// }

void	ft_first_comm(t_names *names)
{
	int temp_fd;
	
	if (dup2(names->fd, STDOUT_FILENO) == -1)
		ft_error_bonus("Failed redirecting");
	if (pipe(names->fd_pipe) == -1)
		ft_error_bonus("Pipe error");
	temp_fd = fork();
	names->proc[names->index] = temp_fd;
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()");
	if (names->proc[names->index] == 0)
		ft_make_first(names);
	names->index++;
}

// void	ft_midd_comm(t_names *names)
// {
// 	while (names->num_comm > 0)
// 	{
// 		names->proc[names->index] = fork();
// 		if (names->proc[names->index] == -1)
// 			ft_error_bonus("Filed in fork()");
// 		if (names->proc[names->index] == 0)
// 			ft_make_midd(names);
// 		names->index++;
// 		names->num_comm--;
// 	}
// }

void	ft_last_comm(t_names *names)
{
	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()");
	if (names->proc[names->index] == 0)
		ft_make_last(names);
	names->index++;
}

void	ft_wait_bonus(t_names *names, int i)
{
	while (names->proc[i] && i < names->index)
		waitpid(names->proc[i++], NULL, 0);
}

void	ft_error_write(char *str)
{
	write(2, str, ft_strlen_bonus(str));
	exit(1);
}

static void	ft_free_path(t_names *names, int i)
{
	while (names->path[i])
		free(names->path[i++]);
	free(names->path);
	free(names->proc);
}

// static void leaks(void)
// {
// 	system("leaks -q pipex");
// }

int	main(int argc, char **argv, char **envp)
{
	t_names	names;

	if (argc < 5)
		ft_error_write("Few args\n");
	ft_setvalues_bonus(&names, argv, envp, argc);
	ft_first_comm(&names);
	// if (names.num_comm > 2)
	// 	ft_midd_comm(&names);
	ft_last_comm(&names);
	close(names.fd_pipe[0]);
	close(names.fd_pipe[1]);
	ft_wait_bonus(&names, 0);
	ft_free_path(&names, 0);
	// atexit(leaks);
	return (0);
}
