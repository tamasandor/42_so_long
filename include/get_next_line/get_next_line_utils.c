/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:08:59 by atamas            #+#    #+#             */
/*   Updated: 2024/01/09 23:39:19 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strlen(const char *string)
{
	int	len;

	len = 0;
	if (!string)
		return (0);
	while (string[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *string, int c, int *nline_pos)
{
	char	ch;
	int		i;

	ch = (char)c;
	i = 0;
	if (!string)
		return (NULL);
	while (*string != '\0')
	{
		if (*string == ch)
		{
			*nline_pos = i;
			return ((char *)string);
		}
		string++;
		i++;
	}
	if (ch == '\0')
		return ((char *)string);
	return (NULL);
}
