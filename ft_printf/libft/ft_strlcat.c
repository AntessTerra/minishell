/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:54:53 by jbartosi          #+#    #+#             */
/*   Updated: 2022/10/20 14:35:23 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	s_len;
	size_t	rem_len;
	size_t	d_len;
	size_t	cpy_len;

	s_len = ft_strlen(src);
	if (!dest && size == 0)
		return (0);
	rem_len = size;
	while (*dest && rem_len > 0)
	{
		dest++;
		rem_len--;
	}
	d_len = size - rem_len;
	if (rem_len > 0)
	{
		cpy_len = rem_len - 1;
		if (s_len < cpy_len)
			cpy_len = s_len;
		ft_memcpy(dest, src, cpy_len);
		dest[cpy_len] = 0;
	}
	return (d_len + s_len);
}
