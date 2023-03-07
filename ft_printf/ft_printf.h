/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:40:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/01/29 16:17:49 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

# define SPECIFIERS	"cspdiuxX%"
# define HEXUP		"0123456789ABCDEF"
# define HEXDOWN	"0123456789abcdef"

typedef struct s_format
{
	int		minus;
	int		plus;
	int		width;
	int		precison;
	int		neg_prec;
	char	specifier;
	int		zero;
	int		dot;
	int		space;
	int		hash;
}				t_format;

int			ft_printf(const char *str, ...);
int			ft_putnchar_fd(char c, int fd, int nb);
int			ft_putstrn_fd(char *str, int fd, int nb);
int			ft_printchar(char c);
int			ft_format(char *str, va_list args);
int			ft_print_char(t_format format, va_list args);
int			ft_print_str(t_format f, char *str, int printed, int calloced);
int			ft_print(t_format format, va_list args);
int			ft_num_len(unsigned long nb, int divider);
int			ft_format_nbr(t_format format, va_list args);
int			ft_print_mem(t_format fr, unsigned long nb);
int			ft_print_hex(t_format fr, va_list args);
#endif
