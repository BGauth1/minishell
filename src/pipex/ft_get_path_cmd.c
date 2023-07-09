/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:55:00 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 13:48:39 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_access_path(char **tab_path)
{
	int		i;
	char	*path;

	i = 0;
	while (tab_path[i] != NULL)
	{
		if (access(tab_path[i], X_OK) == 0)
		{
			path = ft_strdup(tab_path[i]);
			if (!path)
				exit (1);
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	ft_init_path_cmd(t_mishell *mish, t_files files, int j)
{
	char	**tab_tmp;
	int		i;
	int		len;

	len = ft_tablen(files.tab_path);
	tab_tmp = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (files.tab_path[i] != NULL)
	{
		tab_tmp[i] = ft_strjoin_path(files.tab_path[i], mish->cmds[j].c[0]);
		if (!tab_tmp[i])
		{
			ft_free_n_tab(tab_tmp, i);
			exit (1);
		}
		i++;
	}
	tab_tmp[i] = NULL;
	mish->cmds[j].path = ft_access_path(tab_tmp);
	ft_free_tab(tab_tmp);
}

char	**ft_get_tab_path(t_files files)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (files.tab_var_env[i] && ft_strncmp(files.tab_var_env[i], "PATH=", 5))
			i++;
	if (files.tab_var_env[i] == NULL)
		return (NULL);
	tmp = ft_substr(files.tab_var_env[i], 5, ft_strlen(files.tab_var_env[i]));
	if (!tmp)
		exit (1);
	path = ft_split(tmp, ':');
	free(tmp);
	if (!path)
		exit (1);
	return (path);
}

static int	check_path_dir(char *c)
{
	if ((c[0] == '.' && c[1] == '/') || c[0] == '/')
		return (1);
	return (0);
}

void	ft_cmd_path_ready(t_mishell *mish)
{
	int	j;

	j = 0;
	while (j < mish->nb_cmds)
	{
		if (check_if_cmd_built(mish->cmds[j]) == 0 && \
			mish->cmds[j].c[0][0] != '\0')
		{
			if (mish->files->tab_path != NULL)
				ft_init_path_cmd(mish, *mish->files, j);
			if (!mish->cmds[j].path && check_path_dir(mish->cmds[j].c[0]) == 1)
			{
				if (access(mish->cmds[j].c[0], F_OK) == 0)
					mish->cmds[j].path = ft_strdup (mish->cmds[j].c[0]);
			}
		}
		else
			mish->cmds[j].path = NULL;
		j++;
	}
}
