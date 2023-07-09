/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:42:56 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/09 15:27:41 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_parse_tab_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_error_env(char *c, int g)
{
	if (g == 125)
	{
		ft_putstr_fd("env: invalid option: ", 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("\n", 2);
		g_status = 125;
	}
	if (g == 127)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		g_status = 127;
	}
}

static int	ft_parse_env(char **c)
{
	int	len;

	len = ft_tablen(c);
	if (len > 1)
	{
		if (c[1][0] == '-')
		{
			ft_error_env(c[1], 125);
			return (1);
		}
		else
		{
			ft_error_env(c[1], 127);
			return (1);
		}
	}
	return (0);
}

int	ft_env(t_files files, char **c)
{
	int	i;

	i = 0;
	if (!files.tab_var_env)
		return (1);
	if (ft_parse_env(c) == 1)
		return (1);
	while (files.tab_var_env[i])
	{
		if (ft_parse_tab_name(files.tab_var_env[i]) == 0)
			printf("%s\n", files.tab_var_env[i]);
		i++;
	}
	return (0);
}
