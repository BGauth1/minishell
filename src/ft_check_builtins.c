/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:45:48 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/16 15:04:36 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built_no_fork(char **c, t_files *files, t_mishell *m)
{
	size_t	len;

	len = ft_strlen(c[0]) + 1;
	if (c[0] == NULL)
		return (-1);
	else if (ft_strncmp(c[0], "exit", len) == 0)
		ft_exit(m);
	else if (ft_strncmp(c[0], "cd", len) == 0)
		ft_cd(c, files);
	else if (ft_strncmp(c[0], "export", len) == 0)
		ft_export(c, files);
	else if (ft_strncmp(c[0], "unset", len) == 0)
		ft_unset(c, files);
	else
		return (0);
	return (1);
}

int	check_built_fork(char **c, t_files *files)
{
	size_t	len;
	
	len = ft_strlen(c[0]) + 1;
	if (ft_strncmp(c[0], "pwd", len) == 0)
		ft_pwd(c);
	else if (ft_strncmp(c[0], "env", len) == 0)
		ft_env(*files);
	else if (ft_strncmp(c[0], "echo", len) == 0)
		ft_echo(c);
	else 
		return (0);
	return (1);
}

int	check_if_cmd_built(t_cmd cmds)
{
	size_t	len;
	char *c;

	c = cmds.c[0];
	len = ft_strlen(c) + 1;
	if (c == NULL)
		return (-1);
	else if (ft_strncmp(c, "cd", len) == 0)
		return (1);
	else if (ft_strncmp(c, "exit", len) == 0)
		return (1);
	else if (ft_strncmp(c, "export", len) == 0)
		return (1);
	else if (ft_strncmp(c, "unset", len) == 0)
		return (1);
	else if (ft_strncmp(c, "pwd", len) == 0)
		return (2);
	else if (ft_strncmp(c, "env", len) == 0)
		return (2);
	else if (ft_strncmp(c, "echo", len) == 0)
		return (2);
	else
		return (0);
}
