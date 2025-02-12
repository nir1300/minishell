/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:58:56 by vagarcia          #+#    #+#             */
/*   Updated: 2025/02/12 13:06:37 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to check if a character is a special shell operator
bool	is_special_char(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>' || c == '('
		|| c == ')');
}

// Helper function to check if a character is whitespace
bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/* Main lexer function.
   It loops through the input string, skipping whitespace,
   and calls the appropriate helper to build tokens.
   Returns a linked list of tokens or NULL on error. */
t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		i;

	head = NULL;
	current = NULL;
	new_token = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		if (is_whitespace((unsigned char)input[i]))
			i++;
		else if (is_special_char(input[i]))
			new_token = handle_special_char(input, &i);
		else if (input[i] == '"' || input[i] == '\'')
			new_token = handle_quoted_string(input, &i);
		else
			new_token = handle_regular_token(input, &i);
		if (new_token == NULL)
			return (free_tokens(head), NULL);
		if (head == NULL)
		{
			head = new_token;
			current = new_token;
		}
		else
		{
			current->next = new_token;
			current = new_token;
		}
	}
	return (head);
}
