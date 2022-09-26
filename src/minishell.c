/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:45:59 by yogun             #+#    #+#             */
/*   Updated: 2022/09/26 15:35:46 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Greeting shell during startup
void init_shell()
{
    clear();
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MINISHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
        "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    clear();
}

// This function does exactly what pwd does.
void ft_pwd(t_data data)
{
	char	*s;

	data.exit_status = 0;
	s = getcwd(NULL, 0);
	if (!s)
	{
		data.exit_status = 1;
		perror("pwd");
		return ;
	}
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
}

// This function frees the node from the memory.
void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		if (env->value)
			free(env->value);
		env->value = NULL;
		free(env->key);
		env->key = NULL;
		env = env->next;
		tmp->next = NULL;
		free(tmp);
	}
}

// New node is being created under this function for env variable that has been sent.
t_env	*ft_new_env(char *str)
{
	t_env	*new;
	int		i;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new->key = ft_substr(str, 0, i);
	new->value = ft_strdup(str + i + 1);
	new->next = NULL;
	return (new);
}

// Here I will take env and tokenize them with linked list.
t_env *tokenize_env(t_data *data)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	i = 0;
	env = NULL;
	tmp2 = NULL;
	while (data->env[i])
	{
		tmp = ft_new_env(data->env[i]);
		if (!tmp)
		{
			ft_free_env(env);
			write(2, "Error: Memory allocation has failed!\n", 36);
			exit(EXIT_FAILURE);
		}
		if (!env)
			env = tmp;
		else
			tmp2->next = tmp;
		tmp2 = tmp;
		i++;
	}
	return (env);
}

void	ft_export(char *s, t_data *a , t_env *env)
{
	a->exit_status = 0;
	while (env->next)
		env = env->next;
	env->next = ft_new_env(ft_strtrim(s, " "));	
}

void	ft_unset(char *s, t_data *a , t_env *env)
{
	t_env *tmp;
	
	a->exit_status = 0;
	while (env->next)
	{
		tmp = env;
		env = env->next;
		if(!ft_strcmp(env->key , ft_strtrim(s," ")))
		{
			tmp->next = env->next;
			ft_free_env(env);
		}
	}
}

void ft_echo(char *s, t_data data)
{
	int	i;
	int	flag;

	data.exit_status = 0;
	flag = 0;
	if (s && *s == ' ')
		s++;
	while (s[0] && s[0] == '-' && s[1] == 'n')
	{
		i = 1;
		while (*s && s[i] == 'n')
			i++;
		if (s[i] == ' ' || !s[i])
		{
			flag = 1;
			if (s[i])
				i += 1;
			s += i;
		}
		else
			break ;
	}
	// Here we should add a function to handle double and single quotes
	ft_putstr_fd(s, 1);
	if (flag == 0)
		write(1, "\n", 1);
}

int	main(int argc, char **argv, char **envp)
{	
	t_data data;
	t_env *env;
	t_env *tmp;

	if (argc == 1)
	{
		init_shell();
		data.argv = argv;
		data.env = envp;
		data.exit_status = 0;
		//I will parse env variables 
		env = tokenize_env(&data);
		tmp = env;
		while(1)
		{
			data.cmd_line = readline("miniSH > ");
			data.cmd_line = ft_strtrim(data.cmd_line, " ");
			if(ft_strlen(data.cmd_line)>0)
				add_history(data.cmd_line);
			if(!ft_strcmp(data.cmd_line , "exit"))
				break;	
			else if(!ft_strcmp(data.cmd_line , "pwd"))		
				ft_pwd(data);
			else if(!ft_strncmp(data.cmd_line , "echo", 4))
				ft_echo(data.cmd_line+4,data);
			else if (!ft_strncmp(data.cmd_line, "cd", 2))
			{
				// according to rest of the cmd_line chdir function will work
				//chdir("some dir");
				//
			}
			else if (!ft_strncmp(data.cmd_line, "env", 3))
			{
				while(env)
				{
					printf("%s", env->key);
					printf("=%s\n",env->value);
					env = env->next;
				}
				env = tmp;
			}
			else if (!ft_strncmp(data.cmd_line, "export", 6))
			{
				ft_export(data.cmd_line+6, &data, env);
			}
			else if (!ft_strncmp(data.cmd_line, "unset", 5))
			{
				printf("unset will be here\n");
				ft_unset(data.cmd_line+5, &data, env);
			}
		}	
	}
	else
	{
		printf("Too many arguments.\n");
	}

		
	return 0;
}
