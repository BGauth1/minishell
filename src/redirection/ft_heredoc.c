/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:33:28 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/05 18:09:46 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_signal_heredoc(char *line, char *eof_buff, int fd)
{
	if (line[0] == 0 && g_status == -1)
	{
		free(eof_buff);
		close(fd);
		g_status = 130;
		return (1);
	}
	return (0);
}

void	ft_fill_heredoc(char *eof, int fd)
{
	char	*line;
	int		eof_len;
	char	*eof_buf;

	eof_buf = ft_strdup(eof);
	eof_buf = ft_remove_quotes(eof_buf);
	line = ft_read_here_doc("> ", eof_buf);
	if (ft_signal_heredoc(line, eof_buf, fd) == 1)
		return ;
	eof_len = ft_strlen(eof_buf);
	if (eof_buf)
	{
		while (ft_strncmp(line, eof_buf, eof_len + 1) || (line[0] && !eof_buf))
		{
			ft_putstr_fd(line, fd);
			free(line);
			line = ft_read_here_doc("> ", eof_buf);
			if (ft_signal_heredoc(line, eof_buf, fd) == 1)
				return ;
		}
	}
	free(eof_buf);
	close(fd);
}

void	ft_heredoc(char **cmds)
{
	int		i;
	int		fd;

	i = 0;
	while (cmds[i])
	{
		if (!ft_strncmp(cmds[i++], "<<", 3))
		{
			fd = open(".heredoc", O_WRONLY | O_TRUNC);
			if (fd == -1)
			{
				fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (fd == -1)
				{
					printf("minishell: %s: %s\n", ".heredoc", strerror(errno));
					return ;
				}
				else
					ft_fill_heredoc(cmds[i], fd);
			}
			else
				ft_fill_heredoc(cmds[i], fd);
		}
	}
}
