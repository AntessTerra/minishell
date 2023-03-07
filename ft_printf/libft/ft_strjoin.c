/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:01:52 by jbartosi          #+#    #+#             */
/*   Updated: 2022/10/27 16:01:54 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_get_lenght(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	int		i;
	int		x;

	x = 0;
	i = 0;
	out = malloc(ft_get_lenght(s1) + ft_get_lenght(s2) + 1);
	if (!out)
		return (0);
	while (s1[x] != '\0')
		out[i++] = s1[x++];
	x = 0;
	while (s2[x] != '\0')
		out[i++] = s2[x++];
	out[i] = '\0';
	return (out);
}
