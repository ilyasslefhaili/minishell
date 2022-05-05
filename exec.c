/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/05 06:54:41 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "exec.h"

int ft_strlen(char *s)
{
	int count;
	count = 0;
	while (*s++)
		count++;
	return (count);
}
char *ft_join(char **s, int size)
{
	int total_lenght;
	int i;
	int j;
	int	k;
	char *joined_str;

	i = 1;
	k = 0;
	total_lenght = 0;
	while (i < size)
		total_lenght += ft_strlen(s[i++]);
	joined_str = malloc(sizeof(char) * (total_lenght + 1) + (i - 2));
	i = 0;
	while (++i < size)
	{
		j = 0;
		while (j < ft_strlen(s[i]))
			joined_str[k++] = s[i][j++];
		if (i != size -1)
			joined_str[k++] = ' ';
	}
	joined_str[k] = '\0';
	return (joined_str);
}
void ft_echo(int size, char **s, char flag)
{
	int	i;
	i = 0;
	char *to_be_printed;
	to_be_printed = ft_join(s, size);
	if (flag == 'n')
		write(1, to_be_printed, ft_strlen(to_be_printed));
	else
	{
		write(1, to_be_printed, ft_strlen(to_be_printed));
		write(1, "\n", 1);
	}
}
int ft_strcmp(char *s, char *str)
{
	int i;
	i = 0;
	while (s[i] || str[i])
	{
		if (s[i] != str[i])
			return (1);
		i++;
	}
	return (0);
}
int main(int ac, char **av)
{
	if (ac > 1)
	{
		if (ft_strcmp(av[1], "echo") == 0)
		{
			if (ft_strcmp(av[2], "-n") == 0)
				ft_echo(ac, av, 'n');
			else
				ft_echo(ac, av, '\0');
		}
		else if (ft_strcmp(av[1], "cd") == 0)
			;
		else
			write(2, "command not found\n", 19);
	}
	
}