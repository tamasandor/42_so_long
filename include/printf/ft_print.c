/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:32:10 by atamas            #+#    #+#             */
/*   Updated: 2024/04/26 23:42:28 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	ft_buffer_zero(t_parser *parser)
{
	int	i;

	i = 32;
	while (i > 0)
		parser->buffer[i--] = '\0';
}

void	ft_printchr(t_parser *parser, char chr)
{
	parser->len += write(1, &chr, 1);
}

void	ft_printstr(t_parser *parser, char *str)
{
	if (!str)
	{
		parser->len += write(1, "(null)", 6);
	}
	else
	{
		while (*str)
		{
			ft_printchr(parser, *str);
			str++;
		}
		ft_buffer_zero(parser);
	}
}
