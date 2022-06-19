/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:32:40 by mbenicho          #+#    #+#             */
/*   Updated: 2022/05/17 21:32:41 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	print_s(va_list ptr)
{
	char	*str;

	str = va_arg(ptr, char *);
	if (!str)
		return (write(2, "(null)", 6));
	return (write (2, str, ft_strlen(str)));
}

int	ft_printf(char *str, ...)
{
	va_list	ptr;
	int		size;
	int		tmp;

	va_start(ptr, str);
	size = 0;
	tmp = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str == '%' && *(str + 1) == 's')
		{
			tmp = print_s(ptr);
			if (tmp < 0)
				return (-1);
			size += tmp;
			str++;
		}
		else
			size += write(2, &(*str), 1);
		str++;
	}
	va_end(ptr);
	return (size);
}
