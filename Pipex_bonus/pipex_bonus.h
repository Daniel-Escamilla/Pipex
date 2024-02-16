/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:15:48 by descamil          #+#    #+#             */
/*   Updated: 2024/02/16 19:20:48 by descamil         ###   ########.fr       */
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

int		ft_strlen_bonus(const char *s);
int		ft_strchr_bonus(const char *s, int c);
int		ft_strnstr_bonus(const char *s1, const char *s2, int len);

char	*ft_strjoin_bonus(char const *s1, char const *s2);

char	**ft_split_bonus(const char *s, char c);

#endif