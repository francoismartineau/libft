/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sformat_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:26:52 by francoma          #+#    #+#             */
/*   Updated: 2023/03/06 17:42:10 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

int	swrite_char(char **dst, char c)
{
	if (!dst || !*dst)
		return (ERROR);
	**dst = c;
	(*dst)++;
	return (1);
}

int	sformat_char(char **dst, t_aconsumer *ac, char c)
{
	char	padder;
	int		f_w;
	int		res;

	res = 0;
	f_w = ft_max(ac->f_w, 1);
	padder = get_padder(ac);
	if (ac->flags[f_minus])
		if (swrite_char(dst, c) == ERROR)
			return (ERROR);
	if (swritepadn(dst, padder, f_w - 1) == ERROR)
		return (ERROR);
	if (!ac->flags[f_minus])
		if (swrite_char(dst, c) == ERROR)
			return (ERROR);
	return (f_w);
}

int	sformat_percent(char **dst, t_aconsumer *ac)
{
	return (sformat_char(dst, ac, '%'));
}
