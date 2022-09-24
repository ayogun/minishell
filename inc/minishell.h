/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:47:29 by yogun             #+#    #+#             */
/*   Updated: 2022/09/24 16:46:23 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define clear() printf("\033[H\033[J")

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../lib/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	**argv;
	char	**env;
	char	*cmd_line;
}				t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env 	*tokenize_env(t_data *data);
t_env	*ft_new_env(char *str);
void	ft_free_env(t_env *env);
void 	printdir();
void 	init_shell();


#endif