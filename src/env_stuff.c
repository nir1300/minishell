/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:15:32 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 13:15:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **copy_env(char **envp)
{
    int i;
    char **env;

    i = 0;
    while (envp[i])
        i++;
    env = malloc(sizeof(char *) * (i + 1));
    if (!env)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        env[i] = ft_strdup(envp[i]);
        if (!env[i])
        {
            ft_free(env);
            return (NULL);
        }
        i++;
    }
    env[i] = NULL;
    return (env);
}