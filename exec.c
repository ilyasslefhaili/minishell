/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/12 21:01:02 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <limits.h>
#include "get_next_line.h"

void	ft_echo(char *s, char flag)
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

char	*get_promt(void)
{
	char	*cmd;

	cmd = readline("Exec: ");
	if (cmd && *cmd)
		add_history(cmd);
	return (cmd);
}

void	sig_handler(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
		(void)0;
	if (sig == SIGINT)
	{
		get_promt();
		rl_on_new_line();
		rl_redisplay();
	}
}

char	*get_path(char *cmd)
{
	char	*path;
	char	**command_path;
	int		i;

	path = ft_strdup("/usr/local/bin:/usr/bin:/bin:\
			/usr/sbin:/sbin:/usr/local/munki");
	i = 0;
	command_path = ft_split(path, ':');
	while (command_path[i])
	{
		command_path[i] = ft_strjoin(command_path[i], "/");
		command_path[i] = ft_strjoin(command_path[i], cmd);
		if (access(command_path[i], F_OK) == 0)
			return (command_path[i]);
		i++;
	}
	return (NULL);
}

void	ft_execute(char *cmd, char **env)
{
	char	**test;
	char	*command_path;

	test = ft_split(cmd, ' ');
	command_path = get_path(test[0]);
	if (fork() == 0)
	{
		if (access(command_path, F_OK) == 0)
			execve(command_path, test, env);
		perror("Error: ");
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}

void	ft_redirect_output(char	*cmd, char *file, char **env)
{
	int		fd;
	char	**command_args;
	char	*path;

	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		perror("Error: ");
	command_args = ft_split(cmd, ' ');
	if (fork() == 0)
	{
		path = get_path(command_args[0]);
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

void	ft_redirect_output_2(char *cmd, char *file, char **env)
{
	int		fd;
	char	**command_args;
	char	*path;

	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		perror("Error: ");
	command_args = ft_split(cmd, ' ');
	if (fork() == 0)
	{
		path = get_path(command_args[0]);
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

int	ft_strcmp(char *s, char *str)
{
	int	i;

	i = 0;
	while (s[i] || str[i])
	{
		if (s[i] != str[i])
			return (s[i] - str[i]);
		i++;
	}
	return (0);
}

void	ft_herdoc(char *cmd, char *delimeter, char **env)
{
	char	*result;
	int		fd[2];

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
				break ;
			write(fd[1], result, ft_strlen(result));
		}
		dup2(fd[0], STDIN_FILENO);
		ft_execute(cmd, env);
	}
}

t_list	*get_env_list(char **env)
{
	t_list	*env_list;
	int		i;

	i = 0;
	env_list = ft_lstnew(env[i++]);
	while (env[i++ + 1])
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(env[i])));
	return (env_list);
}

void	ft_env(t_list *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

void	ft_export(t_list *env, char *arg)
{
	if (arg == NULL)
	{
		sort_list(&env);
		while (env)
		{
			printf("%s\n", env->content);
			env = env->next;
		}
	}
	else
	{
		ft_lstadd_front(&env, ft_lstnew(arg));
		sort_list(&env);
		while (env)
		{
			printf("%s\n", env->content);
			env = env->next;
		}
	}
}

void	ft_cd(char *path, t_list *env_list)
{
	char	*old_wd;
	char	current_wd[PATH_MAX];
	char	buffer[PATH_MAX];

	if (ft_strcmp("-", path) == 0)
	{
		getcwd(current_wd, sizeof(current_wd));
		old_wd = getenv("OLDPWD");
		if (chdir(old_wd) == -1)
			perror("Error: ");
		ft_setenv(&env_list, "OLDPWD", current_wd);
		getcwd(buffer, sizeof(buffer));
		ft_setenv(&env_list, "PWD", buffer);
	}
	else if (ft_strcmp("~", path) == 0)
	{
		if (chdir(getenv("HOME")) == -1)
			perror("Error ");
	}
	else
		if (chdir(path) == -1)
			return ;
}

void	ft_unset(t_list **env_list, char *to_delete)
{
	t_list	*first;
	t_list	*second;
	t_list	*temp;
	char	**cmd;

	first = *env_list;
	cmd = ft_split((*env_list)->content, '=');
	if (cmd[0] == NULL)
		return ;
	if (ft_strcmp(cmd[0], to_delete) == 0)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free(temp);
		return ;
	}
	second = first->next;
	while (second)
	{
		cmd = ft_split(second->content, '='); /// wa9ila che9itha hna
		if (ft_strcmp(cmd[0], to_delete) == 0)
		{
			temp = second;
			first->next = second->next;
			free(temp);
			return ;
		}
		first = second;
		second = second->next;
	}
}

void	sort_list(t_list **env_list)
{
	t_list	*p;
	t_list	*q;
	char	*val;

	p = *env_list;
	while (p)
	{
		q = *env_list;
		while (q->next)
		{
			if (ft_strcmp(q->content, q->next->content) > 0)
			{
				val = q->content;
				q->content = q->next->content;
				q->next->content = val;
			}
			q = q->next;
		}
		p = p ->next;
	}
}

void	ft_pwd(void)
{
	char	working_directory[PATH_MAX];

	getcwd(working_directory, sizeof(working_directory));
	printf("%s\n", working_directory);
}

/* returns the node in env_list that containts var_name
	if var_name not found it returns NULL; */

t_list	*ft_getenv(t_list *env_list, char *var_name)
{
	char	*temp;

	while (env_list)
	{
		temp = ft_split(env_list->content, '=')[0];
		if (!temp || !*temp)
			return (NULL);
		if (ft_strcmp(temp, var_name) == 0)
			return (env_list);
		env_list = env_list ->next;
	}
	return (NULL);
}

// assign the var_val to var_name and and add it to env_list
void	ft_setenv(t_list **env_list, char *var_name, char *var_val)
{
	char	*var;
	t_list	*temp;

	temp = ft_getenv(*env_list, var_name);
	if (temp == NULL)
	{
		var = ft_strjoin(var_name, "=");
		var = ft_strjoin(var, var_val);
		ft_lstadd_back(env_list, ft_lstnew(var));
	}
	else
	{
		ft_unset(env_list, var_name);
		ft_setenv(env_list, var_name, var_val);
	}
}
void	ft_clear_env(t_list **env_list)
{
	t_list	*temp;

	while (*env_list)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free(temp);
	}
	free(*env_list);
}

