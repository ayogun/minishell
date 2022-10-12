/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:45:59 by yogun             #+#    #+#             */
/*   Updated: 2022/10/12 17:36:06 by yogun            ###   ########.fr       */
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
    usleep(700000);
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
t_env *list_env(t_data *data)
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

// export function but I wrote it very quick.
// We should check it later if I checked all edge cases
void	ft_export(char *s, t_data *a , t_env *env)
{
	a->exit_status = 0;
	while (env->next)
		env = env->next;
	env->next = ft_new_env(ft_strtrim(s, " "));	
}

// unset function, I think fully functional but 
// I should check later whether I handle all errors
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

// Straightforward echo function
// But there is no " and ' sign handling
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

// Check later if I handled all the cases. 
// With this function, I renew my OLDPWD and PWD
void	ft_cd_change_env(t_env *new, t_env *old)
{
	if (!new)
	{
		if (old)
		{
			if (old->value)
				free(old->value);
			old->value = NULL;
		}
		return ;
	}
	else
	{
		if (old)
		{
			if (old->value)
				free(old->value);
			old->value = new->value;
		}
		if (!old && new->value)
			free(new->value);
		new->value = getcwd(NULL, 0);
	}
}

// This function change my directory and send ENV to next ft
void	ft_cd_sub(char *s, t_data a, t_env *new)
{
	t_env	*old;

	old = new;
	if (chdir(s) != 0)
	{
		a.exit_status = 1;
		perror(s);
		return ;
	}
	while (old && ft_strncmp("OLDPWD", old->key, 6))
		old = old->next;
	while (new && ft_strncmp("PWD", new->key, 6))
		new = new->next;
	ft_cd_change_env(new, old);
}

// This function handles error, "cd" case and normal case.
// In normal case, it delivers the work to ft_cd_sub function.
void	ft_cd(char *s, t_data a, t_env *env)
{
	a.exit_status = 0;
	if (!s || *s == '\0')
	{
		while (env && ft_strncmp(env->key, "HOME", 4))
			env = env->next;
		if (env == NULL)
		{
			a.exit_status = 1;
			write(2, "cd: HOME not set\n", 17);
		}
		else
		{
			if (chdir(env->value) != 0)
			{
				perror("cd");
				a.exit_status = 1;
			}
		}
	}
	else
	{
		s++;
		ft_cd_sub(s, a, env);
	}
}

// print out enviroment variables
void	ft_env(char *s, t_data *a, t_env *env)
{
	a->exit_status = 0;
	if (*s++)
	{
		write(2, "Wrong input!\n", 13);
		return ;
	}
	while (env)
	{
		if (env->key && env->value)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
}

// rest of the exit function. Splitted for norminette
int	ft_exit_sub(char *s)
{
	int	i;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
	{
		write(2, "exit: ", 6);
		write(2, s, ft_strlen(s));
		write(2, ": numeric argument required\n", 28);
		return (255);
	}
	i = ft_atoi(s);
	return (i % 256);
}

// exiting from shell with proper error code and message
int	ft_exit(char *s)
{
	int	i;

	i = 0;
	if (!*s++)
		return (0);
	while (s[i] && s[i] != ' ')
		i++;
	
	if (s[i])
	{
		write(2, "exit: too many arguments\n", 25);
		return (128);
	}
	return (ft_exit_sub(s));
}

// I am not sure if it works fully functional
void ft_free(t_data a , t_env *env)
{
	a.cmd_line = NULL;
	if (a.env)
	{
		rl_on_new_line();
		rl_clear_history();
		a.env = NULL;
		ft_free_env(env);
	}
}
// This function is not fully functional. Should be expanded and ellaborated
void ft_last_exit(t_data *a)
{
	char *str;

	str = ft_itoa(a->exit_status);
	write(2 , str , ft_strlen(str));
	write(2 , "\n" , 1);
	
}

int	main(int argc, char **argv, char **envp)
{	
	t_data data;
	t_env *env;
	//t_env *tmp;
	int	in;
	int	out;
	
	if (argc == 1)
	{	
		init_shell();
		data.argv = argv;
		data.env = envp;
		data.exit_status = -1;
		in = dup(0);
		out = dup(1);
		
		//I will parse env variables 
		env = list_env(&data);
		//tmp = env;
		while(1)
		{
			data.cmd_line = readline("minishell > ");
			data.cmd_line = ft_strtrim(data.cmd_line, " ");
			// eğer yazılan satır boş bir satır değilse at baba memoriye
			if(data.cmd_line && *data.cmd_line)
				add_history(data.cmd_line);
			
			ft_init_tokens(&data, in, out);
			
			if(!ft_strncmp(data.cmd_line , "exit" , 4))
				data.exit_status = ft_exit(data.cmd_line+4);
			else if(!ft_strcmp(data.cmd_line , "pwd"))
				ft_pwd(data);
			else if(!ft_strncmp(data.cmd_line , "echo", 4))
				ft_echo(data.cmd_line+4,data);
			else if (!ft_strncmp(data.cmd_line, "cd", 2))
				ft_cd(data.cmd_line + 2, data, env);
			else if (!ft_strncmp(data.cmd_line, "env", 3))
				ft_env(data.cmd_line+3 , &data , env);
			else if (!ft_strncmp(data.cmd_line, "export", 6))
				ft_export(data.cmd_line+6, &data, env);
			else if (!ft_strncmp(data.cmd_line, "unset", 5))
				ft_unset(data.cmd_line+5, &data, env);
			else if (!ft_strncmp(data.cmd_line, "$?", 2))
				ft_last_exit(&data);
			free(data.cmd_line);
			if (data.exit_status != -1)
			{
				// Here I will free the things
				ft_free(data , env);
				//system("leaks minishell");
				exit(data.exit_status);
			}
		}	
	}
	else
	{
		printf("Too many arguments.\n");
	}
	
	return 0;
}
