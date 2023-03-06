/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sformat_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:27:26 by francoma          #+#    #+#             */
/*   Updated: 2023/03/06 17:21:48 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

int	sformat_str(char **dst, t_aconsumer *ac, char *s)
{
	char	padder;
	int		f_w;
	int		n;
	int		res;

	res = 0;
	if (!s)
		return (sformat_str(dst, ac, NULL_STR));
	padder = get_padder(ac);
	n = ft_strlen(s);
	if (ac->precision != -1)
		n = ft_min(n, ac->precision);
	f_w = ft_max(ac->f_w, n);
	if (ac->flags[f_minus])
		res = swritestrn(dst, s, n);
	if (res < 0)
		return (res);
	res = swritepadn(dst, padder, f_w - n);
	if (res < 0)
		return (res);
	if (!ac->flags[f_minus])
		res = swritestrn(dst, s, n);
	if (res < 0)
		return (res);
	return (f_w);
}
