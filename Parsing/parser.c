/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:20:37 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/09 16:10:44 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir(t_redir **list, t_rtype type, t_token *token, int *i)
{
	t_redir	*new;
	t_redir	*tmp;

	new = ft_malloc(sizeof(t_redir), 0x1);
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(token[*i].value);
	new->next = NULL;
	new->ambiguous = token[*i].ambiguous;
	new->fd_herdoc = -1;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_redirection(t_token *tokens, int *i, t_cmd *cmd, t_mini *var)
{
	char	*value;
	char	*filename;
	int		fd_heredoc;
	int		flag;

	value = tokens[*i].value;
	if (tokens[*i + 1].type != T_FILE)
		return ;
	(*i)++;
	filename = ft_strdup(tokens[*i].value);
	fd_heredoc = -1;
	if (ft_strcmp(value, "<") == 0)
		add_redir(&cmd->redirs, IN, tokens, i);
	else if (ft_strcmp(value, ">") == 0)
		add_redir(&cmd->redirs, OUT, tokens, i);
	else if (ft_strcmp(value, ">>") == 0)
		add_redir(&cmd->redirs, APPEND, tokens, i);
	else if (ft_strcmp(value, "<<") == 0)
	{
		flag = 0;
		if (tokens[*i].quoted == 1)
			flag = 1;
		fd_heredoc = handle_heredoc(tokens[*i].value, flag, var);
		add_heredoc(&cmd->redirs, HEREDOC, filename, fd_heredoc);
	}
}

void	fill_args(t_token *tokens, int *i, t_cmd *cmd, t_mini *var)
{
	char	**args;
	int		expanded;
	int		index;

	args = ft_malloc(sizeof(char *) * (count_args(tokens, *i) + 1), 0x1);
	index = 0;
	expanded = 0;
	while (tokens[*i].type != T_END && !(tokens[*i].type == T_OP
			&& ft_strcmp(tokens[*i].value, "|") == 0))
	{
		if (tokens[*i].type == T_ARG || tokens[*i].type == T_CMD)
		{
			if (tokens[*i].empty_ex == 0)
				args[index++] = ft_strdup(tokens[*i].value);
		}
		else if (tokens[*i].type == T_OP)
			handle_redirection(tokens, i, cmd, var);
		(*i)++;
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	args[index] = NULL;
	cmd->args = args;
}

t_cmd	*single_cmd(t_token *tokens, int *i, t_mini *var)
{
	t_cmd	*cmd;
	t_token	*tmp;
	int		start;

	tmp = tokens;
	start = *i;
	cmd = ft_malloc(sizeof(t_cmd), 0x1);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->heredocs = 0;
	cmd->heredocs = count_heredocs(tmp);
	if (cmd->heredocs > 16)
	{
		ft_putstr(2, "maximum here-document count exceeded\n", 0);
		var->status = 2;
		ft_malloc(0, 0);
		exit(2);
	}
	fill_args(tokens, i, cmd, var);
	if (tokens[*i].type == T_OP && ft_strcmp(tokens[*i].value, "|") == 0)
		(*i)++;
	return (cmd);
}

t_cmd	*fill_cmd(t_token *tokens, t_mini *cmd)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_cmd;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	if (!tokens)
		return (NULL);
	while (tokens[i].type != T_END && exit_herdoc(0, 0) != 1)
	{
		new_cmd = single_cmd(tokens, &i, cmd);
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
	}
	if (exit_herdoc(0, 0) == 1)
		exit_herdoc(0, 1);
	return (head);
}
