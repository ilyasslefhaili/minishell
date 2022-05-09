/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/09 11:06:01 by ytouate          ###   ########.fr       */
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
char *get_path(char *cmd)
{
	char *path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	char **command_path = ft_split(path, ':');
	int i = 0;
	while (command_path[i])
	{
		command_path[i] = ft_strjoin(command_path[i], "/");
		command_path[i] = ft_strjoin(command_path[i], cmd);
		if (access(command_path[i], F_OK) == 0)
			return (command_path[i]);
		i++;
	}
	return NULL;
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
		char *command_path = get_path(test[0]);
		if (access(command_path, F_OK) == 0)
			execve(command_path, test, env);
		printf("command not found\n");
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}

void ft_redirect_output(char *cmd, char *file, char **env)
{
	int fd;
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC , 0644);
	if (fd == -1)
		perror("Error: ");
	char **command_args = ft_split(cmd, ' ');
	if (fork() == 0)
	{
		char *path = get_path(command_args[0]);
		if (path == NULL)
			write(2, "Command Not Found\n", 19);
		else
		{
			dup2(fd, STDOUT_FILENO);
			execve(path, command_args, env);
		}
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}

void ft_redirect_output_2(char *cmd, char *file, char **env)
{
	int fd;
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		perror("Error: ");
	char **command_args = ft_split(cmd, ' ');
	if (fork() == 0)
	{
		char *path = get_path(command_args[0]);
		if (path == NULL)
			perror("Error: ");
		else
		{
			dup2( fd, STDOUT_FILENO);
			execve(path, command_args, env);
		}	
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}
int main(int ac, char **av, char **env)
{
	(void)ac;
	// ft_execute(av[1], av, env);
	// ft_redirect_output_2(av[1], "file.", env);
	ft_redirect_output(av[1], "file.txt", env);
	
}