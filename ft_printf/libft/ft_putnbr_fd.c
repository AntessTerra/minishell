/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:24:30 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/13 10:24:32 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	handle_negative(int *n, int *var, int fd)
{
	if (*n == 0)
		write(fd, "0", 1);
	else if (*n >= -2147483647)
	{
		write(fd, "-", 1);
		*n = *n * -1;
	}
	else
	{
		write(fd, "-", 1);
		*n = *n + 1;
		*n = *n * -1;
		*var = 1;
	}
}

static void	more_itoa(int n, int *var, int fd)
{
	char	c;

	while (var[1] > 0)
	{
		if ((n / var[1]) > 0 || var[0])
		{
			var[0] = 1;
			c = (n / var[1]) + '0';
			write(fd, &c, 1);
			n = n - ((n / var[1]) * var[1]);
		}
		if (var[2])
		{
			var[2] = 0;
			n = n + 1;
		}
		var[1] = var[1] / 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		var[3];

	var[0] = 0;
	var[2] = 0;
	if (n <= 0)
		handle_negative(&n, &var[2], fd);
	var[1] = 1000000000;
	return (more_itoa(n, var, fd));
}
