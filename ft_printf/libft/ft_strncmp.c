/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:41:10 by jbartosi          #+#    #+#             */
/*   Updated: 2022/10/20 14:56:34 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*big;
	unsigned char	*small;

	big = (unsigned char *) s1;
	small = (unsigned char *) s2;
	i = 0;
	while (i < n && ((big[i] != '\0') || (small[i] != '\0')))
	{
		if (big[i] != small[i])
			return (big[i] - small[i]);
		i++;
	}
	return (0);
}
