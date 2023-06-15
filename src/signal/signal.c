/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:48:56 by lamasson          #+#    #+#             */
/*   Updated: 2023/06/12 13:36:50 by lamasson         ###   ########.fr       */
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

void	sigint_outfork(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	signal_maj_outfork(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sigint_outfork);
}

int	ft_fork(void)
{
	int	pid;
	int	status;
	char	*buf;

	buf = malloc(sizeof(char) * 1024);
	pid = fork();
	signal(SIGQUIT, sigquit_fork);
	if (pid == 0)
	{
		printf("i'm fork\n");
		while (read(0, buf, sizeof(buf)) != 0)
		{
		}	
	}
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	else
		printf("error\n");
	return (0);
}
/*
int	main(void)
{
	//char	*buf;

	g_status = -1;
	//buf = malloc(sizeof(char) * 1024);
	

	signal(SIGINT, sigint_outfork);
	signal(SIGQUIT, SIG_IGN);
	//while (read(0, buf, sizeof(buf)) != 0)
	//{
		ft_fork();
	//	if (g_status >= 0)
	//		break ;
	//}
	//printf(" stat = %d\n", g_status);
	return (0);
}*/
