/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:26:29 by descamil          #+#    #+#             */
/*   Updated: 2024/02/25 12:21:09 by descamil         ###   ########.fr       */
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

	char	*output;

	char	*route;
	char	*input;
	char	*command;
	char	*path_comm;

	char	**path;
	char	**entire_comm;
}			t_names;

size_t	ft_strlen(const char *s);

int		ft_strrchr(const char *s, int c);
int		ft_strnstr(const char *s1, const char *s2, size_t len);

char	*ft_validate_comm(t_names *names);
char	*ft_strjoin(char const *s1, char const *s2);

char	**ft_create_path(char **envp);
char	**ft_split(const char *s, char c);

void	ft_error(char *str, int i);
void	ft_setnames(t_names *names, char **argv);

void	*ft_memset(void *s, char c, size_t n, int i);

#endif