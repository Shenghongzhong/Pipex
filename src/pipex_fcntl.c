/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fcntl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:34:32 by szhong            #+#    #+#             */
/*   Updated: 2024/04/30 14:11:19 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"
#include <fcntl.h>

void	adv_dup2(int src, int tar, int flag)
{
	int	dup_ret;

	dup_ret = dup2(src, tar);
	if (dup_ret < 0)
	{
		if (flag == 0)
			ft_putendl_fd("Error: Fail to redirect fd to stdin", 2);
		else if (flag == 1)
			ft_putendl_fd("Error: Fail to redirect stdout to fd", 2);
		exit(EXIT_FAILURE);
	}
}

int	openfile(char *pathname, int flag)
{
	int	filefd;

	filefd = -1;
	if (flag == 0)
	{
		filefd = open(pathname, O_RDONLY, 0777);
		if (filefd == -1)
		{
			ft_putstr_fd("no such file or directory: ", 2);
			ft_putendl_fd(pathname, 2);
			exit(EXIT_FAILURE);
		}
	}
	else if (flag == 1)
	{
		filefd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (filefd == -1)
		{
			ft_putstr_fd("Error: Failed to open the file: ", 2);
			ft_putendl_fd(pathname, 2);
			exit(EXIT_FAILURE);
		}
	}
	else
		ft_putendl_fd("Error: function openfile()", 2); 
	return (filefd);
}
