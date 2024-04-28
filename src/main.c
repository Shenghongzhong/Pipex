/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:33 by szhong            #+#    #+#             */
/*   Updated: 2024/04/28 21:41:26 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	int	p_fd[2];
	int	id;

	if (argc != 5)
		error_handler(-1);
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
