/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:15:48 by descamil          #+#    #+#             */
/*   Updated: 2024/02/24 16:50:25 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "get_next_line.h"

typedef struct s_names
{
	pid_t	*proc;

	int		fd;
	int		num;
	int		argc;
	int		index;
	int		value;
	int		fd_tmp;
	int		num_comm;
	int		comm_midd;
	int		fd_infile;
	int		fd_outfile;

	int		fd_pipe[2];

	void	*output;

	char	*route;
	char	*input;
	char	*limiter;
	char	*command;
	char	*path_comm;

	char	**argv;
	char	**envp;
	char	**path;
	char	**entire_comm;
}			t_names;

int		ft_strlen_b(const char *s);
int		ft_strchr_bonus(const char *s, int c);
int		ft_strrchr_bonus(const char *s, int c);
int		ft_strnstr(const char *s1, const char *s2, size_t len);

void	ft_here_doc(t_names *names);
void	ft_last_comm(t_names *names);
void	ft_midd_comm(t_names *names);
void	ft_first_comm(t_names *names);
void	ft_error_bonus(char *str, int i);
void	ft_execute_bonus(t_names *names, char *argv);
void	ft_setvalues(t_names *names, char **argv, char **envp, int argc);

char	*ft_validate_comm_bonus(t_names *names, int i);
char	*ft_strjoin_bonus(char const *s1, char const *s2);

char	**ft_create_path_bonus(t_names *names);
char	**ft_split_bonus(const char *s, char c);

#endif