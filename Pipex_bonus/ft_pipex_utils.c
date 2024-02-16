/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:26:16 by descamil          #+#    #+#             */
/*   Updated: 2024/02/16 18:30:58 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strnstr(const char *s1, const char *s2, size_t len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && i < len)
	{
		if (s1[i] == s2[j])
		{
			k = i;
			while (s1[k] == s2[j] && s2[j] != '\0' && (k++ < len))
			{
				if (s2[++j] == '\0')
					return (1);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((*s++) + 1 == (char)c || *s == (char)c)
			return (1);
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = -1;
	j = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = malloc(j + 1);
	j = 0;
	if (ptr == NULL)
		return (NULL);
	while ((char)s1[++i] != '\0')
		ptr[i] = (char)s1[i];
	while ((char)s2[j] != '\0')
		ptr[i++] = (char)s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
