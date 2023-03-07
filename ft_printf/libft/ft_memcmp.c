/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:28:41 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/11 11:28:42 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*h;
	const unsigned char		*k;

	h = (const unsigned char *) s1;
	k = (const unsigned char *) s2;
	while (n > 0)
	{
		if (*h != *k)
			return (*h - *k);
		n--;
		h++;
		k++;
	}
	return (0);
}
