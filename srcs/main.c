/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:51:51 by mbenicho          #+#    #+#             */
/*   Updated: 2022/06/14 18:51:52 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(t_list **list, t_list *tmp, char **argv, char **envp)
{
	int	fdin;
	int	fdout;

	if (tmp == *list)
		fdin = check_infile(list, tmp, argv, fdin);
	else
		fdin = tmp->pipefd[0];
	if (tmp->next == NULL)
		fdout = check_outfile(list, tmp, argv, fdin, fdout);
	else
	{
		fdout = (tmp->next)->pipefd[1];
		close((tmp->next)->pipefd[0]);
	}
	dup2(fdin, 0);
	dup2(fdout, 1);
	execve(tmp->cmd, tmp->arg, envp);
}

/*static int	wait_for_childs(t_list **list)
{
	char	*tmp;

	tmp = *list;
	while (tmp)
	{
		waitpid(tmp->pid, 0, 0);
		tmp = tmp->next;
	}
}*/

static int	parent(char **argv, char **envp, t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->next)
			pipe((tmp->next)->pipefd);
		if (tmp != *list)
			close(tmp->pipefd[1]);
		tmp->pid = fork();
		if (tmp->pid == 0)
			child(list, tmp, argv, envp);
		if (tmp != *list)
			close(tmp->pipefd[0]);
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		waitpid(tmp->pid, 0, 0);
		tmp = tmp->next;
	}
	ft_lstfree(list);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*list;

	if (argc < 5)
	{
		write(2, "Usage: file1 cmd1 cmd2 ... cmdN file2\n", 38);
		return (EXIT_FAILURE);
	}
	else
	{
		list = init_list(argc, argv, envp, 2);
		if (!list)
			return (write(2, "Unexpected error\n", 17), EXIT_FAILURE);
		return (parent(argv, envp, &list));
	}
}
