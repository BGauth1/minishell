/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:32:04 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/21 16:50:36 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_export(char *c, int g, char *cmd)
{
	if (g == 1)
	{
		printf("minishell: %s: `%s': not a valid identifier\n", cmd, c);	
		g_status = 1;
	}
	else if (g == 2)
	{
		printf("minishell: %s: invalid option\n", cmd);
		g_status = 2;
	}
}

int	check_egal(char *c)
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
	if (c[j][0] == '-')
	{
		ft_error_export(c[j], 2, c[0]);
		return (1);
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
	return(0);
}
