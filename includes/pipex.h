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
# include <errno.h>
# include <stdarg.h>

# include <stdio.h>

typedef struct	s_list
{
	char	*cmd;
	char	**arg;
	int	done;
	int	pipefd[2];
	int	pid;
	struct s_list	*next;
	
} t_list;

void	ft_free_tab(char **tab);
int		ft_strlen(char *str);
char	*ft_strdup(char *s);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_lstfree(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_printf(char *str, ...);
t_list	*init_list(int argc, char **argv, char **envp, int i);
void	close_pipes(t_list **list, t_list *limit);
int		check_infile(t_list **list, t_list *tmp, char **argv);
int		check_outfile(t_list **list, t_list *tmp, char **argv, int fdin);
void	exit_error(t_list **list, t_list *tmp, int error);
void	cmd_error(t_list **list, t_list *tmp);

#endif
