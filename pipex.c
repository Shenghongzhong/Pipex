/4* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/04/26 17:28:20 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

char	**get_paths(char *var, char **env)
{
	char	*path;
	char	**path_arr;
	int	i;
	size_t	var_size;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], var, 5) != 0)
		{
			var_size = ft_strlen(env[i]) - 4;
			path = ft_substr(env[i], 5, var_size);
			break ;
		}
		i++;
	}
	path_arr = ft_split(path, ':');
	free(path);
	return (path_arr);
}

char	*get_program(char *cmd, char **env)
{
	char	**path_arr;
	int	i;
	char	*path_to_cmd;
	size_t	n_size;

	i = -1;
	path_arr = get_paths("PATH", env);
	while (path_arr[++i] != NULL)
	{
		n_size = ft_strlen(path_arr[i]) + 2;
		ft_strlcat(path_arr[i], "/", n_size);
		path_to_cmd = ft_strjoin(path_arr[i], cmd);
		if (access(path_to_cmd, F_OK| X_OK) == 0)
		{
			free(path_arr);
			return (path_to_cmd);
		};
		free(path_to_cmd);
	}
	return (0);
}

void	exec_cmds(char *argv, char **env)
{
	char	**cmd_arr;
	char	*path_exe;

	cmd_arr = ft_split(argv, ' ');
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
