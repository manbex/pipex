/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:51:42 by mbenicho          #+#    #+#             */
/*   Updated: 2022/06/14 18:51:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
#include <errno.h>

# include <stdio.h>

typedef struct	s_list
{
	char	*cmd;
	char	**arg;
	int	place;
	int	pipefd[2];
	struct s_list	*next;
	
} t_list;

void	ft_free_tab(char **tab);
int	ft_strlen(char *str);
char	*ft_strdup(char *s);
int	ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_lstfree(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*init_list(int argc, char **argv, char **envp, int i);

#endif
