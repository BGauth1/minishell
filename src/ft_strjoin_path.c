/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:32:51 by lamasson          #+#    #+#             */
/*   Updated: 2023/05/25 19:58:51 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cat_path(char *s1, char *s2, char *s3)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = '/';
	i++;
	while (s2[y] != '\0')
	{
		s3[i] = s2[y];
		i++;
		y++;
	}
	s3[i] = '\0';
}

char *ft_strjoin_path(char *path, char *cmd)
{
	char	*s3;
	int		len;

	if (!path)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(cmd) + 1;
	s3 = malloc(sizeof(char) * (len + 1));
	if (!s3)
		return (NULL);
	ft_cat_path(path, cmd, s3);
	return (s3);
}
