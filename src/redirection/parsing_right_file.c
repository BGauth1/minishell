/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:54:57 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 15:22:17 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_fdin(char *in)
{
	int	fd_in;

	if (in == NULL)
		return (1);
	fd_in = open(in, O_RDONLY);
	if (fd_in == -1)
	{
		printf("minishell: %s: %s\n", in, strerror(errno));
		g_status = 1;
		return (1);
	}
	else
		close(fd_in);
	return (0);
}

int	ft_check_fdout(char *out, int err)
{
	int	fd_out;

	if (out == NULL)
		return (1);
	fd_out = open(out, O_RDWR);
	if (fd_out == -1 && !err)
	{
		fd_out = open(out, O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			printf("minishell: %s: %s\n", out, strerror(errno));
			g_status = 1;
			return (1);
		}
		else
			close(fd_out);
	}
	else if (fd_out > 0)
		close(fd_out);
	return (0);
}

int	ft_check_fd(char **tmp_fds, int *type)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (tmp_fds[i])
	{
		if (type[i] == 1)
			err += ft_check_fdin(tmp_fds[i]);
		else
			err += ft_check_fdout(tmp_fds[i], err);
		i++;
	}
	return (err);
}

void	set_fd(char **tmp_fds, t_fds *fds, int *type)
{
	int	i;

	i = 0;
	fds->fd_in = NULL;
	fds->fd_out = NULL;
	while (tmp_fds[i])
	{
		if (type[i] == 1)
		{
			if (fds->fd_in != NULL)
				free(fds->fd_in);
			fds->fd_in = ft_strdup(tmp_fds[i]);
		}
		else
		{
			if (fds->fd_out != NULL)
				free(fds->fd_out);
			fds->fd_out = ft_strdup(tmp_fds[i]);
		}
		i++;
	}
	if (fds->fd_in == NULL)
		fds->in = -1;
	if (fds->fd_out == NULL)
		fds->out = -1;
}
