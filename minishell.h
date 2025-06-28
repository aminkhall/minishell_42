/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:01 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/16 15:00:31 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*all;
	struct s_env	*next;
}					t_env;

typedef enum e_rtype
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
}					t_rtype;

typedef struct s_status
{
	int				status;
}					t_status;

typedef struct s_redir
{
	t_rtype			type;
	char			*file;
	int				ambiguous;
	int				fd_herdoc;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	int				heredocs;
	int				expanded;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_mini
{
	t_cmd			*cmd;
	int				status;
	int				cmd_count;
	t_env			*env;
}					t_mini;

void				close_fd(void);
char				*get_value(t_env **env, char *value);
int					ft_strncmp(char *s1, char *s2, int size);
int					ft_cd(t_env **env, char **path, char *pwd);
int					ft_exec(t_mini *mini);
char				*ft_strdup(char *str);
int					ft_strlen(char *str);
void				ft_cat(char *dst, char *src);
void				ft_copy(char *dst, char *src);
char				*ft_join(char *s1, char *s2);
void				ft_putstr(int fd, char *str, int flag);
int					ft_echo(char **av);
char				**ft_split(char *s, char c);
int					ft_pwd(char *pwd);
void				ft_exit(char **code, int *status);
char				*ft_strchr(const char *s, int c);
int					ft_env(t_env **env);
int					is_builtins(char **input);
int					exec_builtins(t_env **env, char **input, int *status);
t_env				*creat_lst(char **env);
void				ft_lstadd_back(t_env **lst, t_env *new);
t_env				*ft_lstnew(char *key, char *value, char *all);
void				ft_swap(char **s1, char **s2);
int					ft_export(t_env **env, char **input);
int					ft_unset(t_env **env, char **input);
t_env				*creat_copy(t_env **env);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
char				**ft_split_env(char *s, char c);
void				check_sig(int sig);
void				ft_redir(t_redir *file, int flag, int *status);
int					ft_atoi(char *str);
void				update_pwd_entry(t_env *tmp, char *path, int *flag);
void				update_oldpwd_entry(t_env *tmp, char *tmp_oldpwd);
void				add_missing_pwd(t_env **env, char *tmp_oldpwd, char *path,
						int *flag);
void				add_missing_oldpwd(t_env **env, char *tmp_oldpwd);
int					count_cmd(t_cmd *cmd);
void				ft_execve(t_mini *mini);
void				close_fd_her(t_redir *tmp);
void				close_all_pipes(int pipes[][2], int cmd_count);
void				init_pipes(int pipes[][2], int cmd_count);
int					check_key(t_env **env, char *key);
int					ft_find(char *str, char c);
int					is_valid(char *input);
int					add_sign(char *input);
void				add(t_env **env, char **tab, char *input);
void				key_notfound(t_env **env, char **tab, char *input);
void				found_key(t_env **env, char **tab, char *input);
void				wait_for_children(pid_t *pids, int cmd_count, int *status);
int					ft_open(t_redir *file);
void				redir_null(void);
void				close_fd_her(t_redir *tmp);
char				**arr_env(t_env *env);

typedef enum e_type
{
	T_CMD,
	T_ARG,
	T_OP,
	T_QUT,
	T_FILE,
	T_END
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	int				expand;
	int				quoted;
	int				ambiguous;
	int				empty_ex;
	int				expanded;
}					t_token;

typedef struct s_delete
{
	void			*ptr;
	struct s_delete	*next;
}					t_delete;

typedef struct s_val
{
	t_token			**tokens;
	int				*count;
	int				expect_cmd;
	int				expect_file;
	int				to_export;
}					t_val;

typedef struct s_quote
{
	int				single;
	int				doubl;
}					t_quote;

t_token				create_token(t_type type, char *value, t_token *tmpl);
t_token				*add_token(t_token *tokens, int *count, int type,
						char *value);
t_cmd				*fill_cmd(t_token *tokens, t_mini *cmd);
char				*ft_strdup(char *s1);
char				*ft_strndup(char *s1, int n);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strjoin3(char *s1, char *s2, char *s3, int flag);
int					ft_strlen(char *s);
void				*ft_malloc(size_t size, int mode);
void				double_operator(char **current, t_val *tkn);
void				single_operator(char **current, t_val *tkn);
void				process_token(char **current, t_val *tkn, t_mini *cmd);
int					validate_operators(char *input);
int					full_space(char *str);
int					d_operator(char c, char next);
int					ft_strcmp(char *s1, char *s2);
int					ft_isalnum(int c);
char				*ft_remove_qoats(char *s);
char				*expand_variable(char *value, t_mini *cmd);
int					is_operator(char c);
int					is_quote(char c);
char				*ft_itoa(int n);
void				set_back_qoats(char *result);
void				set_qoats_fl(char *result);
char				*ft_substr(char *s, unsigned int start, size_t len);
int					handle_heredoc(char *delimiter, int flag, t_mini *var);
char				**expand_export(char *input, t_mini *cmd);
int					exit_herdoc(int val, int flag);
bool				is_space(char c);
int					handle_pipe(char *input);
int					handle_op(char *op, char **input);
void				skip_spaces(char **input);
t_token				*tokenize(char *input, int *t_count, t_mini *cmd);
void				collect_argument(char **current, t_val *tkn, t_mini *cmd);
char				*expand_heredoc(char *value, t_mini *cmd);
int					should_expand(char *input);
int					has_space(char *str);
void				empty_d(char **res, char *input, int *i);
void				get_env(char **res, char *input, int *i, t_mini *cmd);
void				get_string(char **res, char *input, int *i);
char				*get_env_value(t_env *env, char *key);
char				**split_rs(char *result);
void				herdoc_handler(int sig);
char				*ft_itoa_base(void *ptr);
int					should_expand_var(char *arg, t_val *tkn);
void				read_inquotes(char **current, char *buffer, int *index);
int					delim_check(t_val *tkn, char *arg);
char				*rmv_dquotes(char *arg);
char				*buffer_init(char *input);
void				initialize(char **current, char **buffer, char **arg);
int					expand_exprt(t_val *tkn, char *arg, t_mini *cmd);
char				*expand_var(t_val *tkn, char *arg, t_mini *cmd);
int					collect(char **current, char *buffer);
int					count_args(t_token *tokens, int start);
int					count_heredocs(t_token *tmp);
void				add_exp(t_cmd **list, int expanded);
void				add_heredoc(t_redir **list, t_rtype type, char *filename,
						int fd_herdoc);
void				check_sig(int sig);
void				new_node(t_cmd *head);
int					res(int val, int flag);
t_delete			*lstnew(void *str);
bool				empty_line(char *line);
void				remove_qu(char *s, char *result);
char				**get_strings(char *input);
void				get_env_heredoc(char **res, char *input, int *i,
						t_mini *cmd);
void				check_quotes(t_quote *quote, char *s);
void				expand_val(t_mini *cmd, char *s, char **tmp1, int flag);
int					is_var_char(char c);
int					count(char **arr);
char				**quote_case(char *result);

#endif