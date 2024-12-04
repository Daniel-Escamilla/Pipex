/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:39:53 by sergio            #+#    #+#             */
/*   Updated: 2024/12/04 15:09:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_strdup_bonus(const char *str)
{
	size_t	len;
	char	*copy;

	len = ft_strlen_b(str);
	copy = (char *)ft_calloc(sizeof(char), len + 1);
	if (!copy)
		return (NULL);
	ft_strlcpy_bonus(copy, str, len + 1);
	return (copy);
}
