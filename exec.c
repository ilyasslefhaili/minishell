/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/11 09:51:23 by ytouate          ###   ########.fr       */
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
int ft_strcmp(char *s, char *str)
{
	int i = 0;
	while(s[i] || str[i])
	{
		if (s[i] != str[i])
			return s[i] - str[i];
		i++;
	}
	return (0);
}
void ft_herdoc(char *cmd, char *delimeter, char **env)
{
	char *result;
	int fd[2];
	pipe(fd);
	cmd = get_path(cmd);
	if (cmd == NULL)
		printf("command not found\n");
	else
	{
		while (1)
		{
			write(1, "heredoc>", 9);
			result = get_next_line(0);
			if (ft_strcmp(ft_strtrim(result, "\n") , delimeter) == 0 || !result)
				break;
			write(fd[1], result, ft_strlen(result));
		}
		dup2(fd[0], STDIN_FILENO);
		ft_execute(cmd, env);
	}
}

t_list *get_env_list(char **env)
{
	t_list *env_list;
	int i = 0;
	env_list = ft_lstnew(env[i++]);
	while (env[i+1])
	{
		t_list *temp;
		temp = ft_lstnew(ft_strdup(env[i]));
		ft_lstadd_back(&env_list, temp);
		i++;
	}
	return (env_list);
}

void ft_env(t_list *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

void ft_export(t_list *env)
{
	sort_list(&env);
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

char *get_var_from_env(t_list *env_list, char *var_name)
{
	while(ft_strnstr(env_list->content, var_name, ft_strlen(env_list->content)) == NULL)
		env_list = env_list ->next;
	if (ft_strnstr(env_list->content, var_name, ft_strlen(env_list->content)))
		return (env_list->content);
	else
		return NULL;
}

void ft_cd(char *path, char **env)
{
	t_list *env = get_env_list(env);
	char *old_wd = get_var_from_env(env, "OLDPWD");
	printf("%s\n", old_wd);
	(void)path;
	char buffer[PATH_MAX];
	getcwd(buffer, sizeof(buffer));
}

void set_new_wd(t_list **env_list, char *wd_path)
{
	char *new_wd = ft_strdup("PWD=");
	new_wd = ft_strjoin(new_wd, wd_path);
	while (ft_strnstr((*env_list)->content, "PWD=", strlen((*env_list)->content)) == NULL && (*env_list)->next)
		(*env_list) = (*env_list)->next;
	free((*env_list)->content);
	(*env_list)->content = new_wd;
}

void ft_unset(char *to_delete, t_list **env_list)
{
	t_list	*first;
	first = *env_list;
	t_list *temp;
	char **cmd = ft_split((*env_list)->content, '=');
	if (ft_strcmp(cmd[0], to_delete) == 0)
	{

		temp = *env_list;
		*env_list =(*env_list) ->next;
		free(temp);
		return ;
	}
	t_list *second;
	second = first->next;
	while (second)
	{
		char **cmd = ft_split(second->content, '=');
		if (ft_strcmp(cmd[0], to_delete) == 0)
		{
			temp = second;
			first->next = second->next;
			free(temp);
		}
		first = second;
		second = second->next;
	}

}

void sort_list(t_list **env_list)
{
	t_list *p;
	t_list *q;
	p = *env_list;
	while (p)
	{
		q = *env_list;
		while (q->next)
		{
			if (ft_strcmp(q->content, q->next->content) > 0)
			{
				char *val = q->content;
				q->content = q->next->content;
				q->next->content = val;
			}
			q = q->next;
		}
		p = p ->next;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;
	(void)av;
	char *cmd;
	cmd = NULL;
	signal(SIGQUIT, SIG_IGN);
	t_list *temp = get_env_list(env);
	if (!temp)
		return 0;
	// ft_cd("..", env);
	// ft_execute(av[1], env);
	// ft_herdoc(av[1], av[2], env); // it is given a delimeter then reads the input until a line containing the delimeter is seen
	// ft_echo(av[1], 'n'); // like the echo bash function printf the argument passed to it -n means print the parameter without new line at the end
	// ft_execute(av[1], env); // excute the commands that can be excuted such as ls / grep / pwd / cat / head / tail ...
	// ft_redirect_output_2(av[1], "file.", env); // used to redirect the output of a command to a file stream using the following syntax : cmd > file
	// ft_redirect_output(av[1], "file.txt", env); // used to append the output of a command to a given file using the following syntax : cmd >> file
}