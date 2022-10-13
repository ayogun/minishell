/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:16:32 by yogun             #+#    #+#             */
/*   Updated: 2022/10/13 10:19:27 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_token_dquote(t_data *a, int i)
{
	int	j;

	j = 0;
	while (a->cmd_line[i + j] && a->cmd_line[i + j] != '"')
	{
		if (a->cmd_line[i + j] == '$' && a->cmd_line[i + j + 1] != '"')
		{
			if (j)
				ft_new_token(a, 'W', ft_substr(a->cmd_line, i, j), 1);
			i = ft_token_dollar(a, i + j + 1, 0);
			j = -1;
		}
		j++;
	}
	if (!a->cmd_line[i + j])
	{
		a->exit_status = 258;
		ft_free(a, 1);
		write(2, "syntax error, missing \"\n", 24);
		return (-1);
	}
	ft_new_token(a, 'W', ft_substr(a->cmd_line, i, j), 1);
	return (i + j + 1);
}