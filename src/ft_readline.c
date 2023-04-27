/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:16:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/27 18:46:40 by gbertet          ###   ########.fr       */
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

char	*ft_read_here_doc(char *prompt, char *eof)
{
	char	*line;

	line = readline(prompt);
	if (line)
		return (ft_strjoin(line, "\n"));
	else
		return (eof);
}