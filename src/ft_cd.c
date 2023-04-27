/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:08:33 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/27 18:46:40 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//ft_cd en test //ft_readline en test

int ft_cd(char *str)
{
    char    cwd[1024];

    if (chdir(str) != 0)
    {
        perror(str);
        return (1);
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return (1);
    }
    ft_readline(cwd);
    return (0);
}