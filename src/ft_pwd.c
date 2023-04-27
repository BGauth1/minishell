/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:02:12 by lamasson          #+#    #+#             */
/*   Updated: 2023/04/27 18:46:40 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
    char    cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return (1);
    }
    printf("%s", cwd);
    return (0);
}