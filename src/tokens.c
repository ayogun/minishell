/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:15:35 by yogun             #+#    #+#             */
/*   Updated: 2022/10/12 21:22:19 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_token_dollar_sub(t_data *a, int i, int j)
{
	char	*tmp;
	t_env	*tmp2;

	if (!a->env)
		return (NULL);
	tmp = ft_substr(a->cmd_line, i, j);
	tmp2 = a->env;
	while (tmp2)
	{
		if (!ft_strncmp(tmp, tmp2->key, 0))
		{
			free(tmp);
			return (ft_strdup(tmp2->value));
		}
		tmp2 = tmp2->next;
	}
	free(tmp);
	return (NULL);
}

int	ft_token_dollar(t_data *a, int i, int j)
{
	if (!a->cmd_line[i] || ft_check_symbol(a->cmd_line[i]) > 2 || a->cmd_line[i] == '$' || check_next_token(a, 'H'))
	{
		ft_new_token(a, 'W', ft_substr(a->cmd_line, i - 1, 1), 1);
		return (i);
	}
	if (a->cmd_line[i] == '?' || ft_isdigit(a->cmd_line[i]))
	{
		if (a->cmd_line[i] == '?')
			ft_new_token(a, 'W', ft_itoa(a->exit_status), 1);
		else
			if (a->cmd_line[i] == '0')
				ft_new_token(a, 'W', ft_strdup(a->argv), 1);
		i++;
		return (i);
	}
	while (ft_check_symbol(a->cmd_line[i + j]) == 0 && a->cmd_line[i + j] != '$')
		j++;
	ft_new_token(a, 'W', ft_token_dollar_sub(a, i, j), 1);
	return (i + j);
}

int	ft_check_symbol(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	if (c == '\0')
		return (3);
	if (c == ' ' || c == '\t' || c == '\v')
		return (4);
	if (c == '>')
		return (5);
	if (c == '<')
		return (6);
	if (c == '|')
		return (7);
	return (0);
}

int	check_next_token(t_data *a, char b)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = a->token;
	tmp2 = NULL;
	if (tmp)
		tmp2 = tmp->next;
	while (tmp2 && tmp2->next)
	{
		tmp = tmp->next;
		tmp2 = tmp->next;
	}
	if (!tmp2 || (tmp2 && tmp2->i == 1))
		tmp2 = tmp;
	if (tmp2 && tmp2->c == b)
		return (1);
	return (0);
}

void	ft_new_token(t_data *a, char c, char *s, int i)
{
	char	*tmp;
	t_token	*tmp2;

	if (!a->token)
		ft_new_token_sub(a, c, s, i);
	else
	{
		tmp2 = a->token;
		while (tmp2->next)
			tmp2 = tmp2->next;
		if (tmp2->i == 0)
			ft_new_token_sub(a, c, s, i);
		else
		{
			tmp = ft_strjoin(tmp2->content, s);
			if (tmp2->content)
				free(tmp2->content);
			if (s)
				free(s);
			tmp2->content = tmp;
		}
	}
}