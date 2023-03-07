/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:57:09 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/11 11:57:10 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	needed;
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	needed = nmemb * size;
	if (needed / nmemb != size)
		return (NULL);
	ptr = malloc(needed);
	if (!ptr)
		return (ptr);
	ft_memset(ptr, 0, needed);
	return (ptr);
}
