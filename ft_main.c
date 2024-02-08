/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/08 17:24:22 by descamil         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_names	names;
	int		fd;
	
	if (argc <= 4)
		ft_error("Few arguments");
	names.input = argv[1];
	names.output = argv[argc - 1];
	if (access(names.input, F_OK) == -1)
		ft_error("File error");
	if (access(names.output, F_OK) == -1)
		fd = open(names.output, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	printf("Input = %s --- Output = %s\n", names.input, names.output);
	return (0);
}
