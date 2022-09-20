/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:47:29 by yogun             #+#    #+#             */
/*   Updated: 2022/09/20 17:04:00 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../lib/libft.h"

typedef struct s_data
{
	char	**argv;
	char	**env;
}				t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void 	tokenize_env(t_data *data);
t_env	*ft_new_env(char *s);
void 	tokenize_env(t_data *data)



#endif