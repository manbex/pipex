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
		ft_printf("pipex: %s: %s\n", argv[1], strerror(errno));
		close(fdin);
		exit_error(list, tmp, 1);
	}
	else if (fdin < 0)
	{
		close(fdin);
		ft_lstfree(list);
		exit_error(list, tmp, 2);
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
		ft_printf("pipex: %s: %s\n", argv[i], strerror(errno));
		close(fdin);
		close(fdout);
		exit_error(list, tmp, 1);
	}
	else if (fdout < 0)
	{
		close(fdin);
		close(fdout);
		exit_error(list, tmp, 2);
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
		ft_printf("%s\n", tmp->cmd);
		ft_printf("%s: command not found\n", tmp->arg[0]);
		exit_error(list, tmp, 1);
	}
}
