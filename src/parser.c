/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:57:29 by vagarcia          #+#    #+#             */
/*   Updated: 2025/02/12 13:10:12 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_meta(t_token *toks, t_cmd *cmds)
{
	if (ft_strcmp(toks->value, "<") == 0)
	{
		if (toks->next)
			return (add_redirection(cmds, REDIR_IN, toks->next->value), 1);
	}
	else if (ft_strcmp(toks->value, ">") == 0)
	{
		if (toks->next)
			return (add_redirection(cmds, REDIR_IN, toks->next->value), 1);
	}
	else if (ft_strcmp(toks->value, ">>") == 0)
	{
		if (toks->next)
			return (add_redirection(cmds, REDIR_IN, toks->next->value), 1);
	}
	else if (ft_strcmp(toks->value, "<<") == 0)
	{
		if (toks->next)
			return (add_redirection(cmds, REDIR_IN, toks->next->value), 1);
	}
	else if (ft_strcmp(toks->value, ";") == 0)
		cmds->log_op = OP_SEMI;
	return (0);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;

	head = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (!current_cmd)
		{
			current_cmd = create_cmd_node();
			if (!head)
				head = current_cmd;
		}
		if (check_meta(tokens, current_cmd) == 0)
			add_argument(current_cmd, tokens->value);
		tokens = tokens->next;
	}
	return (head);
}

