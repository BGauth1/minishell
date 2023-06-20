/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:21:26 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/19 23:40:41 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_parent_fork(t_mishell *m)
{
	ft_free_cmds(m);
	ft_free_files(m);
	free(m->pid);
}

static void	ft_free_data_fork(char **cmd, char **env, char *path)
{
	ft_free_str(cmd);
	ft_free_str(env);
	if (path)
		free(path);
}

static int	ft_check_data_before_exec(t_mishell *m, char **env, char **cmd, char *path)
{
	if (!m->cmds[m->pos_cmd].path && !check_if_cmd_built(m->cmds[m->pos_cmd]))
	{
		ft_free_parent_fork(m);
		printf("%s: command not found\n", cmd[0]);
		ft_free_data_fork(cmd, env, path);
		return (1);
	}
	return (0);
}

int	ft_exec_cmd(t_mishell *m)
{
	char	*path = NULL;
	char	**cmd;
	char	**env;

	cmd = ft_strstrdup(m->cmds[m->pos_cmd].c);
	env = ft_strstrdup(m->files->tab_var_env);
	if (ft_check_data_before_exec(m, env, cmd, NULL) == 1)
		exit (127);
	else if (check_built_fork(m->cmds[m->pos_cmd].c, m->files) == 0)
	{
		path = ft_strdup(m->cmds[m->pos_cmd].path);
		ft_free_parent_fork(m);
		if (execve(path, cmd, env) == -1)
		{
			printf("minishell: %s: %s\n", cmd[0], strerror(errno));
			ft_free_data_fork(cmd, env, path);
			exit (126);
		}
	}
	ft_free_parent_fork(m);
	ft_free_data_fork(cmd, env, path);
	exit (g_status);
}
