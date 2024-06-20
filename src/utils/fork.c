#include "minishell.h"

#include <signal.h>
#include <unistd.h>

pid_t	fork1(void)
{
	pid_t	pid;

	if (get_sh()->subshell == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			get_sh()->subshell = 1;
			if (signal(SIGINT, SIG_DFL) == SIG_ERR)
				panic("signal");
			if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
				panic("signal");
		}
		else if (pid == -1)
			panic("fork");
		return (pid);
	}
	return (0);
}
