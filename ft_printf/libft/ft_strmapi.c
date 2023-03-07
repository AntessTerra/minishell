/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:52:40 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/14 12:52:41 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	i = 0;
	if (s == NULL || f == NULL)
		return (0);
	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, s, ft_strlen(s) + 1);
	while (result[i])
	{
		result[i] = (*f)(i, result[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
