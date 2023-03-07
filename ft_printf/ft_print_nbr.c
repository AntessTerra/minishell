/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:11:44 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/29 16:16:04 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	plus(t_format format)
{
	if (format.plus)
		return ('+');
	return ('-');
}

static char	*ft_uitoa(unsigned int nb)
{
	char	*str;
	int		lenght;

	lenght = ft_num_len(nb, 10);
	if (nb == 0)
		lenght = 1;
	str = (char *)malloc(lenght + 1);
	if (!str)
		return (0);
	if (nb == 0)
		str[0] = '0';
	str[lenght] = '\0';
	while (nb > 0)
	{
		str[lenght - 1] = nb % 10 + '0';
		nb /= 10;
		lenght--;
	}
	return (str);
}

static int	ft_print_nbr(t_format f, char *str, int lenght, int isneg)
{
	int	pr;

	pr = 0;
	f.width -= (f.space && !isneg && !f.plus && f.width);
	if (isneg || f.plus)
		pr += ft_putnchar_fd(plus(f), 1, f.zero && (!f.dot || f.neg_prec));
	else if (f.space)
		pr += ft_putnchar_fd(' ', 1, !f.zero);
	if (!f.minus && f.width > f.precison && (!f.dot || f.neg_prec) && f.zero)
		pr += ft_putnchar_fd('0', 1, f.width - f.precison - isneg - f.plus);
	else if (!f.minus && f.width > f.precison)
		pr += ft_putnchar_fd(' ', 1, f.width - f.precison - isneg - f.plus);
	if (isneg || f.plus)
		pr += ft_putnchar_fd(plus(f), 1, !f.zero || (f.dot && !f.neg_prec));
	pr += ft_putnchar_fd('0', 1, f.precison - lenght);
	pr += write(1, str, lenght);
	if (f.minus && f.width > f.precison)
		pr += ft_putnchar_fd(' ', 1, f.width - f.precison - isneg - f.plus);
	return (pr);
}

int	ft_format_nbr(t_format format, va_list args)
{
	char	*str;
	int		nb;
	int		isneg;
	int		printed;
	int		lenght;

	printed = 0;
	nb = va_arg(args, int);
	isneg = (nb < 0 && format.specifier != 'u');
	if (isneg)
		format.plus = 0;
	if (nb < 0 && format.specifier != 'u')
		nb = nb * -1;
	str = ft_uitoa((unsigned)nb);
	lenght = ft_strlen(str);
	if (*str == '0' && !format.precison && format.dot)
		lenght = 0;
	if (format.precison < lenght || !format.dot)
		format.precison = lenght;
	printed += ft_print_nbr(format, str, lenght, isneg);
	free(str);
	return (printed);
}
