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

static char	**parth(char **envp)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i] && (envp[i][0] != 'P' || envp[i][1] != 'A' ||
		envp[i][2] != 'T' || envp[i][3] != 'H' || envp[i][4] != '='))
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i], ':');
	if (!path)
		return (NULL);
	tmp = ft_strdup(path[0] + 5);
	if (!tmp)
		return (ft_free_tab(path), NULL);
	free (path[0]);
	path[0] = tmp;
	return (path);
}

static int	is_slash(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

static int	find_path(char *cmd, char **envp, char **res)
{
	char	**path;
	char	*tmp;
	char	*str;
	int		i;

	path = parth(envp);
	if (!path)
		return (0);
	i = 0;
	if (is_slash(cmd) && !access(cmd, F_OK))
		return (ft_free_tab(path), *res = ft_strdup(cmd), 1);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!str)
			return (ft_free_tab(path), 0);
		if (!access(str, F_OK))
			return (ft_free_tab(path), *res = str, 1);
		free(str);
		i++;
	}
	return (ft_free_tab(path), *res = ft_strdup(cmd), 1);
}

t_list	*init_list(int argc, char **argv, char **envp, int i)
{
	t_list	*list;
	t_list	*new;

	list = NULL;
	while (i < argc - 1)
	{
		new = malloc(sizeof(*new));
		if (!new)
			return (ft_lstfree(&list), NULL);
		new->arg = ft_split(argv[i], ' ');
		if (!new->arg)
			return (ft_lstfree(&list), free(new), NULL);
		new->cmd = NULL;
		if (!find_path(new->arg[0], envp, &(new->cmd)))
		{
			ft_lstfree(&list);
			return (ft_free_tab(new->arg), free(new), NULL);
		}
		new->done = 0;
		new->next = NULL;
		ft_lstadd_back(&list, new);
		i++;
	}
	return (list);
}
