#include "pipex.h"

int	check_infile(t_list **list, t_list *tmp, char **argv, int fdin)
{
	fdin = open(argv[1], O_RDONLY);
	if (fdin < 0 && (errno == 2 || errno == 13))
	{
		ft_printf("pipex: %s: %s\n", argv[1], strerror(errno));
		close(fdin);
		exit_error(list, tmp, -1);
	}
	else if (fdin < 0)
	{
		close(fdin);
		ft_lstfree(list);
		exit_error(list, tmp, -2);
	}
	return (fdin);
}

int	check_outfile(t_list **list, t_list *tmp, char **argv, int fdin, int fdout)
{
	int	i;

	i = 0;
	while (argv[i + 1])
		i++;
	fdout = open(argv[i], O_CREAT|O_WRONLY|O_TRUNC, 00664);
	if (fdout < 0 && errno == 13)
	{
		ft_printf("pipex: %s: %s\n", argv[i], strerror(errno));
		close(fdin);
		close(fdout);
		exit_error(list, tmp, -1);
	}
	else if (fdout < 0)
	{
		close(fdin);
		close(fdout);
		exit_error(list, tmp, -2);
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
/*
void	cmd_error(t_list **list, t_list *tmp, int fdin, int fdout)
{
	if (access(tmp->cmd, F_OK))
	{
		ft_printf("%s: command not found\n", tmp->arg[0]);
		exit_error(list, tmp, -1);
	}
	if (access(tmp->cmd, X_OK))
	{
		ft_printf("pipex: %s: Permission denied\n", tmp->cmd);
		exit_error(list, tmp, -1);
	}
}*/
