/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:31:58 by descamil          #+#    #+#             */
/*   Updated: 2024/02/12 13:07:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_remove_path(char *dst, const char *src, int num)
{
	int		i;

	i = 0;
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
		if (ft_strnstr(envp[i], "PATH", 4))
			path = ft_split(envp[i], ':');
	}
	ft_remove_path(path[0], path[0], 5);
	return (path);
}

char	*ft_validate_comm(t_names names)
{
	int		j;

	names.command = ft_strjoin("/", names.entire_comm1[0]);
	j = 0;
	while (names.path[j] != NULL)
	{
		names.path_comm = ft_strjoin(names.path[j++], names.command);
		if (access(names.path_comm, X_OK) == 0)
			return (names.path_comm);
	}
	ft_error("Command doesn't exist");
	return (NULL);
}
