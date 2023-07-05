/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:51:50 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/05 15:59:26 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_status_exec(t_mishell *m)
{
	if (m->cmds[m->pos_cmd].path == NULL && \
		check_if_cmd_built(m->cmds[m->pos_cmd]) == 0)
		g_status = 127;
	else if (m->cmds[m->pos_cmd].fds->err == 1)
		g_status = 1;
}

int	open_fdin(t_mishell *m, int fd_in)
{
	int	op;

	op = -1;
	if (fd_in > 0)
		close(fd_in);
	if (m->cmds[m->pos_cmd].fds->fd_in)
		op = open(m->cmds[m->pos_cmd].fds->fd_in, O_RDONLY);
	return (op);
}

int	open_fdout(t_fds fds)
{
	int	op;

	op = -1;
	if (fds.out == 1)
		op = open(fds.fd_out, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (fds.out == 0)
		op = open(fds.fd_out, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (op);
}

int	ft_check_pipe_and_exit(t_mishell *m)
{
	if (m->nb_cmds > 1 && check_if_cmd_built(m->cmds[m->nb_cmds - 1]) == 3)
		return (1);
	return (0);
}

int	ft_init_tab_pid(t_mishell *m)
{
	m->pos_cmd = 0;
	m->pid = NULL;
	m->pid = (pid_t *)malloc(sizeof(pid_t) * m->nb_cmds);
	if (m->pid == NULL)
		exit (1);
	return (0);
}
