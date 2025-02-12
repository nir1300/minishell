/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:05:17 by codespace         #+#    #+#             */
/*   Updated: 2025/02/12 13:11:38 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _GNU_SOURCE
#include "../includes/minishell.h"

volatile sig_atomic_t g_last_exit_status = 0;

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
void setup_signals(void)
{
    struct sigaction sa;
    
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}


