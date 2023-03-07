/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:46:43 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/10 09:46:44 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char		*str;
	char		*needle;

	str = (char *) big;
	needle = (char *) little;
	if ((!big || !little) && len == 0)
		return (str);
	if (*little == 0 && len == 0)
		return (str);
	if ((*big == 0 && *little == 0) && len > ft_strlen(big))
		return (str);
	while ((*str) && len > 0)
	{
		if (ft_strncmp(str, needle, ft_strlen(needle)) == 0
			&& len >= ft_strlen(needle))
			return (str);
		str++;
		len--;
	}
	return (0);
}
