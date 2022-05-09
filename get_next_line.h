/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:58:56 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/09 17:14:47 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include "./libft/libft.h"
# include<stdio.h> 
# include <fcntl.h> 
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
#define BUFFER_SIZE 1
int			ft_strchr_gnl(const char *s, int c);
char		*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char const *s2);
#endif