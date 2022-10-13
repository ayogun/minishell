/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:05:24 by yogun             #+#    #+#             */
/*   Updated: 2022/10/13 11:07:29 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_token(t_token *p)
{
	t_token	*tmp;

	while (p)
	{
		tmp = p;
		if (p->content)
			free(p->content);
		p->content = NULL;
		p = p->next;
		tmp->next = NULL;
		free(tmp);
	}
}

// I am not sure if it works fully functional. <yogun>
void	ft_free(t_data *a, int i)
{
	if (a->cmd_line)
		free(a->cmd_line);
	a->cmd_line = NULL;
	if (i == 0 && a->env)
	{
		close(a->std[0]);
		close(a->std[1]);
		rl_on_new_line();
		rl_clear_history();
		a->envdb = NULL;
		a->argv = NULL;
		ft_free_env(a->env);
		a->env = NULL;
	}
	if (a->token)
		ft_free_token(a->token);
	a->token = NULL;
}

// This function frees the node from the memory. <yogun>
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