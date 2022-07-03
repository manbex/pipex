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
	int	fd[2];

	if (tmp == *list)
		fdin = check_infile(list, tmp, argv);
	else
		fdin = tmp->pipefd[0];
	if (!tmp->next)
		fdout = check_outfile(list, tmp, argv, fdin);
	else
	{
		fdout = (tmp->next)->pipefd[1];
		close((tmp->next)->pipefd[0]);
	}
	cmd_error(list, tmp);
	fd[0] = dup2(fdin, 0);
	fd[1] = dup2(fdout, 1);
	close(fdin);
	close(fdout);
	if (fd[0] < 0 || fd[1] < 0)
		exit_error(list, tmp, 2);
	execve(tmp->cmd, tmp->arg, envp);
	ft_printf("%s: %s\n", tmp->arg[0], strerror(errno));
	exit_error(list, tmp, 1);
}

static int	open_childs(char **argv, char **envp, t_list **list, t_list *tmp)
{
	int	status;

	status = 0;
	if (tmp->next)
	{
		if (pipe((tmp->next)->pipefd) < 0)
			status = 1;
	}
	if (tmp != *list)
		close(tmp->pipefd[1]);
	if (status == 0)
	{
		tmp->pid = fork();
		if (tmp->pid < 0)
			status = 1;
		else if (tmp->pid == 0)
			child(list, tmp, argv, envp);
		else
			tmp->done = 1;
	}
	if (tmp != *list)
		close(tmp->pipefd[0]);
	return (status);
}

static int	wait_for_childs(t_list **list, int status)
{
	t_list	*tmp;
	int		error;
	int		exit_code;
	int		wstatus;

	tmp = *list;
	error = 0;
	exit_code = 0;
	while (tmp && tmp->done == 1)
	{
		waitpid(tmp->pid, &wstatus, 0);
		if (status || !WIFEXITED(wstatus) || (WIFEXITED(wstatus)
				&& WEXITSTATUS(wstatus)) || WCOREDUMP(wstatus))
		{
			if (!(WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 1)
				&& !(!WIFEXITED(wstatus) && WTERMSIG(wstatus) == 13))
				error++;
			exit_code = 1;
		}
		tmp = tmp->next;
	}
	if (error)
		write(2, "Unexpected error\n", 17);
	return (exit_code);
}

static int	parent(char **argv, char **envp, t_list **list)
{
	t_list	*tmp;
	int		status;
	int		exit_code;

	tmp = *list;
	status = 0;
	while (tmp && status == 0)
	{
		status = open_childs(argv, envp, list, tmp);
		tmp = tmp->next;
	}
	exit_code = wait_for_childs(list, status);
	ft_lstfree(list);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*list;

	if (argc != 5)
	{
		write(2, "Usage: file1 cmd1 cmd2 file2\n", 29);
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
