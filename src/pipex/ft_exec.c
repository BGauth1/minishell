/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:21:26 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/14 18:22:34 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_cmd(t_mishell *mish)
{
	int	b;
	char *path;
	char	**cmd;
	char	**env;

	b = check_if_cmd_built(mish->cmds[mish->pos_cmd]);
	cmd = ft_strstrdup(mish->cmds[mish->pos_cmd].c);
	env = ft_strstrdup(mish->files->tab_var_env);
	if (mish->cmds[mish->pos_cmd].path == NULL && b == 0)
	{
		ft_free_cmds(mish);
		ft_free_files(mish);
		free(mish->pid);
		printf("%s: command not found\n", cmd[0]);
		ft_free_str(cmd);
		ft_free_str(env);
		exit (1);
	}
	else if (check_built_fork(mish->cmds[mish->pos_cmd].c, mish->files) == 0)
	{
		path = ft_strdup(mish->cmds[mish->pos_cmd].path);
		ft_free_cmds(mish);
		ft_free_files(mish);
		free(mish->pid);
		if (execve(path, cmd, env) == -1)
		{
			printf("minishell: %s: %s\n", cmd[0], strerror(errno));
			exit (1);
		}
	}
	ft_free_cmds(mish);
	ft_free_files(mish);
	ft_free_str(cmd);
	ft_free_str(env);
	free(mish->pid);
	exit (0);
}
