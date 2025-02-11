/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:05:17 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 14:08:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _GNU_SOURCE
#include "../includes/minishell.h"

/* Global variable to track the last command status */
volatile sig_atomic_t g_last_exit_status = 0;

/* Signal handler function */
void signal_handler(int signo)
{
    if (signo == SIGINT) // CTRL+C
    {
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signo == SIGQUIT)
        return ;
}

/* Setup signals */
void setup_signal_handlers(void)
{
    struct sigaction sa;
    
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}


/* Main shell loop */
void minishell_loop(t_minishell *shell)
{
    char *input;

    while (1)
    {
        input = readline(generate_prompt(shell));
        if (!input) // CTRL+D (EOF)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            cleanup_minishell(shell);
            exit(shell->exit_status);
        }
        if (*input)
            add_history(input);
        // Process input and execute commands
        shell->exit_status = execute_command(shell, parse_tokens(lexer_tokenize(input)));
        free(input);
    }
}
