/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/09 21:06:56 by ytouate          ###   ########.fr       */
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

char *get_promt(char *cmd)
{
	if (cmd)
	{
		free(cmd);
		cmd = (char *)NULL;
	}
	cmd = readline("Exec: ");
	if (cmd && *cmd)
		add_history(cmd);
	return (cmd);
}

void sig_handler(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
		(void)0;
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

void ft_execute(char *cmd, char **env)
{
	char **test = ft_split(cmd, ' ');
	if (fork() == 0)
	{
		char *command_path = get_path(test[0]);
		if (command_path == NULL)
			perror("Error: ");
		if (access(command_path, F_OK) == 0)
			execve(command_path, test, env);
		perror("Error: ");
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
			perror("Error: ");
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

void ft_herdoc(char *delimeter)
{
	char *temp;
	char *result = ft_strdup("");
	temp = readline(">>");
	while (ft_strnstr(temp, delimeter, ft_strlen(temp)) == NULL && ft_strlen(temp) != ft_strlen(delimeter))
	{
		result = ft_strjoin(result, temp);
		result = ft_strjoin(result, "\n");
		temp = readline(">>");
	}
	if (result && *result)
		printf("%s\n", result);
}

int ft_strcmp(char *s, char *str)
{
	int i = 0;
	while(s[i] || str[i])
	{
		if (s[i] != str[i])
			return 1;
		i++;
	}
	return (0);
}

void ft_cd(char **env)
{	
}
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;
	(void)av;
	char *cmd;
	cmd = NULL;
	signal(SIGQUIT, SIG_IGN);
	// 
	// ft_herdoc(av[1]); // it is given a delimeter then reads the input until a line containing the delimeter is seen
	// ft_echo(av[1], 'n'); // like the echo bash function printf the argument passed to it -n means print the parameter without new line at the end
	// ft_execute(av[1], env); // excute the commands that can be excuted such as ls / grep / pwd / cat / head / tail ...
	// ft_redirect_output_2(av[1], "file.", env); // used to redirect the output of a command to a file stream using the following syntax : cmd > file
	// ft_redirect_output(av[1], "file.txt", env); // used to append the output of a command to a given file using the following syntax : cmd >> file
}