/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:08:10 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 12:42:13 by codespace        ###   ########.fr       */
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
    token->next = NULL;
    return token;
}

t_token *lexer(char *input)
{
    t_token *head = NULL;
    t_token *current = NULL;
    char *token_value;

    token_value = ft_strtok(input, TOKEN_DELIMITERS);
    while (token_value != NULL) {
        t_token *new_token = create_token(token_value);
        if (!head) {
            head = new_token;
        } else {
            current->next = new_token;
        }
        current = new_token;
        token_value = ft_strtok(NULL, TOKEN_DELIMITERS);
    }
    return head;
}
