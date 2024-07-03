/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:15:29 by szhong            #+#    #+#             */
/*   Updated: 2024/05/30 14:15:33 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "bonus.h"
#include "pipex.h"
#include <sys/wait.h>
#include <stdio.h>

void	here_doc(char *argv[])
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		perror("pipe()");
	pid = fork();
	if (pid == -1)
		perror("fork()");
	else if (pid == 0)
		get_usrinput(argv, p_fd);
	else
	{
		wait(NULL);
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
	}
}

void	get_usrinput(char *argv[], int *p_fd)
{
	char	*usr_input;

	close(p_fd[0]);
	while (1)
	{
		usr_input = get_next_line(STDIN_FILENO);
		if (ft_strncmp(argv[2], usr_input, ft_strlen(argv[2])) == 0 \
			&& ft_strlen(argv[2]) == ft_strlen(usr_input) - 1)
		{
			free(usr_input);
			break ;
		}
		ft_putstr_fd(usr_input, p_fd[1]);
		free(usr_input);
	}
	exit(EXIT_SUCCESS);
}

void	pipexing(char *cmd, char *env[])
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		exec_cmds(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
	}
}

int	open_files(char *pathname, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(pathname, O_RDONLY, 0777);
	if (flag == 1)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (flag == 2)
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	main(int argc, char *argv[], char *env[])
{
	int	i;
	int	outfile;
	int	infile;

	i = 0;
	if (argc < 5 || (ft_strcmp("here_doc", argv[1]) == 0 && argc < 6))
		error_handler(-1);
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		i = 3;
		outfile = open_files(argv[argc - 1], 2);
		here_doc(argv);
	}
	else
	{
		i = 2;
		infile = open_files(argv[1], 0);
		outfile = open_files(argv[argc - 1], 1);
		dup2(infile, STDIN_FILENO);
	}
	while (i < argc - 2)
		pipexing(argv[i++], env);
	dup2(outfile, STDOUT_FILENO);
	exec_cmds(argv[argc - 2], env);
}
