/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:47:29 by yogun             #+#    #+#             */
/*   Updated: 2022/10/13 11:07:38 by yogun            ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	int		fd[2];
	int		in;
	int		out;
	int		hd;
	pid_t	pid;
	int		std[2];
	char	*argv;
	char	**envdb;
	char	*cmd_line;
	int		exit_status;
	t_token	*token;
	t_env	*env;
}				t_data;

t_env 	*tokenize_env(t_data *data);
t_env	*ft_new_env(char *str);
void	ft_free_env(t_env *env);
void 	init_shell();
int		ft_token_dollar(t_data *a, int i, int j);
char	*ft_token_dollar_sub(t_data *a, int i, int j);
void	ft_new_token(t_data *a, char c, char *s, int i);
void	ft_init_tokens(t_data *a, int in, int out);
void	ft_check_parameters(t_data *a, int i);
int		ft_check_symbol(char c);
int		check_next_token(t_data *a, char b);
int		ft_token_dquote(t_data *a, int i);
void	ft_new_token_sub(t_data *a, char c, char *s, int i);
void	ft_free_token(t_token *p);
void	ft_free(t_data *a, int i);
void	ft_free_env(t_env *env);





#endif