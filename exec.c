/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/07 12:02:24 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <limits.h>
#include "get_next_line.h"

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
	if (chdir(s) == 0);
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
	(void)sig;
	// if (sig == SIGQUIT)
	// 	(void)0;
	if (sig == SIGINT)
	{
		write(2, "hello world\n", 13);
	}
}
void ft_execute(char *cmd, char **av, char **env)
{
	(void)av;
	char **test = ft_split(cmd, ' ');
	if (ft_strcmp(test[0], "cd") == 0)
	{
		printf("here\n");
		if (test[1] != NULL)
			chdir(test[1]);
		return ;
	}
	if (fork() == 0)
	{
		char *path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
		char **command_path = ft_split(path, ':');
		int i = 0;
		while (command_path[i])
		{
			command_path[i] = ft_strjoin(command_path[i], "/");
			command_path[i] = ft_strjoin(command_path[i], test[0]);
			if (access(command_path[i], F_OK) == 0)
				execve(command_path[i], test, env);
			i++;
		}
		printf("command not found\n");
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}
char **fill_argv(char *cmd)
{
	int size = get_parts(cmd, ' ');
	char **result = malloc(sizeof(char *) * size + 1);
	char **temp = ft_split(cmd, ' ');
	int i = 0;
	int j = 0;
	// result[j++] = strdup("./exec");
	while (cmd[i])
		result[j++] = temp[i++];
	result[j] = NULL;
	return (result);
}
void ft_redirect(int ac, char **av)
{
	(void)ac;
	(void)av;
	char *temp;
	int flag = 1;
	while (flag)
	{
		temp = get_next_line(1);
		if (!temp) 
			flag = 0;
		printf("%s\n", temp);
	}
}
int main(int ac, char **av, char **env)
{
	char	*cmd;
	(void)ac;
	(void)av;
	ft_redirect(ac, av);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		cmd = get_promt();
		if (strcmp(cmd, "exit") == 0)
			exit(0);
		ft_execute(cmd, av, env);
	}
}