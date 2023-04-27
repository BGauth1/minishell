/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:59:02 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/27 20:21:58 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_realloc_tab_env(t_files *files, char *str) //envoyer addr & de files dans proto
{
	int		len;
	int		i;
	char	**buf_tab;

	len = 0;
	i = 0;
	while (files->tab_var_env[len] != NULL)
		len++;
	buf_tab = malloc(sizeof(char *) * (len + 2));
	while (files->tab_var_env[i] != NULL)
	{
		buf_tab[i] = ft_strdup(files->tab_var_env[i]);
		free(files->tab_var_env[i]);
		i++;
	}
	free(files->tab_var_env);
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
		i++;
	name = ft_substr(str, 0, i);
	return (name);
}

void	switch_env(t_files *files, char *name, char *str)
{
	int	i;

	i = 0;
	while (files->tab_var_env[i] != NULL)
	{
		if (ft_strncmp(files->tab_var_env[i], name, ft_strlen(name)) == 0)
		{
			free(files->tab_var_env[i]);
			files->tab_var_env[i] = ft_strdup(str);
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

int	ft_parse_name(char *str)
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

int	ft_export(char *str, t_files *files)//nom var off change struct ok
{
	char	*name;
	int		i;

	i = 0;
	if (!str) //no free puisque conserve tab_env
	{
		ft_env(*files);
		return (0);
	}
	if (ft_parse_name(str) == 1)
		return (0);
	name = rec_var_env(str);
	if (name == NULL)
	{
		ft_free_tab_env(files);
		exit (1);
	}
	if (getenv(name) != NULL)
	{
		switch_env(files, name, str);
		return (0);
	}
	free(name);
	ft_realloc_tab_env(files, str);
	return (0);
}
