/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:26:29 by descamil          #+#    #+#             */
/*   Updated: 2024/12/04 15:06:16 by descamil         ###   ########.fr       */
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
# include <stdint.h>

typedef struct s_names
{
	int		fd;
	int		child1;
	int		child2;
	int		fd_infile;
	int		fd_outfile;

	char	*output;

	char	*route;
	char	*input;
	char	*command;
	char	*path_comm;

	char	**path;
	char	**entire_comm;
}			t_names;

//ft_calloc.c
void	*ft_calloc(size_t nmemb, size_t size);

// ft_commands.c
void	ft_error(char *str, int i);
char	**ft_create_path(char **env);
char	*ft_validate_comm(t_names *names);
void	ft_setnames(t_names *names, char **argv);

// ft_memset.c
void	*ft_memset(void *s, char c, size_t n, int i);

// ft_split.c
char	**ft_split(const char *s, char c);

// ft_strdup.c
char	*ft_strdup(const char *str);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

// ft_strlcpy.c
size_t	ft_strlcpy(char *dest, const char *src, size_t len_dest);

// ft_strchr.c
size_t	ft_strlen(const char *s);
int		ft_strrchr(const char *s, int c);
int		ft_strnstr(const char *s1, const char *s2, size_t len);

#endif