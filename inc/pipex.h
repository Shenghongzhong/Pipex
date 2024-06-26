/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:46:13 by szhong            #+#    #+#             */
/*   Updated: 2024/04/28 21:45:56 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void	exec_cmds(char *arg, char **env);
void	child_proc(int *p_fd, char *argv[], char *env[]);
void	parent_proc(int *p_fd, char *argv[], char *env[]);
char	**get_paths(char *var, char **env);
void	free_arr(char **path_arr);
char	*get_program(char *cmd, char **env);
void	error_handler(int status);

#endif
