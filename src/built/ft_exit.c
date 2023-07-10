/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:54:31 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/10 19:33:50 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if ((ft_isdigit(arg[i]) == 0 && arg[i] != '-' && arg[i] != '+') || \
			len == -1)
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
	printf("exit\n");
	exit (g_status % 256);
}
