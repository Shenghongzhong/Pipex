/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:15:29 by szhong            #+#    #+#             */
/*   Updated: 2024/05/01 17:18:52 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <sys/wait.h>
#include <stdio.h>
#include "bonus.h"

void	child_process(int *p_fd, char *input, char *arg, char *env[])
{
	int	infile;

	infile = open(input, O_RDONLY, 0777);
	if (infile == -1)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(input, 2);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("dup2(infile,STDIN_FILENO)\nError");
		exit(EXIT_FAILURE);
	}
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2(p_fd[1], STDOUT_FILENO)\nError");
		exit(EXIT_FAILURE);
	}
	exec_cmds(arg, env);
	exit(EXIT_SUCCESS);
}

void	parent_process(int *p_fd, char *output, char *arg, char *env[])
{
	int	outfile;

	outfile = open(output, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		perror("open() Error");
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
		perror("dup2(p_fd[0], STDIN_FILENO)\nError");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror("dup2(outfile, STDOUT_FILENO)\nError");
	exec_cmds(arg, env);
}

int	main(int argc, char *argv[], char **env)
{
	pid_t	pid;
	int	p_fd[2];
	int	num_cmds;
	int	i;
	int	j;

	if (argc < 5)
		error_handler(-1);
	num_cmds = argc - 3;
	i = -1;
	j = 2;
	if (pipe(p_fd) == -1)
	{
		perror("Pipe Creation Failure");
		exit(EXIT_FAILURE);
	}
	while (++i < num_cmds)
	{
		pid = fork();
		if (pid  == -1)
		{
			perror("Fork Failure");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			wait(NULL);
			parent_process(p_fd, argv[1], argv[j + 1], env);
		}
		else 
			child_process(p_fd, argv[argc - 1], argv[j], env);
		if (j + 1 == num_cmds)
			break ;
	}
}
