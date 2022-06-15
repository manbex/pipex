/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:13:59 by mbenicho          #+#    #+#             */
/*   Updated: 2022/06/15 23:14:00 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parth(char **envp)
{
	char	**path;
	int	i;

	i = 0;
	while (envp[i][0] != 'P' || envp[i][1] != 'A' || envp[i][2] != 'T' ||
		envp[i][3] != 'H' || envp[i][4] != '=')
		i++;
	path = ft_split(envp[i], ':');
	path[0] = strdup(path[0] + 5);
	return (path);
}
