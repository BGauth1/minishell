/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:54:31 by gbertet           #+#    #+#             */
/*   Updated: 2023/06/20 14:56:06 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

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

static char	*ft_parsing_exit(t_mishell *m)
{
	int		i;
	char	*arg;
	int		len;

	i = 0;
	arg = m->cmds[m->pos_cmd].c[1];
	len = ft_strlen(arg);
	if ((len >= 20 && ft_strncmp(arg, "-9223372036854775809", len + 1) >= 0) \
		|| (len >= 19 && ft_strncmp(arg, "9223372036854775808", len + 1) >= 0))
		len = -1;
	while (arg[i] != '\0')
	{
		if ((ft_isdigit(arg[i]) == 0 && arg[i] != '-') || len == -1)
		{
			g_status = 2;
			printf("minishell: exit: %s: numeric argument required\n", arg);
			return (NULL);
		}
		i++;
	}
	return (arg);
}

int	ft_exit(t_mishell *m)   
{
	int		nb_arg;
	char	*stat;

	nb_arg = ft_tablen(m->cmds[m->pos_cmd].c);
	stat = NULL;
	if (nb_arg > 1)
		stat = ft_parsing_exit(m);
	if (nb_arg > 2 && stat != NULL)
	{
		g_status = 1;
		printf("minishell: exit: too many arguments\n");
		return (g_status);
	}
	if (stat != NULL)
		g_status = ft_atoi(m->cmds[m->pos_cmd].c[1]);
	if (m)
	{
		ft_free_cmds(m);
		ft_free_files(m);
		free(m->pid);
	} 
	exit (g_status % 256);
}
