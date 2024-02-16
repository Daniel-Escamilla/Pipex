/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:31:58 by descamil          #+#    #+#             */
/*   Updated: 2024/02/16 17:25:17 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(1);
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
	if (access(*names->entire_comm, X_OK) == 0)
		return (*names->entire_comm);
	names->command = ft_strjoin("/", names->entire_comm[0]);
	while (names->path[i] != NULL)
	{																		// Necesita una ruta "names->entire_comm" que puede contener la ruta entera o 
		names->path_comm = ft_strjoin(names->path[i++], names->command);	// puede tener solo el nombre, en ese caso se le añade una barra y ruta una a
		if (access(names->path_comm, X_OK) == 0)							// una para probar si son rutas con posibilidad de ejecución.
			return (names->path_comm);
	}
	ft_error("Command not found");
	return (NULL);
}

void	ft_execute(t_names *names, char **argv, char **envp)
{
	names->route = ft_validate_comm(names, 1);				// Se llamara como ft_execute(&names, argv, envp);
	names->entire_comm = ft_split(argv[2], ' ');
	execve(names->route, names->entire_comm, envp);
}