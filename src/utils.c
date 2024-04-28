/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/04/28 20:51:15 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"

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
