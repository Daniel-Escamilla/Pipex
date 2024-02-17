/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:31:58 by descamil          #+#    #+#             */
/*   Updated: 2024/02/17 11:06:02 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error_bonus(char *str)
{
	perror(str);
	exit(1);
}

char	*ft_remove_path_bonus(char *dst, const char *src, int num, int i)
{
	while (src[num] != '\0')
		dst[i++] = src[num++];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

char	**ft_create_path_bonus(t_names *names)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (names->envp[++i] != NULL)
	{
		if (ft_strnstr_bonus(names->envp[i], "PATH=", 5))
			path = ft_split_bonus(names->envp[i], ':');
	}
	ft_remove_path_bonus(path[0], path[0], 5, 0);
	return (path);
}

char	*ft_validate_comm_bonus(t_names *names, int i)
{
	if (access(*names->entire_comm, X_OK) == 0)
		return (*names->entire_comm);
	names->command = ft_strjoin_bonus("/", names->entire_comm[0]);
	while (names->path[i] != NULL)
	{																		// Necesita una ruta "names->entire_comm" que puede contener la ruta entera o 
		names->path_comm = ft_strjoin_bonus(names->path[i++], names->command);	// puede tener solo el nombre, en ese caso se le añade una barra y ruta una a
		if (access(names->path_comm, X_OK) == 0)							// una para probar si son rutas con posibilidad de ejecución.
			return (names->path_comm);
	}
	ft_error_bonus("Command not found");
	return (NULL);
}

void	ft_execute_bonus(t_names *names)
{
	names->route = ft_validate_comm_bonus(names, 1);				// Se llamara como ft_execute(&names, argv, envp);
	names->entire_comm = ft_split_bonus(names->argv[2], ' ');
	execve(names->route, names->entire_comm, names->envp);
}