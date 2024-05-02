/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/05/02 22:18:50 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"
#include <unistd.h>

void	error_handler(int status)
{
	if (status == -1)
	{
		ft_putendl_fd("Error: Incorrect arguments", 2);
		ft_putendl_fd("Hint: ./pipex infile \"cmd1\" \"cmd2\" outfile", 2);
		exit(EXIT_FAILURE);
	}
}

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
		exit(EXIT_FAILURE);
	}
	free_arr(cmd_arr);
	free(path_exe);
}

char	*get_program(char *cmd, char **env)
{
	char	**path_arr;
	int		i;
	char	*path_to_cmd;
	size_t	n_size;

	i = -1;
	path_arr = get_paths("PATH", env);
	while (path_arr[++i] != NULL)
	{
		n_size = ft_strlen(path_arr[i]) + ft_strlen(cmd);
		ft_strlcat(path_arr[i], "/", n_size);
		path_to_cmd = ft_strjoin(path_arr[i], cmd);
		if (access(path_to_cmd, F_OK | X_OK) == 0)
		{
			free_arr(path_arr);
			return (path_to_cmd);
		}
		free(path_to_cmd);
	}
	return (0);
}

char	**get_paths(char *var, char **env)
{
	char	*path;
	char	**path_arr;
	size_t	var_size;
	int		i;

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

void	free_arr(char **path_arr)
{
	int	i;

	i = -1;
	while (path_arr[++i] != NULL)
	{
		free(path_arr[i]);
	}
	free(path_arr);
}
