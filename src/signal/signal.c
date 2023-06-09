/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:48:56 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/09 16:21:09 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_fork(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_status = 130;
	}
	return ;
}

void	sigquit_fork(int signum)
{
	(void)signum;
	printf("Quit (core dumped)\n");
	g_status = 131;
}

static int	signal_check_readline(void)
{
	return (0);
}

static void	sigint_outfork(int signum)
{
	if (signum == SIGINT)
	{
		g_status = -13;
		rl_done = 1;
	}
	return ;
}

void	signal_maj_outfork(void)
{
	rl_event_hook = signal_check_readline;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sigint_outfork);
}
