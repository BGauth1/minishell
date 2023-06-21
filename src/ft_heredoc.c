/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:33:28 by gbertet           #+#    #+#             */
/*   Updated: 2023/06/21 18:24:53 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_fill_heredoc(char *eof, int fd)
{
	char	*line;
	int		eof_len;

	line = ft_read_here_doc("> ", eof);
	eof_len = ft_strlen(eof);
	if (eof)
	{
		while (ft_strncmp(line, eof, eof_len + 1))
		{
			ft_putstr_fd(line, fd);
			free(line);
			line = ft_read_here_doc("> ", eof);
		}
	}
	else
	{
		while (line[0])
		{
			ft_putstr_fd(line, fd);
			free(line);
			line = ft_read_here_doc("> ", eof);
		}
	}
	close(fd);
}

void    ft_heredoc(char **cmds)
{
	int	i;
    int	fd;

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

// int	main(int ac, char **av)
// {
// 	char *s;
// 	char **str;

// 	str = malloc(10 * sizeof(char *));
// 	str[9] = NULL;
// 	str[0] = ft_strdup("<<");
// 	str[1] = ft_strdup("oute");
// 	str[2] = ft_strdup("<<");
// 	str[3] = ft_strdup("out");
// 	str[4] = ft_strdup("commande");
// 	str[5] = ft_strdup(">");
// 	str[6] = ft_strdup("ah");
// 	str[7] = ft_strdup(">>");
// 	str[8] = ft_strdup("bh");

// 	ft_heredoc(str);
// 	int fd = open(".heredoc", O_RDONLY);
// 	s = get_next_line(fd);
// 	while (s)
// 	{
// 		ft_printf("%s", s);
// 		free(s);
// 		s = get_next_line(fd);
// 	}
// 	close (fd);
// }