#include "lexer.h"
#include "parser.h"
#include <stddef.h>

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		get_token(ps, es, NULL, NULL);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet
