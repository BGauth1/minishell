/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:08:33 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 15:24:15 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_user_path(char **c)
{
	char	*user;
	char	*path;

	user = ft_substr(c[1], 1, ft_strlen(c[1]) - 1);
	if (!user)
		exit (1);
	path = ft_strjoin("/nfs/homes/", user);
	if (!path)
	{
		free(user);
		exit (1);
	}
	free(user);
	if (chdir(path) != 0)
	{
		printf("minishell: %s: %s: %s\n", c[0], path, strerror(errno));
		g_status = 1;
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

static int	parsing_cd(char **c)
{
	int	len;

	len = ft_tablen(c);
	if (len > 2)
	{
		printf("minishell: %s: too many arguments\n", c[0]);
		g_status = 1;
	}
	else if (len > 1 && c[1][0] == '-')
		ft_error_export(c[1], 2, c[0]);
	else
		return (0);
	return (1);
}

static char	*ft_home_directory(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
		exit (1);
	return (path);
}

int	ft_cd(char **c, t_files *files)
{
	char	*path;

	path = c[1];
	if (parsing_cd(c) != 0)
		return (1);
	if (path == NULL || ft_strncmp(path, "~", 2) == 0)
	{
		path = ft_home_directory();
		if (!path)
			return (1);
	}
	if (ft_strncmp(path, "~", 1) == 0 && ft_strlen(path) > 1)
		ft_user_path(c);
	else if (chdir(path) != 0)
	{
		printf("minishell: %s: %s: %s\n", c[0], c[1], strerror(errno));
		g_status = 1;
		return (1);
	}
	maj_tab_env_oldpwd(files);
	maj_tab_env_pwd(files);
	return (0);
}
