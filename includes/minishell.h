/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:05:48 by vagarcia          #+#    #+#             */
/*   Updated: 2025/02/12 13:11:28 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************
 *        INCLUDES            *
 ******************************/

# include "../ShellLibft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/******************************
 *        DEFINES             *
 ******************************/
# define SUCCESS 0
# define FAILURE 1
# define PROMPT "minishell-> "
# define READ_END 0
# define WRITE_END 1
# define MAX_TOKENS 1024
# define HEREDOC_TMP "/tmp/.heredoc"

/******************************
 *        ENUMS               *
 ******************************/

/* Redirection Types */
typedef enum e_redir_type
{
	REDIR_IN,     // <
	REDIR_OUT,    // >
	REDIR_APPEND, // >>
	REDIR_HEREDOC // <<
}						t_redir_type;

/* Logical Operators */
typedef enum e_logical_op
{
	OP_NONE,
	OP_AND, // &&
	OP_SEMI,
	OP_OR // ||
}						t_logical_op;

/* Job State */
typedef enum e_job_state
{
	JOB_RUNNING,
	JOB_STOPPED,
	JOB_BACKGROUND,
	JOB_DONE
}						t_job_state;

/******************************
 *        STRUCTURES          *
 ******************************/

/* Redirection Node */
typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_token
{
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_ast_node
{
	t_token				*token;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

/* Command Node */
typedef struct s_cmd
{
	int					in_fd;
	int					out_fd;
	char				**args;
	t_redir				*input;
	t_redir				*output;
	struct s_cmd		*next;
	t_logical_op		log_op;
}						t_cmd;

/* Job Control */
typedef struct s_job
{
	int					job_id;
	pid_t				pgid;
	char				*command;
	t_job_state			state;
	struct s_job		*next;
}						t_job;

/* Unified Minishell Struct */
typedef struct s_minishell
{
	char				**env;
	int					exit_status;
	int					is_interactive;
	int					signal_status;
	int					stdin_backup;
	int					stdout_backup;
	char				*input;
	t_cmd				*cmds;
	t_job				*jobs;
	int					last_job_id;
}						t_minishell;

/******************************
 *        FUNCTION PROTOTYPES *
 ******************************/

/* Testing implementations */
# define TOKEN_DELIMITERS " \t\r\n\a"

bool					is_special_char(char c);
char					**copy_env(char **envp);
void					free_env(char **env);
t_token					*lexer(char *input);
t_cmd					*parser(t_token *tokens);
void					free_tokens(t_token *tokens);
void					free_ast(t_ast_node *root);
void					print_ast(t_ast_node *root, int level);
void					add_argument(t_cmd *cmd, char *value);
void					add_redirection(t_cmd *cmd, t_redir_type type,
							char *file);
t_cmd					*create_cmd_node(void);
int						check_meta(t_token *toks, t_cmd *cmds);
void					*ft_realloc(void *ptr, size_t old_size,
							size_t new_size);
t_token					*handle_regular_token(char *input, int *i);
t_token					*handle_quoted_string(char *input, int *i);
t_token					*handle_special_char(char *input, int *i);

/* ======= SHELL INIT & MAIN LOOP ======= */

void					minishell_loop(t_minishell *shell);
void					init_minishell(t_minishell *shell, char **envp);
void					start_minishell(t_minishell *shell);
void					cleanup_minishell(t_minishell *shell);
void					exit_minishell(t_minishell *shell, int exit_code);

/* ======= LEXER (Tokenization) ======= */
t_token					*create_token(char *value);
t_list					*lexer_tokenize(char *input);
bool					is_operator(char *token);
bool					is_quote(char c);
void					handle_quotes(char *input, bool *in_quote,
							char *quote_char);

/* ======= PARSER (Syntax Analysis) ======= */
t_cmd					*parse_tokens(t_list *tokens);
t_cmd					*create_command_node(char **args);
void					append_command(t_cmd **cmd_list, t_cmd *new_cmd);
t_cmd					*parse_pipeline(t_list **tokens);
t_cmd					*parse_logical_operators(t_list **tokens);
t_redir					*parse_redirection(t_list **tokens);

/* ======= EXPANDER (Variable & Wildcard Expansion) ======= */
char					*expand_variables(char *input, t_minishell *shell);
char					*expand_wildcards(char *pattern);
char					*expand_tilde(char *input, t_minishell *shell);

/* ======= EXECUTOR (Command Execution & Piping) ======= */
int						execute_command(t_minishell *shell, t_cmd *cmd);
int						execute_pipeline(t_minishell *shell, t_cmd *cmd);
void					execute_builtin(t_minishell *shell, t_cmd *cmd);
void					execute_external(t_minishell *shell, t_cmd *cmd);
void					handle_exit_status(int status);

/* ======= BUILTINS (Shell Internal Commands) ======= */
int						builtin_echo(char **args);
int						builtin_cd(char **args, t_minishell *shell);
char					*get_home_directory(t_minishell *shell);
int						builtin_pwd(void);
int						builtin_export(char **args, t_minishell *shell);
void					set_env_variable(char *key, char *value,
							t_minishell *shell);
int						builtin_unset(char **args, t_minishell *shell);
int						builtin_env(t_minishell *shell);
int						builtin_exit(char **args, t_minishell *shell);

/* ======= REDIRECTIONS ======= */
void					apply_redirections(t_cmd *cmd);
int						redirect_input(t_cmd *cmd);
int						redirect_output(t_cmd *cmd);
int						redirect_append(t_cmd *cmd);
int						handle_heredoc(t_cmd *cmd);

/* ======= SIGNAL HANDLING ======= */

void					setup_signals(void);
void					signal_handler(int signo);

/* ======= JOB CONTROL (Background Jobs) ======= */

void					add_job(t_minishell *shell, pid_t pgid, char *cmd,
							t_job_state state);
void					remove_job(t_minishell *shell, int job_id);
void					print_jobs(t_minishell *shell);
void					continue_job(t_minishell *shell, int job_id,
							bool foreground);

/* ======= MEMORY MANAGEMENT ======= */
void					free_command(t_cmd *cmd);
void					free_redirections(t_redir *redir);
void					free_jobs(t_job *jobs);

#endif
