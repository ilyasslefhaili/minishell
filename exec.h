/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:54:13 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/12 09:35:40 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
#include "./libft/libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <curses.h>
#include <term.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/stat.h>

int	get_parts(char  *s, char c);
void sort_list(t_list **env_list);
void ft_setenv(t_list **env_list, char *var_name, char *var_val);
// char	*get_next_line(int fd);
#endif