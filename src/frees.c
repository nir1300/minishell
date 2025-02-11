/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:59:03 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 13:01:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_cmd(t_cmd *cmd)
{
    if (!cmd) return;

    int i;
    
    i = 0;
    if (cmd->args)
    {
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
    }
    free(cmd);
}

void exit_minishell(t_minishell *shell, int exit_code)
{
    // Restore standard file descriptors
    if (shell->env)
        free_env(shell->env);
    if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
        perror("Failed to restore stdin");
    if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
        perror("Failed to restore stdout");
    close(shell->stdin_backup);
    close(shell->stdout_backup);
    if (shell->input)
        free(shell->input);
    if (shell->cmds)
        free_cmd(shell->cmds);
    if (shell->jobs)
        free_jobs(shell->jobs);
    rl_clear_history();
    exit(exit_code);
}

void free_jobs(t_job *jobs)
{
    t_job *current;
    t_job *next;

    current = jobs;
    while (current)
    {
        next = current->next;
        // Free the job structure itself
        free(current);
        current = next;
    }
}

void free_env(char **env)
{
    int i;
    if (!env)
        return;
    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}

void cleanup_minishell(t_minishell *shell)
{
    // Restore standard file descriptors
    if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
        perror("Failed to restore stdin");
    if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
        perror("Failed to restore stdout");

    // Close backup file descriptors
    close(shell->stdin_backup);
    close(shell->stdout_backup);

    // Free any remaining allocated memory
    if (shell->input)
        free(shell->input);
    // Free command structures if any
    if (shell->cmds)
        free_cmd(shell->cmds);
    // Free job structures if any
    if (shell->jobs)
        free_jobs(shell->jobs);
    // Clear readline history
    rl_clear_history();
}

void free_tokens(t_token *tokens)
{
    t_token *current = tokens;
    t_token *next;

    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

void free_ast(t_ast_node *root)
{
    if (!root) return;

    free_ast(root->left);
    free_ast(root->right);
    free(root);
}