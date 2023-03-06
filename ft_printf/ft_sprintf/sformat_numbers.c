/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sformat_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:51:44 by francoma          #+#    #+#             */
/*   Updated: 2023/03/06 18:17:20 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

static int	_display_number(char **dst, t_aconsumer *ac, t_num_properties *num)
{
	char	padder;

	padder = get_padder(ac);
	num->base = get_base(ac);
	if (!ac->flags[f_minus] && padder == ' ')
		if (swritepadn(dst, padder, num->pad_n) == ERROR)
			return (ERROR);
	if (swrite_sign(dst, ac) == ERROR)
		return (ERROR);
	if (swrite_hex_prefix(dst, ac, num->num) == ERROR)
		return (ERROR);
	if (!ac->flags[f_minus] && padder == '0')
		if (swritepadn(dst, padder, num->pad_n) == ERROR)
			return (ERROR);
	if (num->num || ac->precision)
		if (swrite_numbern(dst, num)
			== ERROR)
			return (ERROR);
	if (ac->flags[f_minus])
		if (swritepadn(dst, padder, num->pad_n) == ERROR)
			return (ERROR);
	return (0);
}

int	sformat_u_number(char **dst, t_aconsumer *ac, size_t n)
{
	char				prefix_n;
	int					num_n;
	int					count;
	t_num_properties	num_prop;

	prefix_n = 2 * (ac->type == 'p' || (ac->flags[f_hash] && n));
	num_n = ft_max(count_digits(n, get_base(ac)), ac->precision);
	num_n -= (!n && !ac->precision);
	count = ft_max(ac->f_w, prefix_n + num_n);
	num_prop = (t_num_properties){.num = n, .num_n = num_n,
		.pad_n = count - prefix_n - num_n};
	if (_display_number(dst, ac, &num_prop)
		== ERROR)
		return (ERROR);
	return (count);
}

int	sformat_number(char **dst, t_aconsumer *ac, int n)
{
	int					sign;
	int					count;
	int					num_n;
	t_num_properties	num_prop;

	sign = 0;
	if (n < 0)
		ac->is_negative_number = 1;
	if (n < 0 || ac->flags[f_plus] || ac->flags[f_space])
		sign = 1;
	num_n = ft_max(count_digits(ft_abs_st(n), get_base(ac)), ac->precision);
	num_n -= (!n && !ac->precision);
	count = ft_max(ac->f_w, sign + num_n);
	num_prop = (t_num_properties){.num = ft_abs_st(n), .num_n = num_n,
		.pad_n = count - sign - num_n};
	if (_display_number(dst, ac, &num_prop)
		== ERROR)
		return (ERROR);
	return (count);
}

int	sformat_ptr(char **dst, t_aconsumer *ac, size_t ptr)
{
	int					count;
	int					num_n;
	t_num_properties	num_prop;

	num_n = count_digits(ptr, 16);
	count = ft_max(ac->f_w, 2 + num_n);
	num_prop = (t_num_properties){.num = ptr, .num_n = num_n,
		.pad_n = count - 2 - num_n};
	if (_display_number(dst, ac, &num_prop) == ERROR)
		return (ERROR);
	return (count);
}
