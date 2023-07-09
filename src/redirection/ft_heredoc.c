/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:33:28 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/09 16:18:00 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_signal_heredoc(char *line, char *eof_buff, int fd)
{
	if (line[0] == 0 && g_status == -13)
	{
		free(eof_buff);
		close(fd);
		return (1);
	}
	return (0);
}

static void	ft_var_env_in_heredoc(char *tmp, t_mishell mish, char *eof, int fd)
{
	int		i;
	char	*line;

	i = ft_check_dollar(tmp, 0);
	line = ft_handle_var_env(tmp, *mish.files);
	if (i == -1)
	{
		line = ft_strdup(tmp);
		free(tmp);
	}
	if (i != -1)
		line = ft_remove_quotes(line);
	if (!line[0] && eof[0])
		ft_putstr_fd("\n", fd);
	else
		ft_putstr_fd(line, fd);
	free(line);
}

static void	ft_fill_heredoc(char *eof, int fd, t_mishell mish)
{
	char	*line;
	char	*eof_buf;

	eof_buf = ft_strdup(eof);
	eof_buf = ft_remove_quotes(eof_buf);
	line = ft_read_here_doc("> ", eof_buf);
	if (ft_signal_heredoc(line, eof_buf, fd) == 1)
		return ;
	if (eof_buf)
	{
		while (ft_strncmp(line, eof_buf, ft_strlen(eof_buf) + 1) || \
			(line[0] && !eof_buf))
		{
			ft_var_env_in_heredoc(line, mish, eof_buf, fd);
			line = ft_read_here_doc("> ", eof_buf);
			if (ft_signal_heredoc(line, eof_buf, fd) == 1)
				return ;
		}
	}
	free(eof_buf);
	close(fd);
}

void	ft_heredoc(char **cmds, t_mishell mish)
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
					ft_fill_heredoc(cmds[i], fd, mish);
			}
			else
				ft_fill_heredoc(cmds[i], fd, mish);
		}
	}
}
