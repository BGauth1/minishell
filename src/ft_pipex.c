/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:47:51 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/25 20:54:20 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	ft_open_fd_in(t_mishell mish, t_files files)
{
	int	op;

	op = -2;
//	if (here_doc)//
//		op = .here_doc;// normalement .here_doc est deja dans fd_in a voir
	op = open(files.fd_in, O_RDONLY);
	return (op);
}

int	ft_open_fd_out(t_mishell mish, t_files files)
{
	int	op;

	op = open(files.fd_out, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (files.out == 1)
		op = open(files.fd_out, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		op = open(files.fd_out, O_RDWR | O_CREAT | O_TRUNC, 0644);	
	return (op);
}

static void		ft_dup(int fd_in, int *fd, t_files files, t_mishell mish)
{
	dup2(fd_in, 0);
	close(fd_in);
	close(fd[0]);
	if (files.pos_cmd == mish.nb_cmds - 1 && files.fd_out != NULL)
	{
		close(fd[1]);
		fd[1] = ft_open_fd_out(mish, files);
	}
	dup2(fd[1], 1);
	close(fd[1]);
}

//ft_exec_cmd en cours 
static int		ft_fork(t_mishell mish, t_files files, int fd_in, int *fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		ft_dup(fd_in, fd, files, mish);
		ft_exec_cmd(mish, files);
	}
	if (files.pos_cmd == mish.nb_cmds - 1) //a verif si dernier cmd pipe si oui close
		close (fd[0]);
	waitpid(pid, NULL, 0);
	return (0);
}

static int	ft_pipe(t_mishell mish, t_files files, int fd_in)
{
	int	fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipe"); //erreur de fct
		exit (1);
	}
	if (files.fd_in == NULL && fd_in == -1)
		fd_in = fd[0];
	//gestion close here_doc voir si implementer
	ft_fork(mish, files, fd_in, fd);
	close(fd[1]);
	close(fd_in);
	return (fd[0]);
}

int	ft_call_pipex(t_mishell mish, t_files *files)
{
	int	fd_in;

	files->pos_cmd = 0;
	fd_in = ft_open_fd_in(mish, *files);
	while (files->pos_cmd < mish.nb_cmds - 1)
	{
		if (check_built_no_fork(mish.cmds[files->pos_cmd].c, files) == 0)
			fd_in = ft_pipe(mish, *files, fd_in);
		files->pos_cmd++;
	}
	ft_pipe(mish, *files, fd_in);
	close(fd_in);
	return (0);
}

int	main(void)
{
	t_mishell	mish;
	t_files	files;
	char	*str;
	int	i = 0;
	int	j = 0;

	str = "ls -l | grep .txt > test.c";

//parsing et init pour test //
	mish.full_cmd = normalize_str(str);
	get_cmds(&mish);
	files = parsing_fd(str);

//nvx init necesssaire pour pipe // verif builtin here
	files.tab_path = ft_get_tab_path(files);
	while (j < mish.nb_cmds)
	{
		if (check_if_cmd_built(mish.cmds[j]) == 0)
			ft_init_path_cmd(&mish, files, j);
		else
			mish.cmds[j].path = NULL;
		j++;
	}

//pipex en test //
	ft_call_pipex(mish, &files);

	j = 0;
	while (mish.cmds[j].c)
	{
		i = 0;
		while (mish.cmds[j].c[i])
		{
			printf("\"%s\" ", mish.cmds[j].c[i]);
			i++;
		}
		printf("\n");
		j++;
	}
	printf("%d\n", mish.nb_cmds);
	return (0);
}
/*

"ls" "-l" 
"grep" ".txt" 
"cat" ">" "saucisse" 
"cat" 
"cat" 
"grep" "ls" 

6

*/
