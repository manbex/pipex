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

	if (tmp != *list)
		close(tmp->pipefd[1]);
	if (tmp->next)
		close((tmp->next)->pipefd[0]);
	if (tmp->place == 1)
		fdin = check_infile(tmp, argv, fdin);
	else
		fdin = tmp->pipefd[0];
	if (tmp->place == 2)
		fdout = check_outfile(tmp, argv, fdin, fdout);
	else
		fdout = (tmp->next)->pipefd[1];
	cmd_error(list, tmp, fdin, fdout);
	if (dup2(fdin, 0) == -1 || dup2(fdout, 1) == -1)
		exit_error(list, tmp, fdin, fdout, 1);
	execve(tmp->cmd, tmp->arg, envp);
	printf("%s: %s\n", tmp->arg[0], strerror(errno));
	exit_error(list, tmp, fdin, fdout, -1);
}

static int	wait_childs(t_list **list)
{
	t_list	*tmp;
	int	status;

	tmp = *list;
	status = 0;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
		if (WIFEXITED(status))
			status = 1;
		else if (WEXITSTATUS(status) == -1)
			status = -1;
		else if (!status)
			status = 1;
	}
	return (status);
}

static int	open_child(char **argv, char **envp, t_list **list, t_list *tmp)
{
	int	status;

	status = 0;
	if (tmp->next)
		if (pipe((tmp->next)->pipefd))
			return (1);
	tmp->pid = fork();
	if (tmp->pid < 0)
	{
		if (tmp->next)
		{
			close((tmp->next)->pipefd[0]);
			close((tmp->next)->pipefd[1]);
		}
		status = 1;
	}
	if (tmp->pid == 0)
		child(list, tmp, argv, envp);
	if (tmp != *list)
	{
		close(tmp->pipefd[0]);
		close(tmp->pipefd[1]);
	}
	return (status);
}

static int	parent(char **argv, char **envp, t_list **list)
{
	t_list	*tmp;
	int	status;

	tmp = *list;
	status = 0;
	while (tmp && !status)
	{
		status = open_child(argv, envp, list, tmp);
		tmp = tmp->next;
	}
		status = wait_childs(list);
	if (status == 1)
		write(2, "Unexpected error\n", 17);
	if (status)
		status = EXIT_FAILURE;
	return (ft_lstfree(list), status);
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
