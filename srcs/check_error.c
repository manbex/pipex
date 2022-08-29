/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:57:12 by mbenicho          #+#    #+#             */
/*   Updated: 2022/07/12 14:57:14 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_infile(t_list **list, t_list *tmp, char **argv)
{
	int	fdin;

	if (!ft_strcmp(argv[1], "here_doc"))
		fdin = open(".here_doc.tmp", O_RDONLY | O_CLOEXEC);
	else
		fdin = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (fdin < 0 && (errno == 2 || errno == 13))
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), argv[1]);
		close(fdin);
		exit_error(list, tmp, 1);
	}
	else if (fdin < 0)
	{
		close(fdin);
		ft_lstfree(list);
		exit_error(list, tmp, -1);
	}
	return (fdin);
}

int	check_outfile(t_list **list, t_list *tmp, char **argv, int fdin)
{
	int	i;
	int	fdout;

	i = 0;
	while (argv[i + 1])
		i++;
	if (!ft_strcmp(argv[1], "here_doc"))
		fdout = open(argv[i], O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, 00664);
	else
		fdout = open(argv[i], O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, 00664);
	if (fdout < 0 && (errno == 2 || errno == 13))
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), argv[i]);
		close(fdin);
		close(fdout);
		exit_error(list, tmp, 1);
	}
	else if (fdout < 0)
	{
		close(fdin);
		close(fdout);
		exit_error(list, tmp, -1);
	}
	return (fdout);
}

void	exit_error(t_list **list, t_list *tmp, int error)
{
	if (tmp != *list)
		close(tmp->pipefd[0]);
	if (tmp->next)
	{
		close((tmp->next)->pipefd[0]);
		close((tmp->next)->pipefd[1]);
	}
	ft_lstfree(list);
	exit(error);
}

void	cmd_error(t_list **list, t_list *tmp)
{
	if (tmp->cmd && access(tmp->cmd, F_OK))
	{
		ft_printf("pipex: command not found: %s\n", tmp->cmd);
		exit_error(list, tmp, 1);
	}
}
