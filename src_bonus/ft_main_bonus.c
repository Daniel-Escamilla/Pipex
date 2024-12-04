/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/12/04 15:09:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	ft_wait_bonus(t_names *names, int i)
{
	int	state;

	while (names->proc[i] && i + 1 < names->index)
		waitpid(names->proc[i++], NULL, 0);
	waitpid(names->proc[i], &state, 0);
	return (state);
}

void	ft_error_write(char *str)
{
	write(2, str, ft_strlen_b(str));
	exit(1);
}

static void	ft_free_path(t_names *names, int i)
{
	unlink(".here_doc");
	while (names->path[i])
		free(names->path[i++]);
	free(names->path);
	free(names->proc);
}

void	ft_multiple(t_names *names, char **argv, char **env, int argc)
{
	int	fd;

	names->value = 'M';
	ft_setvalues(names, argv, env, argc);
	ft_first_comm(names);
	if (names->fd_infile == -1)
	{
		fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(fd);
		return ;
	}
	while (--names->num_comm > 2)
		ft_midd_comm(names);
	ft_last_comm(names);
	close(names->fd_pipe[0]);
	close(names->fd_pipe[1]);
}

int	main(int argc, char **argv, char **env)
{
	t_names	names;
	int		state;

	state = 1;
	if (argc < 5)
		ft_error_write("Few args\n");
	if (ft_strnstr(argv[1], "here_doc", 8) == 1)
	{
		if (argc != 6)
			ft_error_write("Few args for here_doc");
		names.value = 'H';
		ft_setvalues(&names, argv, env, argc);
		ft_here_doc(&names);
	}
	else
		ft_multiple(&names, argv, env, argc);
	if (names.fd_infile != -1)
		state = ft_wait_bonus(&names, 0);
	ft_free_path(&names, 0);
	return (WEXITSTATUS(state));
}
