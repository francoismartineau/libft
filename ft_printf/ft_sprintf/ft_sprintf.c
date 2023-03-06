/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:23:30 by francoma          #+#    #+#             */
/*   Updated: 2023/03/06 17:51:18 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_sprintf.h"
#include <unistd.h>

static int	is_aconsumer(char const *format)
{
	return (*format == '%' && *(format + 1));
}

static int	consume_a(char **dst, t_aconsumer *ac, va_list ap)
{
	int	count;

	if (ac->type == 'c')
		count = sformat_char(dst, ac, va_arg(ap, int));
	else if (ac->type == 's')
		count = sformat_str(dst, ac, va_arg(ap, char *));
	else if (ac->type == 'p')
		count = sformat_ptr(dst, ac, va_arg(ap, size_t));
	else if (is_signed_int(ac->type))
		count = sformat_number(dst, ac, va_arg(ap, int));
	else if (is_unsigned_int(ac->type))
		count = sformat_u_number(dst, ac, va_arg(ap, unsigned int));
	else if (ac->type == '%')
		count = sformat_percent(dst, ac);
	else
		count = 0;
	return (count);
}

static int	_ft_sprintf(char *dst, const char *format, va_list ap)
{
	t_aconsumer	ac;
	int			count;
	int			temp_count;

	count = 0;
	temp_count = 0;
	while (*format)
	{
		if (is_aconsumer(format))
		{
			format += parse_aconsumer(format, &ac);
			temp_count = consume_a(&dst, &ac, ap);
		}
		else
		{
			temp_count = swrite_char(&dst, *format);
			format += temp_count;
		}
		if (temp_count == -1)
			return (-1);
		count += temp_count;
	}
	return (count);
}

int	ft_sprintf(char *dst, const char *format, ...)
{
	va_list		ap;
	int			count;

	if (!format)
		return (0);
	va_start(ap, format);
	count = _ft_sprintf(dst, format, ap);
	va_end(ap);
	return (count);
}
