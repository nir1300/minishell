/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:57:41 by vagarcia          #+#    #+#             */
/*   Updated: 2025/02/12 13:03:33 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input = cmd->output = NULL;
	cmd->next = NULL;
	cmd->log_op = OP_NONE;
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	return (cmd);
}

void add_redirection(t_cmd *cmd, t_redir_type type, char *file)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return;
    redir->type = type;
    redir->file = ft_strdup(file);
    if (type == REDIR_IN || type == REDIR_HEREDOC)
	{
        redir->next = cmd->input;
        cmd->input = redir;
    }
	else
	{
        redir->next = cmd->output;
        cmd->output = redir;
    }
}

// Helper to add an argument to a command
void	add_argument(t_cmd *cmd, char *value)
{
	int	count;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	cmd->args = ft_realloc(cmd->args, count, (count + 2) * sizeof(char *));
	if (!cmd->args)
		return ;
	cmd->args[count] = ft_strdup(value);
	cmd->args[count + 1] = NULL;
}

