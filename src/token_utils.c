/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:31:23 by yogun             #+#    #+#             */
/*   Updated: 2022/10/15 21:31:39 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_token_separate(t_data *a)
{
	t_token	*tmp;

	tmp = a->token;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->i = 0;
	}
}
