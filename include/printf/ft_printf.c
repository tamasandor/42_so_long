/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:58:49 by atamas            #+#    #+#             */
/*   Updated: 2024/04/26 14:54:30 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

void	ft_operation(t_parser *parser, va_list args)
{
	if (parser->flag == '%')
		ft_printchr(parser, '%');
	if (parser->flag == 'c')
		ft_printchr(parser, va_arg(args, int));
	if (parser->flag == 's')
		ft_printstr(parser, va_arg(args, char *));
	if (parser->flag == 'd' || parser->flag == 'i')
	{
		parser->ptr = ft_itoa(va_arg(args, int));
		ft_printstr(parser, parser->ptr);
		free(parser->ptr);
	}
	if (parser->flag == 'x' || parser->flag == 'X' || parser->flag == 'u')
	{
		parser->forhexa = va_arg(args, unsigned int);
		ft_conversion_handler(parser);
	}
	if (parser->flag == 'p')
	{
		parser->forpointer = va_arg(args, unsigned long long);
		ft_conversion_handler(parser);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list		argument;
	t_parser	parser;

	parser.len = 0;
	va_start(argument, str);
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == '%')
		{
			parser.flag = *(++str);
			ft_operation(&parser, argument);
		}
		else
			ft_printchr(&parser, *str);
		str++;
	}
	va_end(argument);
	return (parser.len);
}

/* int	main(void)
{
	ft_printf(" %%");
} */