int main(int ac, char **av, char **env)
{
	char	*cmd;
	t_list	*temp_env_vars;
	t_list	*env_list;
	
	(void)ac;
	(void)av;
	cmd = NULL;
	temp_env_vars = ft_lstnew(ft_strdup(""));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	env_list = get_env_list(env);
	while (true)
	{
		cmd = get_promt();
		if (cmd == NULL)
			exit(EXIT_SUCCESS);
		if (*cmd)
		{
			if (ft_strnstr(cmd, "=", ft_strlen(cmd)) != NULL)
				ft_lstadd_front(&temp_env_vars, ft_lstnew(cmd));
			else if (ft_strnstr(cmd, ">", ft_strlen(cmd)) != NULL)
			{
				char *temp = ft_strnstr(cmd, ">>", ft_strlen(cmd));
				if (temp == NULL)
				{
					char **args = ft_split(cmd, '>');
					ft_redirect_output(args[0], args[1], env);
				}
				else
				{
					char **args = ft_split(cmd, '>');
					ft_redirect_output_2(args[0], args[1], env);
				}
			}
			else if (ft_strnstr(cmd, "cd", ft_strlen(cmd)) != NULL)
			{
				char *path = ft_split(cmd, ' ')[1];
				ft_cd(path, env_list);
			}
			else if (ft_strnstr(cmd, "export", ft_strlen(cmd)) != NULL)
			{
				char **export_args = ft_split(cmd, ' ');
				if (export_args[1] == NULL)
					ft_export(env_list, NULL);
				t_list *temp = ft_getenv(temp_env_vars, export_args[1]);
				if (temp)
				{
					char **splitted_var = ft_split(temp->content, '=');
					ft_setenv(&env_list, splitted_var[0], splitted_var[1]);
				}
			}
			else if (ft_strcmp(cmd, "env") == 0)
				ft_env(env_list);
			else if (ft_strnstr(cmd, "unset", ft_strlen(cmd)) != NULL)
			{
				char **unset_args = ft_split(cmd, ' ');
				if (unset_args[1] != NULL)
				{
					ft_unset(&env_list, unset_args[1]);
					ft_unset(&temp_env_vars, unset_args[1]);
				}
				else
					printf("unset: Not enough arguments\n");
			}
			else if (ft_strcmp(cmd, "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(cmd, "exit") == 0)
				exit(EXIT_SUCCESS);
			else
				ft_execute(cmd, env);
		}
	}
}