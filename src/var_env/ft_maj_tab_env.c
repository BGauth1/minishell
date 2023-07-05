/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maj_tab_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:51:11 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/05 14:41:17 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_new_old_pwd(t_files *files, char *name)
{
	int		i;
	int		len;
	char	*val;

	i = 0;
	while (files->tab_var_env[i])
	{
		if (ft_strncmp(files->tab_var_env[i], name, 4) == 0)
		{
			len = ft_strlen(files->tab_var_env[i]);
			val = ft_substr(files->tab_var_env[i], 4, len - 4);
			return (val);
		}
		i++;
	}
	return (NULL);
}

int	maj_tab_env_oldpwd(t_files *files)
{
	char	*buf;
	char	*val;
	char	*tmp;
	char	*name;

	val = find_new_old_pwd(files, "PWD=");
	tmp = ft_strdup("OLDPWD=");
	if (!tmp)
		exit (1);
	buf = ft_strjoin_loop(tmp, val);
	if (val)
		free(val);
	name = ft_strdup("OLDPWD");
	if (!name)
		exit (1);
	switch_env(files, name, buf);
	free(buf);
	return (0);
}

int	maj_tab_env_pwd(t_files *files)
{
	char	*pwd;
	char	*tmp;
	char	*name;

	pwd = malloc(sizeof(char *) * 1024);
	if (pwd == NULL)
		exit (1);
	if (getcwd(pwd, 1024) == NULL)
	{
		free(pwd);
		exit (1);
	}
	tmp = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (tmp == NULL)
		exit (1);
	name = ft_strdup("PWD");
	if (env_var_found(files->tab_var_env, name, name) == 0)
	{
		free(name);
		ft_realloc_tab_env(files, tmp);
	}
	else
		switch_env(files, name, tmp);
	free(tmp);
	return (0);
}
