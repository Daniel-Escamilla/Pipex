/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:26:29 by descamil          #+#    #+#             */
/*   Updated: 2024/02/16 18:31:36 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_names
{
	int		fd;
	int		child1;
	int		child2;

	void	*output;

	char	*route;
	char	*input;
	char	*command;
	char	*path_comm;

	char	**path;
	char	**entire_comm;
}			t_names;

int		ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);
int		ft_strnstr(const char *s1, const char *s2, size_t len);

char	*ft_strjoin(char const *s1, char const *s2);

#endif