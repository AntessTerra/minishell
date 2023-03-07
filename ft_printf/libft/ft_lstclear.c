/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:38:56 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/16 10:38:58 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*first;

	first = *lst;
	while (first)
	{
		tmp = first->next;
		(*del)(first->content);
		free(first);
		first = tmp;
	}
	*lst = NULL;
}
