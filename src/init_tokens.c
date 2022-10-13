/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:35:25 by yogun             #+#    #+#             */
/*   Updated: 2022/10/13 11:09:01 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_parameters(t_data *a, int i)
{
	while (i > -1 && a->cmd_line[i])
	{
		if (a->cmd_line[i] == '$')
			i = ft_token_dollar(a, i + 1, 0);
		else if (a->cmd_line[i] == '"')
			i = ft_token_dquote(a, i + 1);
		else if (a->cmd_line[i] == '\'')
			i = ft_token_quote(a, i + 1);
		else if (a->cmd_line[i] == '>' || a->cmd_line[i] == '<')
			i = ft_token_redir(a, i);
		else if (a->cmd_line[i] == '|')
			i = ft_token_pipeline(a, i + 1);
		else
			i = ft_token_word(a, i);
	}
}

void	ft_init_tokens(t_data *a, int in, int out)
{
	char	*tmp;

	tmp = ft_strtrim(a->cmd_line, " ");
	free(a->cmd_line);
	a->cmd_line = tmp;
	a->token = NULL;
	a->hd = 0;
	a->pid = -1;
	a->fd[0] = -1;
	a->fd[1] = -1;
	a->std[0] = in;
	a->std[1] = out;
	ft_check_parameters(a, 0);
}