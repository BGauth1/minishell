/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:47:51 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/05 15:56:39 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_dup(int fd_in, int *fd, t_mishell m, int out)
{
	if (m.cmds[m.pos_cmd].fds->fd_out != NULL)
	{
		dup2(out, 1);
		close(out);
	}
	else if (m.pos_cmd != m.nb_cmds - 1)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (fd_in > -1 && check_if_cmd_built(m.cmds[m.pos_cmd]) == 0)
	{
		close(fd[1]);
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (fd_in > 1 && check_if_cmd_built(m.cmds[m.pos_cmd]) != 0)
		close(fd_in);
	close(fd[1]);
	close(fd[0]);
}

static int	ft_fork(t_mishell *mish, int fd_in, int *fd)
{
	int	out;

	out = 0;
	g_status = 0;
	signal(SIGINT, sigint_fork);
	signal(SIGQUIT, sigquit_fork);
	if (mish->cmds[mish->pos_cmd].fds->fd_out != NULL)
		out = open_fdout(*mish->cmds[mish->pos_cmd].fds);
	mish->pid[mish->pos_cmd] = fork();
	if (mish->pid[mish->pos_cmd] < 0)
		perror("fork");
	if (mish->pid[mish->pos_cmd] == 0)
	{
		ft_dup(fd_in, fd, *mish, out);
		ft_exec_cmd(mish);
	}
	if (out > 0)
		close(out);
	if (mish->pos_cmd == mish->nb_cmds - 1)
	{	
		close(fd[0]);
		if (mish->cmds[mish->pos_cmd].fds->fd_out != NULL)
			close(fd[1]);
	}
	return (0);
}

static int	ft_pipe(t_mishell *m, int fd_in)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	ft_fork(m, fd_in, fd);
	ft_check_status_exec(m);
	close(fd[1]);
	if (fd_in > 0)
		close(fd_in);
	return (fd[0]);
}

void	waitpid_tab(t_mishell *m)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < m->nb_cmds)
	{
		if (m->pid[i] > 0)
			waitpid(m->pid[i], &status, 0);
		if (m->pid[i] > -1 && WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		i++;
	}
	free(m->pid);
}

int	ft_call_pipex(t_mishell *m)
{
	int	fd_in;

	fd_in = -1;
	if (ft_check_pipe_and_exit(m) == 1)
		return (0);
	ft_init_tab_pid(m);
	ft_cmd_path_ready(m);
	while (m->pos_cmd < m->nb_cmds)
	{
		if (m->cmds[m->pos_cmd].fds->fd_in != NULL)
			fd_in = open_fdin(m, fd_in);
		if (check_built_no_fork(m->cmds[m->pos_cmd].c, m->files, m) == 0 \
			&& m->cmds[m->pos_cmd].fds->err != 1)
			fd_in = ft_pipe(m, fd_in);
		else
			m->pid[m->pos_cmd] = -1;
		m->pos_cmd++;
	}
	waitpid_tab(m);
	if (fd_in > 0)
		close(fd_in);
	return (0);
}
