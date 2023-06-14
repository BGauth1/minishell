/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:21:26 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/14 16:50:12 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_cmd(t_mishell mish, t_files files)
{
	int	b;

	b = check_if_cmd_built(mish.cmds[mish.pos_cmd]);
	if (mish.cmds[mish.pos_cmd].path == NULL && b == 0)
	{
		printf("%s: command not found\n", mish.cmds[mish.pos_cmd].c[0]);
		exit (1);
	}
	else if (check_built_fork(mish.cmds[mish.pos_cmd].c, &files) == 0)
	{
		if (execve(mish.cmds[mish.pos_cmd].path, mish.cmds[mish.pos_cmd].c, files.tab_var_env) == -1)
		{
			printf("minishell: %s: %s\n", mish.cmds[mish.pos_cmd].c[0], strerror(errno));
			exit (1);
		}
	}
	exit (0);
}
