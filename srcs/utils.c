/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:21:08 by mbenicho          #+#    #+#             */
/*   Updated: 2022/06/15 23:21:11 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;

	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (free (str), NULL);
	i = 0;
	while (*s)
		str[i++] = *s++;
	str[i] = 0;
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_lstfree(t_list **lst)
{
	t_list	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free((*lst)->cmd);
			ft_free_tab((*lst)->arg);
			free(*lst);
			(*lst) = tmp;
		}
		*lst = 0;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (*lst)
	{
		list = *lst;
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else if (lst)
		*lst = new;
}
