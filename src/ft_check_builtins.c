/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:45:48 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/22 15:14:59 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//recupere entrer et renvoie sortit sous condition ? pipe et redirection ? 
//fct en cours
int	ft_check_builtins(char **c, t_files *files)
{
	size_t	len;

	len = ft_strlen(c[0]);
	if (ft_strncmp(c[0], "echo", len) == 0 && len == ft_strlen("echo"))
//		ft_echo(); //with -n option
	if (ft_strncmp(c[0], "cd", len) == 0 && len == ft_strlen("cd"))
		ft_cd(c, files); //with relative or absolute path
	if (ft_strncmp(c[0], "pwd", len) == 0 && len == ft_strlen("pwd"))
		ft_pwd(c); //no option
	if (ft_strncmp(c[0], "export", len) == 0 && len == ft_strlen("export"))
		ft_export(c, files); //no option
	if (ft_strncmp(c[0], "unset", len) == 0 && len == ft_strlen("unset"))
		ft_unset(c, files); //no option
	if (ft_strncmp(c[0], "env", len) == 0 && len == ft_strlen("env"))
		ft_env(*files); //no option no args
	if (ft_strncmp(c[0], "exit", len) == 0 && len == ft_strlen("exit"))
		//ft_exit(); //no option
//	else
//		ft_check_exec_cmd();
	return (0);
}
/*
int	main(int argc, char **argv)
{
	(void) argc;

	ft_check_builtins(argv[1]);
	return (0);
}*/
