/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:58:56 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/07 11:54:04 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<stdio.h> 
# include <fcntl.h> 
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
#define BUFFER_SIZE 1
char		*ft_strjoin(char *s1, char const *s2);
int			ft_strchr(const char *s, int c);
char		*get_next_line(int fd);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);

#endif