/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:51:50 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/15 19:36:33 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_status_exec(t_mishell *m)
{
	if (m->cmds[m->pos_cmd].path == NULL && check_if_cmd_built(m->cmds[m->pos_cmd]) == 0)
		g_status = 127;
	else if (m->cmds[m->pos_cmd].fds->err == 1 || m->cmds[m->pos_cmd].fds->err == 1)
		g_status = 1;
}
