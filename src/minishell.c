/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:45:59 by yogun             #+#    #+#             */
/*   Updated: 2022/09/20 17:10:08 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_new_env(char *s)
{
	t_env	*new;
	int		i;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	new->key = ft_substr(s, 0, i);
	new->value = ft_strdup(s + i + 1);
	new->next = NULL;
	return (new);
}

// Here I will take env and tokenize them with linked list.
void tokenize_env(t_data *data)
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
}

int	main(int argc, char **argv, char **envp)
{	
	t_data data;

	if (argc == 1)
	{
		data.argv = argv;
		data.env = envp;
		//I will parse env variables 
		tokenize_env(&data);
		write(1,"$",1);
		while(1)
			sleep(10);
	}
	else
		printf("Too many arguments.");
	return 0;
}
