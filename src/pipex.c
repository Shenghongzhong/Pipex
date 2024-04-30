/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/04/30 14:10:38 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <sys/wait.h>

void	error_handler(int status)
{
	if (status == -1)
	{
		ft_putendl_fd("Error: Incorrect arguments", 2);
		ft_putendl_fd("Hint: ./pipex infile \"cmd1\" \"cmd2\" outfile", 2);
		exit(EXIT_FAILURE);
	}
}

void	child_proc(int *p_fd, char *argv[], char *env[])
{
	int	infd;

	close(p_fd[0]);
	infd = openfile(argv[1], 0);
	adv_dup2(infd, STDIN_FILENO, 0);
	adv_dup2(p_fd[1], STDOUT_FILENO, 1);
	exec_cmds(argv[2], env);
}

void	parent_proc(int *p_fd, char *argv[], char *env[])
{
	int	outfd;

	close(p_fd[1]);
	outfd = openfile(argv[4], 1);
	adv_dup2(outfd, STDOUT_FILENO, 1);
	adv_dup2(p_fd[0], STDIN_FILENO, 0);
	exec_cmds(argv[3], env);
}
