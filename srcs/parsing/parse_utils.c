
#include "../../includes/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}

int	is_redir(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HERE_DOC);
}

void	handle_redir(t_cmd *cmd, t_token **tok)
{
	int	type;

	type = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != WORD)
		return ;
	if (type == REDIR_IN || type == HERE_DOC)
		cmd->input_file = remove_quotes(ft_strdup((*tok)->value));
	else if (type == REDIR_OUT)
		cmd->output_file = remove_quotes(ft_strdup((*tok)->value));
	else if (type == REDIR_APPEND)
	{
		cmd->output_file = remove_quotes(ft_strdup((*tok)->value));
		cmd->append = 1;
	}
	*tok = (*tok)->next;
}

int	count_args(t_token *start, t_token *end)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = start;
	while (tmp && tmp != end)
	{
		if (tmp->type == WORD)
			count++;
		else if (is_redir(tmp->type) && tmp->next)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (count);
}

char	**build_args(t_token *start, t_token *end)
{
	char	**args;
	int		count;
	int		i;

	count = count_args(start, end);
	args = ft_calloc(count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (start && start != end && i < count)
	{
		if (start->type == WORD)
			args[i++] = remove_quotes(ft_strdup(start->value));
		else if (is_redir(start->type) && start->next)
			start = start->next;
		start = start->next;
	}
	return (args);
}
