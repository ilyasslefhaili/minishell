/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:54:13 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/06 13:33:59 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
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
char	*ft_substr(char  *s, int start, int len);
int	get_parts(char  *s, char c);
char	**ft_split(char  *s, char c);
int ft_strlen(char *s);
char	*ft_strjoin(char  *s1, char  *s2);
#endif