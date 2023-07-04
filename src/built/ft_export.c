/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:59:02 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/03 17:31:02 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_realloc_tab_env(t_files *files, char *str) //envoyer addr & de files dans proto
{
	int		len;
	int		i;
	int		j;
	char	**buf_tab;

	i = 0;
	len = ft_tablen(files->tab_var_env);
	buf_tab = malloc(sizeof(char *) * (len + 2)); //new + NULL = 2
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
//utiliser dans unset void si necessaire ou move in unset.c
int	ft_parse_name(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) != 1)
		return (1);
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			break ;
		if (ft_isalnum(str[i]) != 1 && str[i] != '_' && str[i] != '-')
			return (1);
		i++;
	}
	return (0);
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
		if (env_var_found(files->tab_var_env, name, c[i]) == 1)
			switch_env(files, name, c[i]);
		else if (env_var_found(files->tab_var_env, name, c[i]) == 2) //29/06 verif si name bien free ds ce cas
		{
			free(name);
			return (0);
		}
		else
		{
			free(name);
			ft_realloc_tab_env(files, c[i]); 
			return (0);
		}
	}
	return (0);
}
