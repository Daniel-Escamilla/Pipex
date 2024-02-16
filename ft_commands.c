/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:31:58 by descamil          #+#    #+#             */
/*   Updated: 2024/02/16 18:03:38 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

void	ft_setnames(t_names *names, char **argv)
{
	names->input = argv[1];
	if (argv[4] != NULL)
		names->output = (void *)argv[4];
}

char	*ft_remove_path(char *dst, const char *src, int num, int i)
{
	while (src[num] != '\0')
		dst[i++] = src[num++];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
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
			path = ft_split(envp[i], ':');
	}
	ft_remove_path(path[0], path[0], 5, 0);
	return (path);
}

char	*ft_validate_comm(t_names *names, int i)
{
	int		j;

	j = 0;
	if (i == 1)
	{
		if (access(*names->entire_comm1, X_OK) == 0)
			return (*names->entire_comm1);
		names->command = ft_strjoin("/", names->entire_comm1[0]);
	}
	else if (i == 2)
	{
		if (access(*names->entire_comm2, X_OK) == 0)
			return (*names->entire_comm2);
		names->command = ft_strjoin("/", names->entire_comm2[0]);
	}
	while (names->path[j] != NULL)
	{
		names->path_comm = ft_strjoin(names->path[j++], names->command);
		if (access(names->path_comm, X_OK) == 0)
			return (names->path_comm);
	}
	ft_error("Command not found");
	return (NULL);
}
