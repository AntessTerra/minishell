/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:10:19 by jbartosi          #+#    #+#             */
/*   Updated: 2022/10/21 10:39:24 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	base;

	i = 0;
	sign = 1;
	base = 0;
	if (nptr[i] == '\0')
		return (0);
	while (nptr[i] <= ' ' && nptr[i] != '\e')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		base = 10 * base + (nptr[i++] - '0');
	return (base * sign);
}
