/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:58:15 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/10 15:39:15 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

static int	ft_mini_exec(t_mishell *mish)
{
	char	**tmp;

	if (synthax_check(mish->full_cmd))
	{
		tmp = ft_init_struct_cmds(mish);
		if (!tmp)
			return (1);
		get_cmds(mish, tmp);
		mish->files->tab_path = ft_get_tab_path(*mish->files);
		if (g_status != 130)
		{
			ft_call_pipex(mish);
			ft_free_cmds(mish);
		}
		else
			free(mish->full_cmd);
		if (mish->files->tab_path)
			ft_free_tab(mish->files->tab_path);
	}
	return (0);
}

static int	ft_signal_parent(void)
{
	if (g_status == -13)
	{
		g_status = 130;
		return (1);
	}
	return (0);
}

static char	*ft_prompt(t_mishell *mish)
{
	char	path[1024];
	char	*prompt;

	if (env_var_found(mish->files->tab_var_env, "PWD", "PWD") > 0)
		prompt = ft_strjoin(mish->path, "$ ");
	else
	{
		if (getcwd(path, sizeof(path)) == NULL)
			exit (1);
		prompt = ft_strjoin(path, "$ ");
	}
	free(mish->path);
	return (prompt);
}

static int	ft_prompt_parsing(t_mishell *mish)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_prompt(mish);
	tmp = ft_readline(prompt);
	free(prompt);
	if (ft_signal_parent() == 1)
		return (1);
	else if (!empty_str(tmp))
	{
		mish->full_cmd = normalize_str(tmp, mish->files);
		free(tmp);
		if (empty_str(mish->full_cmd))
		{
			free(mish->full_cmd);
			return (1);
		}
		ft_mini_exec(mish);
	}
	else
		free(tmp);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mishell	mish;
	char		*pwd;

	(void)argc;
	(void)argv;
	g_status = 0;
	ft_init_tab_env(env, &mish);
	while (1)
	{
		signal_maj_outfork();
		pwd = ft_strdup("$PWD");
		mish.path = ft_handle_var_env(pwd, *mish.files);
		if (mish.path)
			mish.path = ft_remove_quotes(mish.path);
		if (ft_prompt_parsing(&mish) == 1)
			continue ;
		unlink(".heredoc");
	}
	free(mish.path);
	ft_free_files(&mish);
	free(mish.full_cmd);
}
