/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/04/30 14:33:14 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

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
	infd = open(argv[1], O_RDONLY, 0777);
	if (infd == -1)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(argv[1], 2);
	}
	if (dup2(infd, STDIN_FILENO) < 0)
		perror("dup2(infd,STDIN_FILENO)\nError");
	if (dup2(p_fd[1], STDOUT_FILENO) < 0)
		perror("dup2(p_fd[1], STDOUTFILENO);\nError");
	exec_cmds(argv[2], env);
}

void	parent_proc(int *p_fd, char *argv[], char *env[])
{
	int	outfd;

	close(p_fd[1]);
	outfd = open(argv[4], O_RDWR | O_CREAT, 0777);
	if (outfd == -1)
		perror("outfd\nError");
	if (dup2(outfd, STDOUT_FILENO) < 0)
		perror("dup2(outfd, STDOUT_FILENO);\nError");
	if (dup2(p_fd[0], STDIN_FILENO) < 0)
		perror("dup2(outfd, STDIN_FILENO);\nError");
	exec_cmds(argv[3], env);
}
