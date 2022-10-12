/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:47:29 by yogun             #+#    #+#             */
/*   Updated: 2022/10/12 17:48:58 by yogun            ###   ########.fr       */
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

typedef struct s_token
{
	int				i;
	char			c;
	char			*content;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	int		fd[2];
	int		in;
	int		out;
	int		hd;
	pid_t	pid;
	int		std[2];
	char	**argv;
	char	**env;
	char	*cmd_line;
	int		exit_status;
	t_token	*token;
	t_env	*env;
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
void 	init_shell();


#endif