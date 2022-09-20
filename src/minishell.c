/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:45:59 by yogun             #+#    #+#             */
/*   Updated: 2022/09/20 16:22:16 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{	
	t_data data;

	if (argc == 1)
	{
		data.argv = argv;
		data.env = envp;
		write(1,"$",1);
		while(1)
			sleep(10);
	}
	else
		printf("Too many arguments.");
	return 0;
}
