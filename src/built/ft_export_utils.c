/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:09:56 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 15:18:28 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_one_by_one(char **tab, int i)
{
	int	c;

	c = 0;
	while (tab[i][c] && tab[i + 1][c])
	{
		if (ft_strncmp(tab[i], tab[i + 1], c) > 0)
			return (0);
		if (ft_strncmp(tab[i], tab[i + 1], c) < 0)
			return (1);
		if (tab[i][c] == '=')
			return (1);
		if (tab[i + 1][c] == '=')
			return (0);
		if (ft_strncmp(tab[i], tab[i + 1], c) == 0)
			c++;
	}
	return (1);
}

void	ft_print_tab_export(char **tab, int len, int c)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (tab[i][++j] != '\0')
		{
			ft_putchar_fd(tab[i][j], 1);
			if (tab[i][j] == '=' && c == 0)
			{
				ft_putchar_fd('\"', 1);
				c = 1;
			}
		}
		if (c == 1)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		j = 0;
		c = 0;
		if (tab[++i] && tab[i][j] == '_')
			i++;
	}
}

void	ft_sort_tab(char **tab, int len)
{
	int		i;
	int		c;
	char	*tmp;

	i = 0;
	c = 0;
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
	ft_print_tab_export(tab, len, c);
}

int	ft_export_no_arg(t_files files)
{
	int		len;
	int		i;
	char	**tab;

	i = 0;
	len = ft_tablen(files.tab_var_env);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		exit (1);
	while (i < len)
	{
		tab[i] = ft_strdup(files.tab_var_env[i]);
		if (!tab[i])
		{
			ft_free_n_tab(tab, i);
			exit (1);
		}
		i++;
	}
	tab[i] = NULL;
	ft_sort_tab(tab, len);
	ft_free_tab(tab);
	return (0);
}

char	*concat_export(char *env_var, char *str)
{
	int		i;
	int		concat;
	char	*buff;
	char	*res;

	i = -1;
	concat = 0;
	buff = str;
	while (*buff && *buff != '=' )
	{
		if (*buff == '+')
			concat = 1;
		buff++;
	}
	buff++;
	if (concat)
	{
		res = malloc((ft_strlen(env_var) + ft_strlen(buff) + 1) * sizeof(char));
		ft_strlcpy(res, env_var, ft_strlen(env_var) + 1);
		ft_strlcat(res, buff, ft_strlen(res) + ft_strlen(buff) + 1);
	}
	else
		res = ft_strdup(str);
	return (res);
}
