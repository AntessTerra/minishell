/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:03:35 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/29 15:27:05 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_format	ft_newformat(void)
{
	t_format	newformat;

	newformat.dot = 0;
	newformat.hash = 0;
	newformat.minus = 0;
	newformat.neg_prec = 0;
	newformat.plus = 0;
	newformat.precison = 0;
	newformat.space = 0;
	newformat.specifier = 0;
	newformat.width = 0;
	newformat.zero = 0;
	return (newformat);
}

static t_format	ft_format_width(char *str, va_list args, t_format format)
{
	int	done;

	done = 0;
	while (*str != '.' && !ft_strchr(SPECIFIERS, *str))
	{
		if (*str == '-')
			format.minus = 1;
		if (*str == '0' && !ft_isdigit(*(str - 1)))
			format.zero = 1;
		else if (((*str > '0' && *str <= '9') || *str == '*') && !done)
		{
			if (*str == '*')
				format.width = va_arg(args, int);
			else
				format.width = ft_atoi(str);
			done = 1;
		}
		str++;
	}
	return (format);
}

static t_format	ft_format_special(char *str, t_format format)
{
	while (*str != '.' && !ft_strchr(SPECIFIERS, *str))
	{
		if (*str == '+')
			format.plus = 1;
		if (*str == ' ')
			format.space = 1;
		if (*str == '#')
			format.hash = 1;
		str++;
	}
	return (format);
}

static t_format	ft_format_precision(char *str, va_list args, t_format format)
{
	int	done;

	done = 0;
	while (!ft_strchr(SPECIFIERS, *str))
	{
		if ((ft_isdigit(*str) || *str == '*') && !done)
		{
			if (*str == '*')
				format.precison = va_arg(args, int);
			else
				format.precison = ft_atoi(str);
			done = 1;
		}
		str++;
	}
	return (format);
}

int	ft_format(char *str, va_list args)
{
	t_format	format;

	format = ft_format_width(str, args, ft_newformat());
	format = ft_format_special(str, format);
	while (!ft_strchr(SPECIFIERS, *str) && *str != '.')
		str++;
	if (*str == '.' && !format.specifier)
	{
		format.dot = 1;
		format = ft_format_precision(str++, args, format);
		while (!ft_strchr(SPECIFIERS, *str))
			str++;
	}
	if (format.width < 0)
	{
		format.minus = 1;
		format.width *= -1;
	}
	format.specifier = *str;
	format.neg_prec = format.precison < 0;
	return (ft_print(format, args));
}
