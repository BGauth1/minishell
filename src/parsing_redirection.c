/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:09:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/27 18:46:40 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rec_file(char *str, int i)
{
	int		y;
	char	*file;

	y = i;
	while (ft_iswhitespace(str[y]) == 0)
		y++;
	file = ft_substr(str, i, y - i);
	if (file == NULL)
		exit (1) ; //fct de free necessaire suivant pos dans cod
	return (file);
}

int	redirect_out(char *str, int *i)
{
	int	out;

	(*i)++;
	if (str[*i] == '>')
	{
		out = 1;
		(*i)++;
		if (str[*i] == '>')
		{
			printf("minsihell: syntax error near unexpected token `>'\n");
			exit (1);
		}
	}
	else
		out = 0;
	return (out);
}

int	find_redirect_left(char *str, t_files *fd)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			while (ft_iswhitespace(str[i]) == 1)
				i++;
			fd->fd_in = rec_file(str, i);
			return (0);
		}
		i++;
	}
	fd->fd_in = NULL;
	return (1);
}

int	find_redirect_right(char *str, t_files *fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			fd->out = redirect_out(str, &i);
			while (ft_iswhitespace(str[i]) == 1)
				i++;
			fd->fd_out = rec_file(str, i);
			return (0);
		}
		i++;
	}
	fd->out = -1;
	fd->fd_out = NULL;
	return (1);
}

t_files parsing_fd(char *str)
{
	t_files	fd;

	find_redirect_left(str, &fd);
	find_redirect_right(str, &fd);
	fd.nb_pipe = 0;
	if (fd.nb_pipe > 0)
	{
		ft_check_fdout(fd);
		ft_check_fdin(fd);
	}
	else {
		ft_check_fdin(fd);
		ft_check_fdout(fd);
	}
	return (fd);
}