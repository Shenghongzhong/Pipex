/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/04/23 16:42:48 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void	child_proc(int *p_fd, char *argv[], char *env[])
{
	int	fd;

	close(p_fd[0]);
	fd = open(argv[1], O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	char *args[] = {"ls", "-l", NULL};
	execve("/bin/ls", args, env);
}

void	parent_proc(int *p_fd, char *argv[], char *env[])
{
	int	outfd;

	close(p_fd[1]);
	outfd = open(argv[4], O_RDWR | O_CREAT, 0777);
	dup2(outfd, STDOUT_FILENO);
	dup2(p_fd[0], STDIN_FILENO);
	char *args[] = {"wc", "-l", NULL};
	execve("/usr/bin/wc", args, env);
}

int	main(int argc, char *argv[], char *env[])
{
	int	i;
	int	p_fd[2];
	int	id;

	i = 1;
	if (argc != 5)
		return (-1);
	else
	{
		if (pipe(p_fd) == -1)
		{
			ft_printf("Pipe creation failed");
			exit(EXIT_FAILURE);
		}
		id = fork();
		if (id == -1)
		{
			ft_printf("Fork Failed");
			exit(EXIT_FAILURE);
		}
		if (id == 0)
			child_proc(p_fd, argv, env);
		else
			parent_proc(p_fd, argv, env);

	}
	return (0);
		
}

