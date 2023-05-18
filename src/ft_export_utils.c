/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:37:41 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/16 19:17:08 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_one_by_one(char **tab, int i)
{
	int	c;

	c = 0;
	while (tab[i][c] && tab[i + 1][c])
	{
		if (tab[i + 1][c] == '=')
			return (0);
		if (tab[i][c] == '=')
			return (1);
		if (ft_strncmp(tab[i], tab[i + 1], c) > 0)
			return (0);
		if (ft_strncmp(tab[i], tab[i + 1], c) < 0)
			return (1);
		if (ft_strncmp(tab[i], tab[i + 1], c) == 0)
			c++;
	}
	return (1);
}

void	ft_sort_tab(char **tab, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i] && tab[i + 1])
	{
		if (ft_one_by_one(tab, i) == 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
			continue ;
		}
		i++;
	}
	i = 1; //don't print "_=cmd" only export with opt -p
	while (i < len)
		printf("declare -x %s\n", tab[i++]);
}

int	ft_export_no_arg(t_files files)
{
	int	len;
	int	i;

	i = 0;
	len = ft_tablen(files.tab_var_env);
	ft_sort_tab(files.tab_var_env, len);
	return (0);
}
