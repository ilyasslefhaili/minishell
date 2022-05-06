/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/06 14:33:04 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <limits.h>
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
void ft_cd(char *s)
{
	if (!s)
		return ;
	if (chdir(s) == 0)
		printf("directory changed\n");
	else
		perror("Error");
}
void ft_pwd(void)
{
	char buffer[FILENAME_MAX];
	getcwd(buffer, 100);
	printf("%s\n", buffer);
}
char *get_promt()
{
	char *cmd;
	cmd = readline("Exec: ");
	if (cmd == NULL)
		exit(EXIT_SUCCESS);
	return (cmd);
}
void sig_handler(int sig)
{
	if (sig == SIGQUIT)
		(void)0;
	if (sig == SIGINT)
	{
		rl_on_new_line();
	}
}
void ft_execute(char *cmd, char **av, char **env)
{
	int id;
	id = fork();
	if (id == 0)
	{
		char *path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
		char **command_path = ft_split(path, ':');
		int i = 0;
		(void)cmd;
		while (command_path[i])
		{
			command_path[i] = ft_strjoin(command_path[i], "/");
			printf("\n|%s|\n", cmd);
			command_path[i] = ft_strjoin(command_path[i], cmd);
			if (access(command_path[i], F_OK) == 0)
				execve(command_path[i], av, env);
			i++;
		}
		printf("command not found\n");
	}
	kill(0, SIGINT);

}
int main(int ac, char **av, char **env)
{
	char	*cmd;
	char	*temp;
	(void)ac;
	(void)av;
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		cmd = get_promt();
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
		{
			temp = readline("which directory: ");
			ft_cd(temp);
		}
		else if (ft_strcmp(cmd, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd, "exit") == 0)
			exit(EXIT_SUCCESS);
		else
			ft_execute(cmd, av, env);
	}
}