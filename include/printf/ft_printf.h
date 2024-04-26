/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:00:21 by atamas            #+#    #+#             */
/*   Updated: 2024/04/26 15:11:56 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/libft.h"

typedef struct s_parser
{
	char				flag;
	int					len;
	char				*ptr;
	char				buffer[32];
	char				upper_lower;
	unsigned int		forhexa;
	unsigned long long	forpointer;
}			t_parser;

int		ft_printf(const char *str, ...);
void	ft_printchr(t_parser *parser, char str);
void	ft_printstr(t_parser *parser, char *str);
void	ft_conversion_handler(t_parser *parser);

#endif