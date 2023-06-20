/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:47:51 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/19 23:55:06 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_fdin(t_mishell *m, int fd_in)
{
	int	op;
	(void)fd_in;
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

static void	ft_dup(int fd_in , int *fd, t_mishell m)
{
	int	out;

	if (m.cmds[m.pos_cmd].fds->fd_out != NULL)
	{
		close(fd[0]);
		out = open_fdout(*m.cmds[m.pos_cmd].fds);
		dup2(out, 1);
		close(out);
	}
	else if (m.pos_cmd != m.nb_cmds - 1)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
/*	if (!m.cmds[m.pos_cmd].fds->fd_in && check_if_cmd_built(m.cmds[m.pos_cmd]) != 2)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}*/
	if (fd_in > -1)
	{
		close(fd[1]);
		dup2(fd_in, 0);
		close(fd_in);
	}
	close(fd[1]);
	close(fd[0]);
}

static int		ft_fork(t_mishell *mish, int fd_in, int *fd)
{
	g_status = 0;
	signal(SIGINT, sigint_fork);
	signal(SIGQUIT, sigquit_fork);
	mish->pid[mish->pos_cmd] = fork();
	if (mish->pid[mish->pos_cmd] < 0)
		perror("fork");
	if (mish->pid[mish->pos_cmd] == 0)
	{
		ft_dup(fd_in, fd, *mish);
		ft_exec_cmd(mish);
	}
	if (mish->pos_cmd == mish->nb_cmds - 1)
	{	
		close(fd[0]);
		if (mish->cmds[mish->pos_cmd].fds->fd_out != NULL)
			close(fd[1]);
	}
	return (0);
}

//gestion close here_doc voir si implementer
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
	int	status; //error nb

	i = 0;
	status = 0;
	while (i < m->nb_cmds)
	{
		if (m->pid[i] > 0)
			waitpid(m->pid[i], &status, 0);
		if (m->pid[i] > -1 && WIFEXITED(status)) //erreur avec heredoc 
			g_status = WEXITSTATUS(status);
		i++;
	}
	free(m->pid);
}

int	ft_call_pipex(t_mishell *m)
{
	int	fd_in;

	m->pos_cmd = 0;
	fd_in = -1;
	m->pid = NULL; 
	m->pid = (pid_t *)malloc(sizeof(pid_t) * m->nb_cmds);
	if (m->pid == NULL)
		exit (1);
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

/*
int	main(int argc, char **argv, char **env)
{
 	t_mishell	mish;
 	char	*str;
	int	j = 0;
 	(void)argc;
 	(void)argv;

	str = "cat t1.c | < test.c cat | cat >> t.c";

//	parsing et init pour test //

	mish.full_cmd = normalize_str(str);
	get_cmds(&mish);
	ft_init_tab_env(env, &mish);

//	!!!!!! important init path pour cmd non built !!!!!!!!!!//
	
	mish.files->tab_path = ft_get_tab_path(*mish.files);
	while (j < mish.nb_cmds)
	{
		if (check_if_cmd_built(mish.cmds[j]) == 0)
			ft_init_path_cmd(&mish, *mish.files, j);
		else
			mish.cmds[j].path = NULL;
		j++;
	}

//	pipex en test //
	
 	ft_call_pipex(&mish);

//	printf("\n\n");
//	int	i = 0;
//	while (files.tab_var_env[i])
//	{
//		//if (ft_strncmp(files.tab_var_env[i], "PWD", 3) == 0 || ft_strncmp(files.tab_var_env[i], "OLDPWD", 6) == 0)
//		printf("%s\n\n", files.tab_var_env[i]);
//		i++;
//	} retest bultin avec nvx pipex ////////

	ft_free_files(mish.files);
	ft_free_cmds(&mish);
	return (0);
}*/
