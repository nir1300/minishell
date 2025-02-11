/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:08:10 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 12:56:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *create_token(char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
    {
        perror("lexer: allocation error");
        exit(EXIT_FAILURE);
    }
    token->value = ft_strdup(value);
    if (!token->value)
    {
        perror("lexer: allocation error");
        exit(EXIT_FAILURE);
    }
    token->next = NULL;
    return token;
}

t_token *lexer(char *input)
{
    t_token *head;
    t_token *current;
    t_token *new_token;
    char *token_value;

    current = NULL;
    head = NULL;
    token_value = ft_strtok(input, TOKEN_DELIMITERS);
    while (token_value != NULL)
    {
        new_token = create_token(token_value);
        if (!new_token)
        {
            perror("lexer: allocation error");
            exit(EXIT_FAILURE);
        }
        if (!head)
            head = new_token;
        else
            current->next = new_token;
        current = new_token;
        token_value = ft_strtok(NULL, TOKEN_DELIMITERS);
    }
    return (head);
}
