/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:46:13 by szhong            #+#    #+#             */
/*   Updated: 2024/05/21 10:44:57 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

void	here_doc(char *argv[]);
void	get_usrinput(char *argv[], int *p_fd);
void	pipexing(char *cmd, char *env[]);
int		open_files(char *pathname, int flag);
#endif
