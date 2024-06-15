#include "minishell.h"

char	*ft_getenv(char *name)
{
	char	**envp;
	char	*env;
	char	*ptr;

	if (!name || !*name)
		return (0);
	envp = get_sh()->env;
	while (*envp)
	{
		env = *envp;
		ptr = name;
		while (*env == *ptr && *ptr != '\0')
		{
			env++;
			ptr++;
		}
		if (*ptr == '\0' && *env == '=')
			return (env + 1);
		envp++;
	}
	return (0);
}
