/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aconsumer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:44:43 by francoma          #+#    #+#             */
/*   Updated: 2023/03/06 16:23:00 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_aconsumer(t_aconsumer *ac)
{
	size_t	n;
	size_t	i;

	n = ft_strlen(FLAGS);
	i = 0;
	while (i < n)
		ac->flags[i++] = 0;
	ac->f_w = 0;
	ac->precision = -1;
	ac->type = -1;
	ac->is_negative_number = 0;
}

size_t	parse_aconsumer(const char *s, t_aconsumer *ac)
{
	int		nth_flag;
	size_t	i;

	init_aconsumer(ac);
	i = 1;
	while (1)
	{
		nth_flag = nth_in_str(s[i], FLAGS);
		if (nth_flag == -1)
			break ;
		ac->flags[nth_flag] = 1;
		i++;
	}
	ac->f_w = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '.')
	{
		ac->precision = ft_atoi(&s[++i]);
		while (ft_isdigit(s[i]))
			i++;
	}
	if (in_str(s[i], TYPES))
		ac->type = s[i];
	return (i + 1);
}

char	get_padder(t_aconsumer *ac)
{
	if (ac->flags[f_zero] && !ac->flags[f_minus]
		&& (!is_int(ac->type) || ac->precision == -1))
		return ('0');
	return (' ');
}

int	get_base(t_aconsumer *ac)
{
	if (is_hex(ac->type))
		return (16);
	else if (ft_tolower(ac->type) == 'b')
		return (2);
	else
		return (10);
}
