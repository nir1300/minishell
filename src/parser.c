/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:07:02 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 13:11:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast_node *create_ast_node(t_token *token)
{
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node)
    {
        perror("parser: allocation error");
        exit(EXIT_FAILURE);
    }
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return node;
}

t_ast_node *parser(t_token *tokens)
{
    t_ast_node *root = NULL;
    t_ast_node *current = NULL;

    while (tokens)
    {
        t_ast_node *new_node = create_ast_node(tokens);
        if (!root)
            root = new_node;
        else
            current->right = new_node;
        current = new_node;
        tokens = tokens->next;
    }
    return root;
}

t_cmd *parse_logical_operators(t_list **tokens)
{
    t_cmd *cmd_list = NULL;
    t_cmd *cmd;

    while (*tokens)
    {
        cmd = parse_pipeline(tokens);
        append_command(&cmd_list, cmd);
        if (*tokens && (ft_strcmp((*tokens)->content, "&&") == 0 || ft_strcmp((*tokens)->content, "||") == 0))
        {
            *tokens = (*tokens)->next; // Skip the logical operator
        }
    }
    return cmd_list;
}

t_cmd *parse_pipeline(t_list **tokens)
{
    t_cmd *cmd_list = NULL;
    t_cmd *cmd;
    char **args;
    int arg_count;

    while (*tokens && ft_strcmp((*tokens)->content, "|") != 0)
    {
        arg_count = 0;
        args = ft_calloc(sizeof(char *), 64); // Assuming max 64 arguments
        while (*tokens && ft_strcmp((*tokens)->content, "|") != 0)
        {
            args[arg_count++] = (*tokens)->content;
            *tokens = (*tokens)->next;
        }
        args[arg_count] = NULL;
        cmd = create_command_node(args);
        append_command(&cmd_list, cmd);
        if (*tokens && ft_strcmp((*tokens)->content, "|") == 0)
        {
            *tokens = (*tokens)->next; // Skip the "|"
        }
    }
    return cmd_list;
}