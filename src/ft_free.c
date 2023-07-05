/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:24:01 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/05 15:25:34 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* free le nb de ligne choisi ds le cas
 * d'une erreur de malloc*/

void	ft_free_n_tab(char **tab, int n)
{
	while (n >= 0)
	{
		free(tab[n]);
		n--;
	}
	free(tab);
}

void	ft_free_str(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_free_cmds(t_mishell *m)
{
	int	i;

	i = 0;
	if (m->full_cmd)
		free(m->full_cmd);
	while (m->cmds[i].c)
	{
		ft_free_str(m->cmds[i].c);
		free(m->cmds[i].path);
		free(m->cmds[i].fds->fd_in);
		free(m->cmds[i].fds->fd_out);
		free(m->cmds[i].fds);
		i++;
	}
	free(m->cmds);
}

void	ft_free_files(t_mishell *mish)
{
	ft_free_tab(mish->files->tab_path);
	ft_free_tab(mish->files->tab_var_env);
	free(mish->files);
}
