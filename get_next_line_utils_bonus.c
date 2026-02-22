/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:32:54 by skhachat          #+#    #+#             */
/*   Updated: 2026/02/22 13:32:54 by skhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!newstr)
		return (NULL);
	while (str1[i])
	{
		newstr[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		newstr[i + j] = str2[j];
		j++;
	}
	newstr[i + j] = '\0';
	free(str1);
	return (newstr);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = malloc(ft_strlen(str) + 1);
	if (!cpy)
		return (NULL);
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	real_len;
	char	*ptr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	real_len = s_len - start;
	if (real_len > len)
		real_len = len;
	ptr = malloc(real_len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < real_len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
