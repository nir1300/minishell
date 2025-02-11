/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:07:02 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 12:16:33 by codespace        ###   ########.fr       */
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