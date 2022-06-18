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

/*void	child(t_list *list, char **argv, char **envp)
{
}

int	parent(int argc, char **argv, char **envp)
{
	return (0);
}*/

int	main(int argc, char **argv, char **envp)
{
	t_list	*list;

	if (argc != 5)
		write(2, "Usage: file1 cmd1 cmd2 file2\n", 29);
	else
	{
		//list = init_list(argc, argv, envp, 2);
		list = NULL;
		if (!list)
			return (write(2, "Unexpected error\n", 17), 0);
		ft_lstfree(&list);
		//parent(argc, argv, envp);
	}
	return (0);
}
