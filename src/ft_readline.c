/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:16:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 18:59:04 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(char *str)
{
	char	*line;

	line = readline(str);
	if (g_status == -13)
		return (NULL);
	if (line)
	{
		if (line[0])
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
	{
		if (eof)
		{
			if (!ft_strncmp(line, eof, ft_strlen(line) + 1))
			{
				free(line);
				return (eof);
			}
		}
		if (line[0] == '\0')
			return (line);
		return (ft_strjoin(line, "\n"));
	}
	else
	{
		printf("bash: warning: here-document delimited by end-of-file \
(wanted `%s')\n", eof);
		free(line);
		return (eof);
	}
}
