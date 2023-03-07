/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:36:49 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/11 11:36:50 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;
	char	*m;

	str = (char *) s;
	m = (char *) s;
	i = 0;
	while (i < n)
	{
		if (m[i] % 256 == c % 256)
			return (str);
		str++;
		i++;
	}
	return (0);
}
