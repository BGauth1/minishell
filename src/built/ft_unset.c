/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:00:32 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/21 17:18:13 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_var_env_unset(char **tab, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (tab[i])
	{
		if (ft_strncmp(tab[i], name, len) == 0)
		{
			if (tab[i][len] == '=' || tab[i][len] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **c, t_files *files)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	if (!c[1])
		return (0);
	while (c[++j])
	{
		i = 0;
		if (ft_parse_name_export(c, j))
			continue ;
		if (check_var_env_unset(files->tab_var_env, c[j]) == 0)
			continue ;
		while (ft_strncmp(files->tab_var_env[i], c[j], ft_strlen(c[j])) != 0 \
			&& ft_strlen(c[j]) != ft_strlen(files->tab_var_env[i]))
			i++;
		free(files->tab_var_env[i]);
		while (files->tab_var_env[i] != NULL)
		{
			tmp = files->tab_var_env[i + 1];
			files->tab_var_env[i] = tmp;
			i++;
		}
	}
	return (0);
}
