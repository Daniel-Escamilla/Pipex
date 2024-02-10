/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:32:22 by descamil          #+#    #+#             */
/*   Updated: 2024/02/10 17:38:36 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(t_names names, char **argv, char **envp)
{
	pid_t	child;
	int		current[2];
	int		prev[2];
	int		error;
	int		fd;
	int		i;
	int		k;
	
	k = 0;
	i = 2;
	error = 0;
	names.path = ft_create_path(envp);
	fd = open(names.input, O_RDONLY);
	if (fd == -1)
		ft_error("Error while read infile");
	while (names.num_comm > 0)
	{
		printf ("NUM = [%d]\n", names. num_comm);
		if (names.num_comm > 1)
		{
			if (pipe(current) == -1)
				ft_error("Error pipe");
		}
		child = fork();
		if (child == -1)
			ft_error("Failed trying making child");
		if (child == 0)
		{
			printf("Child = 0\n");
			if (names.num_comm > 1)
			{
				close(current[0]);
				dup2(current[1], 1);
				close(current[1]);
			}
			dup2(fd, 0);
			names.entire_comm = ft_split(argv[i--], ' ');
			names.route = ft_validate_comm(names);
			while (names.entire_comm[k] != NULL)
				printf("Entire = [%s]\n", names.entire_comm[k++]);
			printf("Route = [%s]\n", names.route);
			if (names.route == NULL)
				ft_error("Filed to create route");
			if (execve(names.route, names.entire_comm, envp) == -1)
				ft_error("Failed to execute command");
		}
		else
		{
			printf("Father\n");
			if (names.num_comm > 1)
				close(current[1]);
			waitpid(child, NULL, 0);
			if (names.num_comm > 1)
			{
				prev[0] = current[0];
				prev[1] = current[1];
			}
			names.num_comm--;
		}
		i++;
	}
	close (fd);
	close (prev[0]);
	close (prev[1]);
}
