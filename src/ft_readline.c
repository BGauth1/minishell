/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:16:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/26 15:30:18 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//fct en test
char *ft_readline(char *str)
{
	char    *line;

	line = readline(str);
	if (line)
	{
		add_history(line);
		return (line);		
	}
	else
		return (ft_strdup("exit"));
}