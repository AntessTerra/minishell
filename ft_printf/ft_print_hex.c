/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:40:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/30 11:40:59 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*hash(t_format format)
{
	if (format.specifier == 'X')
		return ("0X");
	return ("0x");
}

static int	ft_hex(t_format format, unsigned long nb, unsigned long done)
{
	int		printed;
	int		digit;
	char	c;

	printed = 0;
	if (nb > 0 || (!done && (format.specifier != 'p' || !format.dot)))
	{
		digit = nb % 16;
		if (format.specifier == 'X')
			c = HEXUP[digit];
		else
			c = HEXDOWN[digit];
		nb /= 16;
		done = 1;
		printed += ft_hex(format, nb, done);
		printed += ft_printchar(c);
	}
	return (printed);
}

int	ft_print_hex(t_format f, va_list args)
{
	int				printed;
	int				lenght;
	unsigned int	nb;

	printed = 0;
	nb = va_arg(args, unsigned int);
	lenght = ft_num_len(nb, 16);
	if (!nb && !f.precison && f.dot)
		lenght = 0;
	if (f.precison < 0 || f.precison < lenght || !f.dot)
		f.precison = lenght;
	if (f.hash && nb)
		f.width -= 2;
	printed += ft_putstrn_fd(hash(f), 1, 2 * (f.hash && f.zero && nb));
	if (!f.minus && f.width > f.precison && (!f.dot || f.neg_prec) && f.zero)
		printed += ft_putnchar_fd('0', 1, (f.width - f.precison));
	else if (!f.minus && f.width > f.precison)
		printed += ft_putnchar_fd(' ', 1, (f.width - f.precison));
	printed += ft_putstrn_fd(hash(f), 1, 2 * (f.hash && !f.zero && nb));
	printed += ft_putnchar_fd('0', 1, (f.precison - lenght));
	if (lenght)
		printed += ft_hex(f, nb, nb);
	if (f.minus && f.width > f.precison)
		printed += ft_putnchar_fd(' ', 1, f.width - f.precison);
	return (printed);
}

int	ft_print_mem(t_format fr, unsigned long nb)
{
	int		printed;
	int		lenght;

	printed = 0;
	lenght = ft_num_len(nb, 16);
	lenght *= !(!nb && !fr.precison && fr.dot);
	if (fr.precison < lenght || !fr.dot)
		fr.precison = lenght;
	printed += write(1, "0x", 2 * fr.zero);
	fr.width -= 2;
	if (!fr.minus && fr.width > fr.precison && !fr.dot && fr.zero)
		printed += ft_putnchar_fd('0', 1, (fr.width - fr.precison));
	else if (!fr.minus && fr.width > fr.precison)
		printed += ft_putnchar_fd(' ', 1, (fr.width - fr.precison));
	printed += write(1, "0x", 2 * !fr.zero);
	printed += ft_putnchar_fd('0', 1, (fr.precison - lenght) * (nb != 0));
	printed += ft_putnchar_fd('0', 1, fr.precison * (fr.dot && !nb));
	if (lenght)
		printed += ft_hex(fr, nb, nb);
	if (fr.minus && fr.width > fr.precison)
		printed += ft_putnchar_fd(' ', 1, fr.width - fr.precison);
	return (printed);
}
