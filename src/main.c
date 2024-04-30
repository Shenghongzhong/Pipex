/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/04/30 14:37:45 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int argc, char *argv[], char *env[])
{
	int	p_fd[2];
	pid_t	pid;

	if (argc != 5)
		error_handler(-1);
	else
	{
		if (pipe(p_fd) == -1)
		{
			perror("Pipe creation failed");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Fork Failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child_proc(p_fd, argv, env);
		else
		{
			wait(NULL);
			parent_proc(p_fd, argv, env);
		}
	}
	return (0);
}
