/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/24 09:58:19 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_setvalues(t_names *names, char **argv, char **envp, int argc)
{
	names->fd = 0;
	names->argc = argc;
	names->argv = argv;
	names->envp = envp;
	names->path = ft_create_path_bonus(names);
	names->output = names->argv[names->argc - 1];
	if (names->value == 'M')
	{
		names->index = 0;
		names->comm_midd = 3;
		names->input = names->argv[1];
		names->num_comm = names->argc - 3 + 1;
		names->proc = malloc(names->num_comm * sizeof(int));
	}
	else if (names->value == 'H')
	{
		names->proc = malloc(2 * sizeof(int));
		names->index = 0;
	}
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

void	ft_multiple(t_names *names, char **argv, char **envp, int argc)
{
	names->value = 'M';
	ft_setvalues(names, argv, envp, argc);
	ft_first_comm(names);
	while (--names->num_comm > 2)
		ft_midd_comm(names);
	ft_last_comm(names);
	close(names->fd_pipe[0]);
	close(names->fd_pipe[1]);
}

void	ft_here(t_names *names, char **argv, char **envp, int argc)
{
	if (argc < 6)
		ft_error_write("Few args for here_doc");
	names->value = 'H';
	ft_setvalues(names, argv, envp, argc);
	ft_here_doc(names);
}

int	main(int argc, char **argv, char **envp)
{
	t_names	names;
	int		state;
	int		i;

	i = 0;
	if (argc < 5)
		ft_error_write("Few args\n");
	if (ft_strnstr(argv[1], "here_doc", 8) == 1)
		ft_here(&names, argv, envp, argc);
	else
		ft_multiple(&names, argv, envp, argc);
	while (i < 2)
		printf("%d\n", names.proc[i++]);
	state = ft_wait_bonus(&names, 0);
	ft_free_path(&names, 0);
	// atexit(leaks);
	return (WEXITSTATUS(state));
}
