/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/12 14:47:35 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	if (str == NULL)
		str = "ERROR";
	perror(str);
	exit(1);
}

void	ft_setnames(t_names names, int fd)
{
	if (access(names.input, F_OK) == -1)
		ft_error("File error"); 
	if (access(names.output, F_OK) == -1)
		fd = open(names.output, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
}

int	main(int argc, char **argv, char **envp)
{
	t_names	names;
	int		fd;
	int		i;

	i = 0;
	fd = 0;
	if (argc < 2)
		ft_error("Few arguments");
		
	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Failed to open file");
	
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error("Failed redirecting");

	names.path = ft_create_path(envp);

	names.entire_comm1 = ft_split(argv[2], ' ');
	names.route = ft_validate_comm(names);
	
	execve(names.route, names.entire_comm1, envp);

}

// while (names.path[i] != NULL)
// 	printf("PATH = %s\n", names.path[i++]);
// printf("Command = %s\n", names.command);
// printf("Path_comm = %s\n", names.path_comm);
// printf("Input = %s --- Output = %s\n", names.input, names.output);

	// if (argc <= 4)
	// 	ft_error("Few arguments");
	// names.input = argv[1];
	// names.output = argv[argc - 1];
	// names.route = ft_validate_comm(names);
	// names.entire_comm1 = ft_split(argv[2], ' ');
	// names.entire_comm2 = ft_split(argv[3], ' ');

	// FILE *file = fopen("log.txt", "w");
	// if (file)
	// {
	// 	int x = 0;
	// 	while (command[x])
	// 		fprintf(file, "- [%s]", command[x++]);
	// 	fclose(file);
	// }