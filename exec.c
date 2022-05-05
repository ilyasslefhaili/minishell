/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/05 10:15:24 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
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
void ft_echo(char *s, char flag)
{
	int	i;
	i = 0;
	if (flag == 'n')
		write(1, s, ft_strlen(s));
	else
	{
		write(1, s, ft_strlen(s));
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
void ft_cd(char **s)
{
	if (chdir(s[2]) == 0)
		printf("directory changed\n");
	else
		perror("Error");
}
void ft_pwd(void)
{
	char buffer[100];
	getcwd(buffer, 100);
	printf("%s\n", buffer);
}
int main(int ac, char **av)
{
	char *cmd;
	char *temp;
	(void)ac;
	while (1)
	{
		cmd = readline("Exec: ");
		if (ft_strcmp(cmd, "echo") == 0)
		{
			temp = readline("what to print ?: ");
			ft_echo(temp, '\0');
		}
		else if (ft_strcmp(cmd, "echo -n")== 0)
		{
			temp = readline("what to print ?: ");
			ft_echo(temp, 'n');
		}
		else if (ft_strcmp(cmd, "cd") == 0)
			ft_cd(av);
		else if (ft_strcmp(cmd, "pwd") == 0)
			ft_pwd();
		else
			write(2, "command not found\n", 19);
	}
}