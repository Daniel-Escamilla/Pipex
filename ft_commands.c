/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:31:58 by descamil          #+#    #+#             */
/*   Updated: 2024/08/22 10:02:52 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str, int i)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(i);
	perror(str);
}

void	ft_setnames(t_names *names, char **argv)
{
	ft_memset(names, 0, sizeof(names), 0);
	names->input = argv[1];
	names->output = argv[4];
}

char	**ft_create_path(char **envp)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (envp[++i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			path = ft_split(envp[i] + 5, ':');
	}
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
		ft_error("Error", 127);
	names->command = ft_strjoin("/", names->entire_comm[0]);
	while (names->path[j] != NULL)
	{
		names->path_comm = ft_strjoin(names->path[j++], names->command);
		if (access(names->path_comm, X_OK) == 0)
			return (names->path_comm);
	}
	ft_error("Command not found", 127);
	return (NULL);
}
