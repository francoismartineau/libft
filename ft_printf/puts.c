/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:44:39 by francoma          #+#    #+#             */
/*   Updated: 2023/02/09 08:04:09 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ftprintf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (s[i] && err != -1)
		err = ft_putchar(s[i++]);
	if (err == -1)
		return (-1);
	return (i);
}

int	put_sign(t_aconsumer *ac)
{
	int	res;

	res = 0;
	if (!is_signed_int(ac->type))
		return (res);
	if (ac->is_negative_number)
		res = ft_putchar('-');
	else if (ac->flags[f_plus])
		res = ft_putchar('+');
	else if (ac->flags[f_space])
		res = ft_putchar(' ');
	return (res);
}

int	put_hex_prefix(t_aconsumer *ac, size_t n)
{
	if ((!is_hex(ac->type) && ft_tolower(ac->type) != 'b')
		|| (ac->type != 'p' && !n) || (ac->type != 'p' && !ac->flags[f_hash]))
		return (0);
	return (ft_putstr("0") + ft_putstr(&ac->type));
}

int	put_numbern(size_t n, int num_n, size_t base, char type)
{
	char	*digits;
	char	dgt;
	int		i;
	int		dgt_count;
	int		err;

	err = 0;
	dgt_count = count_digits(n, base);
	i = num_n;
	while (--i >= dgt_count && err != -1)
		err = ft_putchar('0');
	digits = DIGITS;
	while (i >= 0 && err != -1)
	{
		dgt = digits[n / ft_pow_st(base, i) % base];
		if (ft_isupper(type))
			dgt = ft_toupper(dgt);
		err = ft_putchar(dgt);
		i--;
	}
	if (err == -1)
		return (-1);
	return (num_n);
}
