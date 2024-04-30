/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:15:29 by szhong            #+#    #+#             */
/*   Updated: 2024/04/30 18:02:04 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <sys/wait.h>
#include <stdio.h>


void	child_proc(int *p_fd, char **argv)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		perror("open() Error");
		exit(EXIT_FAILURE);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("no such file:", 2);
		ft_putendl_fd(argv[1], 2);
		perror("dup2(infile, STDIN_FILENO)\nError");
	}
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
		perror("dup2(p_fd[1], STDOUT_FILENO)\nError");
	exec_cmds();
	exit(EXIT_SUCCESS);
}

void	parent_proc(int *p_fd, char **argv)
{
	int	outfile;

	outfile = open(argv[], O_RWONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		perror("open() Error");
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
		perror("dup2(p_fd[0], STDIN_FILENO)\nError");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror("dup2(outfile, STDOUT_FILENO)\nError");
	exec_cmd();
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int	p_fd[2];
	int	num_cmds;
	int	i;
	int	j;

	if (argc < 0)
		ft_printf("error\n");//error_handler(-1);
	num_cmds = 0;
	j = -1;
	while (*argv)
	{
		num_cmds++;
		argv++;
	}
	num_cmds -= 3;
	ft_printf("cmds are %d\n", num_cmds);
	i = -1;
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
			parent_doc(p_fd[0], argv);
		}
		else 
			child_proc(p_fd[1], argv);
	}
}
