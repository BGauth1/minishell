/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:59:02 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/05 18:02:05 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_realloc_tab_env(t_files *files, char *str)
{
	int		len;
	int		i;
	int		j;
	char	**buf_tab;

	i = 0;
	len = ft_tablen(files->tab_var_env);
	buf_tab = malloc(sizeof(char *) * (len + 2));
	while (files->tab_var_env[i] != NULL)
	{
		buf_tab[i] = ft_strdup(files->tab_var_env[i]);
		free(files->tab_var_env[i]);
		i++;
	}
	free(files->tab_var_env);
	j = 0;
	while (str[j] && str[j] != '=')
	{
		if (str[j] == '+')
			str = remove_char(str, j--);
		j++;
	}
	buf_tab[i] = ft_strdup(str);
	buf_tab[i + 1] = NULL;
	files->tab_var_env = buf_tab;
}

char	*rec_var_env(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '=')
	{
		if (str[i] == '\0' || str[i] == '+')
			break ;
		i++;
	}
	name = ft_substr(str, 0, i);
	if (!name)
		exit (1);
	return (name);
}

void	switch_env(t_files *files, char *name, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (files->tab_var_env[i] != NULL)
	{
		if (ft_strncmp(files->tab_var_env[i], name, ft_strlen(name)) == 0)
		{
			tmp = concat_export(files->tab_var_env[i], str);
			free(files->tab_var_env[i]);
			files->tab_var_env[i] = ft_strdup(tmp);
			free(tmp);
			if (files->tab_var_env[i] == NULL)
			{
				ft_free_tab_env(files);
				free(name);
				exit (1);
			}
			break ;
		}
		i++;
	}
	free(name);
}

int	ft_export(char **c, t_files *files)
{
	char	*name;
	int		i;
	int		b;

	i = 0;
	if (ft_parse_len(c, files) == 0)
		return (0);
	while (c[++i])
	{
		b = ft_parse_name_export(c, i);
		if (b == 2)
			return (0);
		else if (b == 1)
			continue ;
		name = rec_var_env(c[i]);
		if (!name)
			return (1);
		b = env_var_found(files->tab_var_env, name, c[i]);
		if (!ft_env_cases(files, name, c[i], b))
			return (0);
	}
	return (0);
}
