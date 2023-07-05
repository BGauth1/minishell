/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:58:15 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/05 15:12:52 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status;

static int	ft_mini_exec(t_mishell *mish)
{
	if (synthax_check(mish->full_cmd))
	{
		get_cmds(mish);
		mish->files->tab_path = ft_get_tab_path(*mish->files);
		if (g_status != 130)
		{
			ft_call_pipex(mish);
			ft_free_cmds(mish);
		}
		else
			free(mish->full_cmd);
		ft_free_tab(mish->files->tab_path);
	}
	return (0);
}

static int	ft_prompt_parsing(t_mishell *mish)
{
	char	*prompt;
	char	*tmp;

	if (getcwd(mish->path, sizeof(mish->path)) == NULL)
		exit (1);
	prompt = ft_strjoin(mish->path, "$ ");
	tmp = ft_readline(prompt);
	free(prompt);
	if (!empty_str(tmp))
	{
		mish->full_cmd = normalize_str(tmp, mish->files);
		g_status = 0;
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

	(void)argc;
	(void)argv;
	g_status = 0;
	ft_init_tab_env(env, &mish);
	signal_maj_outfork();
	while (1)
	{
		if (ft_prompt_parsing(&mish) == 1)
			continue ;
		signal_maj_outfork();
		unlink(".heredoc");
	}
	ft_free_files(&mish);
	free(mish.full_cmd);
}
