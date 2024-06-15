#include "libft.h"
#include "minishell.h"

t_cmd	*execute(void)
{
	t_execute	*cmd;

	cmd = (t_execute *)ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		panic("ft_calloc");
	cmd->type = EXECUTE;
	return ((t_cmd *)cmd);
}

t_cmd	*redirection(t_subtype subtype, t_cmd *subcmd, int mode, int fd)
{
	t_redirection	*cmd;

	cmd = (t_redirection *)ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		panic("ft_calloc");
	cmd->type = REDIRECTION;
	cmd->subtype = subtype;
	cmd->cmd = subcmd;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*list(t_subtype subtype, t_cmd *left, t_cmd *right)
{
	t_list	*cmd;

	cmd = (t_list *)ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		panic("ft_calloc");
	cmd->type = LIST;
	cmd->subtype = subtype;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*pipeline(t_subtype subtype, t_cmd *left, t_cmd *right)
{
	t_pipeline	*cmd;

	cmd = (t_pipeline *)ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		panic("ft_calloc");
	cmd->type = PIPELINE;
	cmd->subtype = subtype;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
