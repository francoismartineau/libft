/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swrite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:44:39 by francoma          #+#    #+#             */
/*   Updated: 2023/03/06 18:03:39 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_sprintf.h"

int	swrite_sign(char **dst, t_aconsumer *ac)
{
	int	res;

	res = 0;
	if (!is_signed_int(ac->type))
		return (res);
	if (ac->is_negative_number)
		res = swrite_char(dst, '-');
	else if (ac->flags[f_plus])
		res = swrite_char(dst, '+');
	else if (ac->flags[f_space])
		res = swrite_char(dst, ' ');
	return (res);
}

int	swrite_hex_prefix(char **dst, t_aconsumer *ac, size_t n)
{
	char	prefix[2];
	int		res;

	res = 0;
	if (((is_hex(ac->type) || is_bin(ac->type)) && ac->flags[f_hash])
		|| (ac->type == 'p' && n != 0))
	{
		prefix[0] = '0';
		if (ac->type == 'p')
			prefix[1] = 'x';
		else
			prefix[1] = ac->type;
		res = swritestrn(dst, prefix, 2);
	}
	return (res);
}

int	swrite_numbern(char **dst, t_num_properties *num)
{
	char	*digits;
	char	dgt;
	int		i;
	int		dgt_count;
	int		err;

	err = 0;
	dgt_count = count_digits(num->num, num->base);
	i = num->num_n;
	while (--i >= dgt_count && err != -1)
		err = swrite_char(dst, '0');
	digits = DIGITS;
	while (i >= 0 && err != -1)
	{
		dgt = digits[num->num / ft_pow_st(num->base, i) % num->base];
		if (ft_isupper(num->type))
			dgt = ft_toupper(dgt);
		err = swrite_char(dst, dgt);
		i--;
	}
	if (err == -1)
		return (-1);
	return (num->num_n);
}

int	swritestrn(char **dst, char *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (swrite_char(dst, s[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (n);
}

int	swritepadn(char **dst, char pad, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (swrite_char(dst, pad) == ERROR)
			return (ERROR);
		i++;
	}
	return (n);
}
