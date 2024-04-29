/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:15:29 by szhong            #+#    #+#             */
/*   Updated: 2024/04/29 18:36:18 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char *argv[], char **env)
{
	pid_t	pid;
	int	p_fd[2];
	int	num_cmds;
	int	i;

	if (argc < 5)
		error_handler(-1);
	while (*(*argv + 1) != NULL)
	{
		num_cmds++;
		(*argv + 1)++;
	}
	num_cmds -= 2;
	i = -1;
	while (++i < num_cmds)
	{
		// damn I forgot about how to structure the minimum process of 2
		// need to memorise it?
	}
	if (pipe(p_fd) == -1)
	{
		perror("Pipe Creation Failure");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) == -1)
	{
		perror("Fork Failure");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process();
	else
		parent_process();

}
