/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:23:55 by francoma          #+#    #+#             */
/*   Updated: 2023/03/06 17:59:35 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

# include <stddef.h>
# include "../../libft.h"
# include "../ft_printf.h"

typedef struct s_num_properties
{
	int		num_n;
	int		pad_n;
	size_t	num;
	char	type;
	size_t	base;
}	t_num_properties;

int		swritestrn(char **dst, char *s, int n);
int		swritepadn(char **dst, char pad, int n);

int		sformat_char(char **dst, t_aconsumer *ac, char c);
int		sformat_str(char **dst, t_aconsumer *ac, char *s);
int		sformat_percent(char **dst, t_aconsumer *ac);
int		sformat_u_number(char **dst, t_aconsumer *ac, size_t n);
int		sformat_number(char **dst, t_aconsumer *ac, int d);
int		sformat_ptr(char **dst, t_aconsumer *ac, size_t ptr);

int		swrite_char(char **dst, char c);
int		swrite_sign(char **dst, t_aconsumer *ac);
int		swrite_hex_prefix(char **dst, t_aconsumer *ac, size_t n);
int		swrite_numbern(char **dst, t_num_properties *num);

#endif