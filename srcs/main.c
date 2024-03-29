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
		exit_error(list, tmp, -1);
	execve(tmp->cmd, tmp->arg, envp);
	ft_printf("%s: %s\n", tmp->arg[0], strerror(errno));
	exit_error(list, tmp, 1);
}

static int	open_childs(char **argv, char **envp, t_list **list, t_list *tmp)
{
	int	status;

	status = EXIT_SUCCESS;
	if (tmp->next && pipe((tmp->next)->pipefd) < 0)
		status = EXIT_FAILURE;
	if (tmp != *list)
		close(tmp->pipefd[1]);
	if (status == EXIT_SUCCESS)
	{
		tmp->pid = fork();
		if (tmp->pid < 0)
		{
			status = EXIT_FAILURE;
			close((tmp->next)->pipefd[0]);
			close((tmp->next)->pipefd[1]);
		}
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
	exit_code = EXIT_SUCCESS;
	while (tmp && tmp->done == 1)
	{
		waitpid(tmp->pid, &wstatus, 0);
		if (status || !WIFEXITED(wstatus) || (WIFEXITED(wstatus)
				&& WEXITSTATUS(wstatus)) || WCOREDUMP(wstatus))
		{
			if (!(WIFEXITED(wstatus) && (WEXITSTATUS(wstatus) == 1
						|| WEXITSTATUS(wstatus) == 2)) && !(!WIFEXITED(wstatus)
					&& WTERMSIG(wstatus) == 13))
				error++;
			exit_code = EXIT_FAILURE;
		}
		tmp = tmp->next;
	}
	if (error)
		write(2, "Unexpected error\n", 18);
	return (exit_code);
}

static int	parent(char **argv, char **envp, t_list **list)
{
	t_list	*tmp;
	int		status;

	tmp = *list;
	status = EXIT_SUCCESS;
	if (!ft_strcmp(argv[1], "here_doc") && here_doc(argv))
	{
		write(2, "Unexpected error\n", 17);
		return (EXIT_FAILURE);
	}
	while (tmp && status == EXIT_SUCCESS)
	{
		status = open_childs(argv, envp, list, tmp);
		tmp = tmp->next;
	}
	status = wait_for_childs(list, status);
	ft_lstfree(list);
	if (!ft_strcmp(argv[1], "here_doc") && unlink(".here_doc.tmp"))
	{
		write(2, "Unexpected error\n", 17);
		return (EXIT_FAILURE);
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*list;

	if (argc > 1 && !ft_strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
		{
			write(2, "Usage: here_doc LIMITER cmd1 cmd2 ... cmdn file2\n", 50);
			return (EXIT_FAILURE);
		}
		list = init_list(argc, argv, envp, 3);
		if (!list)
			return (write(2, "Unexpected error\n", 17), EXIT_FAILURE);
		return (parent(argv, envp, &list));
	}
	if (argc < 5)
	{
		write(2, "Usage: file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 43);
		return (EXIT_FAILURE);
	}
	list = init_list(argc, argv, envp, 2);
	if (!list)
		return (write(2, "Unexpected error\n", 17), EXIT_FAILURE);
	return (parent(argv, envp, &list));
}
