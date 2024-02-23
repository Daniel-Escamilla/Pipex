/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/23 18:56:38 by descamil         ###   ########.fr       */
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
	names->num_comm = names->argc - 3 + 1;
	names->path = ft_create_path_bonus(names);
	names->output = names->argv[names->argc - 1];
	names->proc = malloc(names->num_comm * sizeof(int));
}

int	ft_wait_bonus(t_names *names, int i)
{
	int	state;
	
	while (names->proc[i] && i + 1 < names->index)
		waitpid(names->proc[i++], NULL, 0);
	waitpid(names->fd_outfile, &state, 0);
	return (state);
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
	int		state;
	int		i;

	i = 0;
	if (argc < 5)
		ft_error_write("Few args\n");
	// if (ft_strnstr(argv[2], "here_doc", 8) == 1)
	// 	ft_here_doc();
	ft_setvalues_bonus(&names, argv, envp, argc);
	ft_first_comm(&names);
	while (--names.num_comm > 2)
		ft_midd_comm(&names);
	ft_last_comm(&names);
	close(names.fd_pipe[0]);
	close(names.fd_pipe[1]);
	while (i < 6)
		printf("%d\n", names.proc[i++]);
	state = ft_wait_bonus(&names, 0);
	ft_free_path(&names, 0);
	return (WEXITSTATUS(state));
}

	// atexit(leaks);