/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:09:15 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/16 15:12:24 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_minishell(int *status)
{
	printf("exit\n");
	ft_malloc(0, 0);
	exit(*status);
}

void	handle_input(char *input, t_mini *mini)
{
	t_token	*tokens;
	int		t_count;

	if (!validate_operators(input))
	{
		mini->status = 2;
		return ;
	}
	t_count = 0;
	tokens = tokenize(input, &t_count, mini);
	mini->cmd = fill_cmd(tokens, mini);
	new_node(mini->cmd);
	mini->cmd_count = count_cmd(mini->cmd);
	if (mini->cmd_count >= 1)
		ft_exec(mini);
}

void	read_content(t_mini *mini)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, check_sig);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		if (res(0, 0) == 1)
		{
			mini->status = 130;
			res(0, 1);
		}
		if (!input)
			exit_minishell(&mini->status);
		if (empty_line(input))
			continue ;
		if (*input)
			add_history(input);
		handle_input(input, mini);
		free(input);
		input = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	if (!isatty(1) || !isatty(0))
		return (1);
	mini.env = creat_lst(env);
	mini.status = 0;
	read_content(&mini);
	return (0);
}
