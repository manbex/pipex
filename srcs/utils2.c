/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:57:01 by mbenicho          #+#    #+#             */
/*   Updated: 2022/07/12 14:57:04 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int size)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < size - 1)
		i++;
	return (s1[i] - s2[i]);
}

int	here_doc(char **argv)
{
	char	*str;
	int		fd;

	fd = open(".here_doc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 1)
		return (1);
	write (1, "heredoc> ", 9);
	str = get_next_line(0);
	while (str)
	{
		if (!ft_strncmp(str, argv[2], ft_strlen(str) - 1))
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
		write (1, "heredoc> ", 9);
		str = get_next_line(0);
	}
	free(str);
	close(fd);
	return (0);
}
