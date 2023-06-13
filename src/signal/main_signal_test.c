/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:58:15 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/12 19:05:32 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_mishell mish;
	char *prompt;
	char *tmp;

	if (getcwd(mish.path, sizeof(mish.path)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_init_tab_env(env, &mish);
	mish.files->tab_path = ft_get_tab_path(*mish.files);
	signal(SIGINT, sigint_outfork);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = ft_strjoin(mish.path, "$ ");
		tmp = ft_readline(prompt);
		free(prompt);
		if (!empty_str(tmp))
		{
			mish.full_cmd = normalize_str(tmp, mish.files);
			if (synthax_check(mish.full_cmd))
			{
				get_cmds(&mish);
				ft_call_pipex(&mish);
				if (!ft_strncmp(mish.full_cmd, "exit", 4))
					ft_exit(&mish);
				ft_free_cmds(&mish);
			}
		}
		free(tmp);
	}
	free(tmp);
	free(prompt);
	ft_free_files(&mish);
	free(mish.full_cmd);
}
