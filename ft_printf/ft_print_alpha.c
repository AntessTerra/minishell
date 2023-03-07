/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:37:29 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/29 16:10:23 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnchar_fd(char c, int fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		write(fd, &c, 1);
		i++;
	}
	return (nb);
}

int	ft_putstrn_fd(char *str, int fd, int nb)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < nb)
		write(fd, &str[i++], 1);
	return (nb);
}

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_char(t_format format, va_list args)
{
	char	c;
	int		printed;

	printed = 0;
	if (format.specifier == 'c')
		c = va_arg(args, int);
	else
		return (ft_printchar('%'));
	format.precison = 1;
	if (!format.minus && format.zero)
		printed += ft_putnchar_fd('0', 1, format.width - format.precison);
	else if (!format.minus && format.width > format.precison)
		printed += ft_putnchar_fd(' ', 1, format.width - format.precison);
	printed += ft_printchar(c);
	if (format.minus && format.width - format.precison > 0)
		printed += ft_putnchar_fd(' ', 1, format.width - format.precison);
	return (printed);
}

int	ft_print_str(t_format f, char *str, int printed, int malloced)
{
	if (str == NULL && f.dot && f.precison == 1)
		return (ft_putnchar_fd(' ', 1, (f.width - f.precison) + 1));
	else if (str == NULL && f.precison > 0 && f.precison < 6)
		return (0);
	if (!str)
	{
		str = malloc(7);
		malloced = 1;
		ft_strlcpy(str, "(null)", 7);
	}
	if (!f.dot || f.precison > (int)ft_strlen(str) || f.precison < 0)
		f.precison = ft_strlen(str);
	if (!f.minus && f.width > f.precison && f.zero && (!f.dot || f.neg_prec))
		printed += ft_putnchar_fd('0', 1, f.width - f.precison);
	else if (!f.minus && f.width - f.precison > 0)
		printed += ft_putnchar_fd(' ', 1, f.width - f.precison);
	printed += ft_putstrn_fd(str, 1, f.precison);
	if (f.minus && f.width - f.precison > 0)
		printed += ft_putnchar_fd(' ', 1, f.width - f.precison);
	if (malloced)
		free(str);
	return (printed);
}
