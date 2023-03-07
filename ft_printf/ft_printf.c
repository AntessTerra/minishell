/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:40:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/29 16:15:49 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_num_len(unsigned long nb, int divider)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		i++;
		nb /= divider;
	}
	return (i);
}

int	ft_print(t_format format, va_list args)
{
	unsigned long	ptr;
	int				printed;
	int				malloced;

	printed = 0;
	malloced = 0;
	if (format.specifier == 'c' || format.specifier == '%')
		return (ft_print_char(format, args));
	if (format.specifier == 's')
		return (ft_print_str(format, va_arg(args, char *), printed, malloced));
	if (format.specifier == 'd' || format.specifier == 'i'
		|| format.specifier == 'u')
		return (ft_format_nbr(format, args));
	if (format.specifier == 'x' || format.specifier == 'X')
		return (ft_print_hex(format, args));
	if (format.specifier == 'p')
	{
		ptr = va_arg(args, unsigned long);
		if (ptr)
			return (ft_print_mem(format, ptr));
		else
			return (ft_print_str(format, "(nil)", 0, 0));
	}
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	int		printed;
	va_list	args;
	char	*save;

	printed = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			save = (char *)str;
			if (*(++str))
				printed += ft_format((char *)str, args);
			while (*str && !ft_strchr(SPECIFIERS, *str))
				str++;
			if (!(*str))
				str = save;
		}
		else
			printed += ft_printchar(*str);
		if (*str)
			str++;
	}
	va_end(args);
	return (printed);
}
