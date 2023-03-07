/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:05:12 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/10 09:05:14 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = 0;
	if (c == '\0')
		return (str + ft_strlen(str));
	if (*s == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] % 256 == c % 256)
			return (str);
		str++;
		i++;
	}
	return (0);
}
