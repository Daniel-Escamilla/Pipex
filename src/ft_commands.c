/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:31:58 by descamil          #+#    #+#             */
/*   Updated: 2024/12/12 11:33:59 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_error(char *str, int i)
{
	write(2, str, ft_strlen(str));
	exit(i);
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

void	ft_setnames(t_names *names, char **argv)
{
	ft_memset(names, 0, sizeof(names), 0);
	names->input = argv[1];
	names->output = argv[4];
	names->child1 = 0;
	names->child2 = 0;
}

char	**ft_create_path(char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			path = ft_split(env[i] + 5, ':');
	}
	if (path == NULL)
		*path = ft_strdup("");
	return (path);
}

char	*ft_validate_comm(t_names *names)
{
	int		j;

	j = 0;
	if (access(*names->entire_comm, X_OK) == 0
		&& ft_strrchr(*names->entire_comm, '/'))
		return (*names->entire_comm);
	if (access(*names->entire_comm, X_OK) != 0
		&& ft_strrchr(*names->entire_comm, '/'))
		ft_error("Error\n", 127);
	names->command = ft_strjoin("/", names->entire_comm[0]);
	while (names->path[j] != NULL)
	{
		names->path_comm = ft_strjoin(names->path[j++], names->command);
		if (access(names->path_comm, X_OK) == 0)
			return (names->path_comm);
		free(names->path_comm);
	}
	ft_error("Command not found", 127);
	return (NULL);
}
