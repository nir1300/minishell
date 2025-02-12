/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:45:40 by vagarcia          #+#    #+#             */
/*   Updated: 2025/02/12 13:04:33 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = value;
	token->next = NULL;
	return (token);
}

/* Handles special characters.
   Supports multi-character operators ">>" and "<<" only. */

t_token	*handle_special_char(char *input, int *i)
{
	t_token	*token;
	char	*str;

	str = NULL;
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		str = malloc(3);
		if (str == NULL)
			return (NULL);
		str[0] = '>';
		str[1] = '>';
		str[2] = '\0';
		*i = *i + 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		str = malloc(3);
		if (str == NULL)
			return (NULL);
		str[0] = '<';
		str[1] = '<';
		str[2] = '\0';
		*i = *i + 2;
	}
	else
	{
		str = malloc(2);
		if (str == NULL)
			return (NULL);
		str[0] = input[*i];
		str[1] = '\0';
		*i = *i + 1;
	}
	token = create_token(str);
	if (token == NULL)
		free(str);
	return (token);
}

/* Handles quoted strings.
   Returns a token whose value is the quoted substring (without quotes).
   On unmatched quotes, returns NULL. */
t_token	*handle_quoted_string(char *input, int *i)
{
	t_token	*token;
	char	*str;
	char	quote;
	int		start;
	int		len;

	quote = input[*i];
	*i = *i + 1;
	start = *i;
	while (input[*i] != '\0' && input[*i] != quote)
		*i = *i + 1;
	if (input[*i] != quote)
		return (NULL); /* Unmatched quote error */
	len = *i - start;
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, &input[start], len);
	str[len] = '\0';
	*i = *i + 1;
	token = create_token(str);
	if (token == NULL)
		free(str);
	return (token);
}

/* Handles a regular (non‐quoted, non‐operator) token.
   The token continues until whitespace or a special char is found. */
t_token	*handle_regular_token(char *input, int *i)
{
	t_token	*token;
	char	*str;
	int		start;
	int		len;

	start = *i;
	while (input[*i] != '\0' && !isspace((unsigned char)input[*i])
		&& !is_special_char(input[*i]))
		*i = *i + 1;
	len = *i - start;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, &input[start], len);
	str[len] = '\0';
	token = create_token(str);
	if (token == NULL)
		free(str);
	return (token);
}
