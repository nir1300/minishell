/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:08:00 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 13:09:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd *create_command_node(char **args)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd) {
        perror("parser: allocation error");
        exit(EXIT_FAILURE);
    }
    cmd->args = args;
    cmd->next = NULL;
    return cmd;
}

void append_command(t_cmd **cmd_list, t_cmd *new_cmd)
{
    t_cmd *current;

    if (!*cmd_list) {
        *cmd_list = new_cmd;
    } else {
        current = *cmd_list;
        while (current->next) {
            current = current->next;
        }
        current->next = new_cmd;
    }
}


