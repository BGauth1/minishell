/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:58:15 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/15 18:31:33 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status;

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_mishell mish;
	char *prompt;
	char *tmp;

	g_status = 0;
	ft_init_tab_env(env, &mish);
	signal(SIGINT, sigint_outfork);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (getcwd(mish.path, sizeof(mish.path)) == NULL)
			exit (1);
		prompt = ft_strjoin(mish.path, "$ ");
		tmp = ft_readline(prompt);
		free(prompt);
		if (!empty_str(tmp))
		{
			mish.full_cmd = normalize_str(tmp, mish.files);
			free(tmp);
			if (empty_str(mish.full_cmd))
			{
				free(mish.full_cmd);
				continue ;
			}
			if (synthax_check(mish.full_cmd))
			{
				get_cmds(&mish);
				mish.files->tab_path = ft_get_tab_path(*mish.files);
				ft_call_pipex(&mish);
				ft_free_cmds(&mish);
				ft_free_tab(mish.files->tab_path);
			}
		}
		signal_maj_outfork();
		//ft_free_tab(mish.files->tab_path);
		unlink(".heredoc");
	}
	free(tmp);
	free(prompt);
	ft_free_files(&mish);
	free(mish.full_cmd);
}
