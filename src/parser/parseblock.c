#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "run.h"
#include <stddef.h>

t_cmd	*parseblock(char **ps, char *es)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		panic("missing `('");
	get_token(ps, es, NULL, NULL);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
	{
		freecmd(cmd);
		panic("missing `)'");
	}
	get_token(ps, es, NULL, NULL);
	cmd = parseredir(cmd, ps, es);
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet
