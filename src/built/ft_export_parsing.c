/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:32:04 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 15:32:53 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_egal(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	env_var_found(char **tab, char *name, char *c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], name, len))
		{
			if (tab[i][len] == '=' && !check_egal(c))
				return (2);
			if (tab[i][len] == '=' || tab[i][len] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_error_export(char *c, int g, char *cmd)
{
	if (g == 1)
	{
		printf("minishell: %s: `%s': not a valid identifier\n", cmd, c);
		g_status = 1;
	}
	else if (g == 2)
	{
		printf("minishell: %s: %s: invalid option\n", cmd, c);
		g_status = 2;
	}
}

int	ft_parse_len(char **c, t_files *files)
{
	int	len;

	len = ft_tablen(c);
	if (len == 1)
	{
		ft_export_no_arg(*files);
		return (0);
	}
	return (1);
}

int	ft_parse_name_export(char **c, int j)
{
	int	i;

	i = 1;
	if (c[j][0] == '-' && j < 2)
	{
		ft_error_export(c[j], 2, c[0]);
		return (2);
	}
	if (ft_isalpha(c[j][0]) != 1)
	{
		ft_error_export(c[j], 1, c[0]);
		return (1);
	}
	while (c[j][i] && c[j][i] != '=')
	{
		if (c[j][i] == '+' && c[j][i + 1] == '=')
			break ;
		if (ft_isalnum(c[j][i]) != 1 && c[j][i] != '_')
		{
			ft_error_export(c[j], 1, c[0]);
			return (1);
		}
		i++;
	}
	return (0);
}
