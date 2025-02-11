/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:14:52 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 14:22:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_minishell(t_minishell *shell, char **envp)
{
    shell->env = copy_env(envp);
    if (!shell->env)
    {
        perror("Failed to copy environment");
        exit(EXIT_FAILURE);
    }
    // Initialize other fields
    shell->exit_status = 0;
    shell->is_interactive = isatty(STDIN_FILENO);
    shell->signal_status = 0;
    shell->input = NULL;
    shell->cmds = NULL;
    shell->jobs = NULL;
    shell->last_job_id = 0;
    shell->stdin_backup = dup(STDIN_FILENO);
    shell->stdout_backup = dup(STDOUT_FILENO);
    if (shell->stdin_backup == -1 || shell->stdout_backup == -1)
    {
        perror("Failed to backup file descriptors");
        exit(EXIT_FAILURE);
    }
    //setup_signals();
}



void minishell_loop(t_minishell *shell)
{
    t_token *tokens;
    t_ast_node *ast;
    char *prompt = "Minishell-> ";

    while (1)
    {
        shell->input = readline(prompt);
        if (!shell->input || ft_strcmp(shell->input, "exit") == 0)
        {
            write(1, "exit\n", 5);
            exit_minishell(shell, 0);
            break;
        }
        if (*(shell->input))
            add_history(shell->input);
        tokens = lexer(shell->input);
        if (!tokens)
        {
            free(shell->input);
            continue;
        }
        ast = parser(tokens);
        if (!ast)
        {
            free(shell->input);
            free_tokens(tokens);
            continue;
        }
        print_ast(ast, 0);
        free_ast(ast);
        free_tokens(tokens);
        free(shell->input);
    }
    rl_clear_history();
}