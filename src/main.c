/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:36:51 by codespace         #+#    #+#             */
/*   Updated: 2025/02/11 14:20:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_ast(t_ast_node *root, int level)
{
    int i;

    if (!root)
        return ;
    i = 0;
    while (i < level)
    {
        printf("  ");
        i++;
    }
    printf("%s\n", root->token->value);
    print_ast(root->left, level + 1);
    print_ast(root->right, level + 1);
}

int main(int argc, char **argv, char **envp)
{
    t_minishell shell;

    (void)argc;
    (void)argv;
    init_minishell(&shell, envp);
    minishell_loop(&shell);
    cleanup_minishell(&shell);
    free_env(shell.env);
    return shell.exit_status;
}