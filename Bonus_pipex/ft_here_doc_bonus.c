/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:21:42 by descamil          #+#    #+#             */
/*   Updated: 2024/02/24 12:09:58 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_child1(t_names *names, int fd_tmp)
{
	if (pipe(names->fd_pipe) == -1)
		ft_error_bonus("Pipe error", 1);
	close(names->fd_pipe[1]);
	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (names->proc[names->index] == 0)
	{
		close(names->fd_pipe[0]);
		dup2(fd_tmp, STDIN_FILENO);
		dup2(names->fd_pipe[1], STDOUT_FILENO);
		close(fd_tmp);
		close(names->fd_pipe[1]);
		ft_execute_bonus(names, names->argv[3]);
	}
	printf("1º TMP = %d\n", fd_tmp);
	printf("2º [0]%d\n", names->fd_pipe[0]);
	printf("3º [1]%d\n", names->fd_pipe[1]);
	names->index++;
}

void	ft_child2(t_names *names)
{
	int		fd;

	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (names->proc[names->index] == 0)
	{
		fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			close(names->fd_pipe[0]);
			ft_error_bonus("Error open input", 1);
		}
		dup2(names->fd_pipe[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(names->fd_pipe[0]);
		close(fd);
		ft_execute_bonus(names, names->argv[4]);
	}
	printf("1º [0]%d\n", names->fd_pipe[0]);
	printf("2º [1]%d\n", names->fd_pipe[1]);
}

void	ft_here_doc(t_names *names)
{
	char	*line;
	int		fd_tmp;

	printf("%s\n", names->limiter);
	
	fd_tmp = open(names->fd_infile, O_WRONLY | O_CREAT, 0644);
	// fd_tmp = open(".here_doc", O_WRONLY | O_CREAT, 0644);
	// if (fd_tmp == -1)
	// 	ft_error_bonus("Error open", 1);
	// while (1)
	// {
	// 	line = get_next_line(0);
	// 	if (ft_strnstr(line, names->limiter, ft_strlen_b(names->limiter)) == 1)
	// 		break ;
	// 	if (write(fd_tmp, line, ft_strlen_b(line)) == -1)
	// 		ft_error_bonus("Error write", 1);
	// }
	ft_child1(names, fd_tmp);
	ft_child2(names);
}
