/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/04/28 16:30:28 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void	exec_cmds(char *arg, char **env)
{
	char	**cmd_arr;
	char	*path_exe;

	cmd_arr = ft_split(arg, ' ');
	path_exe = get_program(cmd_arr[0], env);
	if (execve(path_exe, cmd_arr, env) == -1)
	{
		ft_putstr_fd("Error: Command not found:", 2);
		ft_putendl_fd(cmd_arr[0], 2);
		exit(EXIT_SUCCESS);
	}
	free(cmd_arr);
	free(path_exe);
}

void	child_proc(int *p_fd, char *argv[], char *env[])
{
	int	fd;

	close(p_fd[0]);
	fd = open(argv[1], O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	exec_cmds(argv[2], env);
}

void	parent_proc(int *p_fd, char *argv[], char *env[])
{
	int	outfd;

	close(p_fd[1]);
	outfd = open(argv[4], O_RDWR | O_CREAT, 0777);
	dup2(outfd, STDOUT_FILENO);
	dup2(p_fd[0], STDIN_FILENO);
	exec_cmds(argv[3], env);
}
