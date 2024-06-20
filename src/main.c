#include "minishell.h"

#include <stdlib.h>

static int	keep_running(void)
{
	t_sh	*sh;

	sh = get_sh();
	get_str();
	if (!sh->str)
		return (0);
	if (*sh->str)
	{
		sh->cmd = parse_command(sh->str);
		execute_command(sh->cmd);
		free_command(&sh->cmd);
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	sh_init(argc, argv, envp);
	while (keep_running())
		;
	sh_deinit(EXIT_SUCCESS);
}
