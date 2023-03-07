/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:32:58 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/14 10:33:00 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			num++;
		while (s[i] != c && s[i])
			i++;
	}
	return (num);
}

static char	*ft_string(const char *s, char c)
{
	int		i;
	char	*out;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	out = malloc(i + 1);
	if (!out)
	{
		free(out);
		return (NULL);
	}
	ft_strlcpy(out, s, i + 1);
	return (out);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**out;

	len = ft_count(s, c);
	out = ft_calloc(sizeof(char *), (len + 1));
	if (!out)
		return (0);
	i = 0;
	while (i < len)
	{
		while (s[0] == c)
			s++;
		out[i] = ft_string(s, c);
		if (!out[i])
		{
			free(out);
			return (NULL);
		}
		s = s + ft_strlen(out[i]);
		i++;
	}
	out[i] = 0;
	return (out);
}
