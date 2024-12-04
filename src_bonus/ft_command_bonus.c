/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:31:58 by descamil          #+#    #+#             */
/*   Updated: 2024/12/04 15:09:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_error_bonus(char *str, int i)
{
	perror(str);
	exit(i);
}

char	**ft_create_path_bonus(t_names *names)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (names->env[++i] != NULL)
	{
		if (ft_strnstr(names->env[i], "PATH=", 5))
			path = ft_split_bonus(names->env[i] + 5, ':');
	}
	if (path == NULL)
		*path = ft_strdup_bonus("");
	return (path);
}

char	*ft_validate_comm_bonus(t_names *names, int i)
{
	if (access(*names->entire_comm, X_OK) == 0
		&& ft_strrchr_bonus(*names->entire_comm, '/'))
		return (*names->entire_comm);
	if (access(*names->entire_comm, X_OK) != 0
		&& ft_strrchr_bonus(*names->entire_comm, '/'))
		ft_error_bonus("Error", 127);
	names->command = ft_strjoin_bonus("/", names->entire_comm[0]);
	while (names->path[i] != NULL)
	{
		names->path_comm = ft_strjoin_bonus(names->path[i++], names->command);
		if (access(names->path_comm, X_OK) == 0)
			return (names->path_comm);
		free(names->path_comm);
	}
	ft_error_bonus("Command not found", 127);
	return (NULL);
}

void	ft_execute_bonus(t_names *names, char *argv)
{
	names->entire_comm = ft_split_bonus(argv, ' ');
	if (names->entire_comm == NULL)
		ft_error_bonus("Bad split", 1);
	names->route = ft_validate_comm_bonus(names, 1);
	if (names->fd_infile == -1)
	{
		names->fd_infile = 0;
		if (names->route != NULL)
			ft_error_bonus("Failed open input", 1);
		else
			write (2, "Command not found\n", 19);
	}
	execve(names->route, names->entire_comm, names->env);
}
