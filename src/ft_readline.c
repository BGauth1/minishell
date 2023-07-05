/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:16:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/05 17:19:30 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(char *str)
{
	char	*line;

	line = readline(str);
	if (line)
	{
		add_history(line);
		return (line);
	}
	else
		return (ft_strdup("exit"));
}

int	ft_path_pos_prompt(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char *) * 1024);
	if (pwd == NULL)
		exit (1);
	if (getcwd(pwd, 1024) == NULL)
	{
		perror(strerror(errno));
		free(pwd);
		return (1);
	}
	free(pwd);
	return (0);
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
