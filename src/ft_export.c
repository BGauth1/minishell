/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:59:02 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/27 18:46:40 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rec_var_env(char *str)
{
	int		i;
	char	*rec;

	i = 0;
	while (str[i] != '=')
		i++;
	rec = ft_substr(str, 0, i);
	if (!rec)
		exit (1); // fct de free
	return (rec);
}

void	switch_env(t_files *files, char *name, char *str)
{
	int	i;

	i = 0;
	while (files->tab_var_env[i] != NULL)
	{
		if (ft_strncmp(files->tab_var_env[i], name, ft_strlen(name)) == 0)
			files->tab_var_env[i] = str;
		i++;
	}
	free(name);
}

int	ft_export(char **argv, t_files *files)//(t_minishell ***data) //nom var off change struct ok
{
	char	*name;
	int		i;

	i = 0;
	if (!argv[2])//(!data->cmd[0][1])
	{
		ft_env(files);
		exit (0);
	}
	if (argv[2])//(data->cmd[0][1])
	{
		name = rec_var_env(argv[2]);
		if (getenv(name) != NULL)
		{
			switch_env(files, name, argv[2]);
			return (0);
		}
		free(name);
	}
	while (files->tab_var_env[i] != NULL)
		i++;
	files->tab_var_env[i] = argv[2];
	files->tab_var_env[i + 1] = NULL;
	return (0);
}