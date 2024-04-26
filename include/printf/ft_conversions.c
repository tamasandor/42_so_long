/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:28:28 by atamas            #+#    #+#             */
/*   Updated: 2023/12/08 13:57:16 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_multidigit(int base, unsigned long long number)
{
	int	multidigit;

	multidigit = 0;
	if (number == 0)
		multidigit++;
	while (number > 0)
	{
		number /= base;
		multidigit++;
	}
	return (multidigit);
}

static void	ft_itoa_base(int base, unsigned long long number, t_parser *parser)
{
	int		multidigit;
	int		chr;

	multidigit = ft_multidigit(base, number);
	parser->buffer[multidigit] = '\0';
	while (multidigit > 0)
	{
		multidigit--;
		chr = number % base;
		if (chr > 9)
			chr += parser->upper_lower;
		else
			chr += '0';
		parser->buffer[multidigit] = chr;
		number /= base;
	}
}

void	ft_conversion_handler(t_parser *parser)
{
	if (parser->flag == 'x')
	{
		parser->upper_lower = 87;
		ft_itoa_base(16, parser->forhexa, parser);
	}
	if (parser->flag == 'X')
	{
		parser->upper_lower = 55;
		ft_itoa_base(16, parser->forhexa, parser);
	}
	if (parser->flag == 'u')
	{
		parser->upper_lower = '0';
		ft_itoa_base(10, parser->forhexa, parser);
	}
	if (parser->flag == 'p')
	{
		ft_printstr(parser, "0x");
		parser->upper_lower = 87;
		ft_itoa_base(16, parser->forpointer, parser);
	}
	ft_printstr(parser, parser->buffer);
}
