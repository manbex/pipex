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

# include <stdio.h>


void	ft_free_tab(char **tab);
int	ft_strlen(char *str);
char	*ft_strdup(char *s);
char	**parth(char **envp);
char	**ft_split(char const *s, char c);

#endif
