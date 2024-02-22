/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/22 12:12:41 by descamil         ###   ########.fr       */
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
	names->comm_midd = 3;
	names->input = names->argv[1];
	names->num_comm = names->argc - 3;
	names->path = ft_create_path_bonus(names);
	names->output = names->argv[names->argc - 1];
	names->proc = malloc(names->num_comm * sizeof(int));
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
	printf("Set = %d\n", names.num_comm);
	ft_first_comm(&names);
	printf("FD_PIPE[0] = [%d]\n", names.fd_pipe[0]);
	printf("FD_PIPE[1] = [%d]\n\n", names.fd_pipe[1]);
	printf("FD_TEMP = [%d]\n", names.fd_tmp);
	while (names.num_comm > 2)
	{
		printf("Antes2 = %d\n", names.num_comm);
		ft_midd_comm(&names);
		printf("FD_PIPE[0] = [%d]\n", names.fd_pipe[0]);
		printf("FD_PIPE[1] = [%d]\n\n", names.fd_pipe[1]);
		names.num_comm--;
	}
	printf("Después = %d\n", names.num_comm);
	ft_last_comm(&names);
	printf("FD_PIPE[0] = [%d]\n", names.fd_pipe[0]);
	printf("FD_PIPE[1] = [%d]\n\n", names.fd_pipe[1]);
	close(names.fd_pipe[0]);
	close(names.fd_pipe[1]);
	int	i = 0;
	while (i != 4)
		printf("PROC = %d \n", names.proc[i++]);
	ft_wait_bonus(&names, 0);
	ft_free_path(&names, 0);
	// atexit(leaks);
	return (0);
}
