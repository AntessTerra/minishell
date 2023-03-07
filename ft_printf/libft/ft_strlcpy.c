/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:19 by jbartosi          #+#    #+#             */
/*   Updated: 2022/10/19 12:36:02 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char		*d;
	char		*e;
	const char	*s;

	d = dest;
	e = dest + size;
	s = src;
	if (size > ft_strlen(src))
		ft_memcpy(dest, src, ft_strlen(src) + 1);
	while (*s != '\0' && d < e)
		*d++ = *s++;
	if (d < e)
		*d = 0;
	else if (size > 0)
		d[-1] = 0;
	while (*s != '\0')
		s++;
	return (s - src);
}
