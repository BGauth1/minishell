/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:27:42 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/05 17:37:32 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*has_here_doc(char *s, int nb_cmds)
{
	int	*here_doc;
	int	n;
	int	i;

	n = 0;
	i = 0;
	here_doc = malloc(nb_cmds * sizeof(int));
	while (n < nb_cmds)
	{
		here_doc[n] = 0;
		n++;
	}
	n = 0;
	while (n < nb_cmds && s[i])
	{
		if (s[i] == '|' && !ft_betweenquotes(s, i))
			n++;
		else if (s[i] == '<' && s[i + 1] == '<' && !ft_betweenquotes(s, i))
		{
			here_doc[n] = 1;
			i++;
		}
		i++;
	}
	return (here_doc);
}

static char	**ft_init_struct_cmds(t_mishell *m)
{
	int		i;
	char	**tmp;

	i = 0;
	m->full_cmd = ft_handle_var_env(m->full_cmd, *m->files);
	g_status = 0;
	tmp = ft_split_minishell(m->full_cmd, '|');
	while (tmp[i])
		i++;
	m->nb_cmds = i;
	m->here_doc = has_here_doc(m->full_cmd, m->nb_cmds);
	m->cmds = malloc((m->nb_cmds + 1) * sizeof(t_cmd));
	m->cmds[m->nb_cmds].c = NULL;
	return (tmp);
}

static int	check_signal_here(char **tmp2, t_mishell *mish)
{
	if (g_status == 130)
	{
		ft_free_str(tmp2);
		free(mish->cmds);
		return (1);
	}
	return (0);
}

void	get_cmds(t_mishell *m)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tmp2;

	tmp = ft_init_struct_cmds(m);
	i = -1;
	while (++i < m->nb_cmds)
	{
		m->cmds[i].here_doc = m->here_doc[i];
		tmp2 = ft_split_minishell(tmp[i], ' ');
		j = -1;
		ft_heredoc(tmp2);
		if (check_signal_here(tmp2, m) == 1)
			break ;
		m->cmds[i].fds = parsing_fd(tmp2);
		m->cmds[i].c = ft_remove_redirections(tmp2);
		while (m->cmds[i].c[++j])
			m->cmds[i].c[j] = ft_remove_quotes(m->cmds[i].c[j]);
		m->cmds[i].path = NULL;
	}
	ft_free_str(tmp);
	free(m->here_doc);
}
