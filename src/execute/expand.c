#include <stdio.h>
#include <stdlib.h>

#include "ft.h"
#include "minishell.h"

char	*expand_variable(const char **arg, char **envp)
{
	char	env_name[1024];
	char	*env_value;
	char	*current;

	ft_bzero(env_name, sizeof(env_name));
	if (*arg && (ft_isalnum(**arg) || **arg == '_'))
	{
		current = env_name;
		while (*arg && (ft_isalnum(**arg) || **arg == '_'))
			*current++ = *(*arg)++;
		*current = '\0';
		env_value = ft_getenv(env_name, envp);
		if (env_value)
			return (env_value);
		return ("");
	}
	return ("$");
}

char	*expand_variables(const char *arg, char **envp)
{
	char	expanded[1024];
	char	*current;

	ft_bzero(expanded, sizeof(expanded));
	while (arg && *arg)
	{
		current = expanded + ft_strlen(expanded);
		while (*arg && *arg != '$')
			*current++ = *arg++;
		*current = '\0';
		if (*arg == '$')
		{
			arg++;
			ft_strlcat(expanded, expand_variable(&arg, envp), sizeof(expanded));
		}
	}
	return (ft_strdup(expanded));
}

char	*remove_quotes(const char *arg)
{
	char	*no_quotes;
	char	*dest;
	char	quote;

	no_quotes = (char *)malloc(ft_strlen(arg) + 1);
	if (no_quotes == NULL)
		panic("malloc");
	dest = no_quotes;
	quote = 0;
	while (*arg)
	{
		if (*arg == '\\' && (*(arg + 1) == '"' || *(arg + 1) == '\''))
			*dest++ = *++arg;
		else if (!quote && (*arg == '"' || *arg == '\''))
			quote = *arg++;
		else if (*arg == quote)
		{
			quote = 0;
			arg++;
		}
		else
			*dest++ = *arg++;
	}
	*dest = '\0';
	return (no_quotes);
}

char	*expand_argument(const char *arg, char **envp)
{
	char	*no_quotes;
	char	*expanded;

	no_quotes = remove_quotes(arg);
	if (*arg == '\'')
		return (no_quotes);
	if (ft_strchr(arg, '$'))
	{
		free(no_quotes);
		expanded = expand_variables(arg, envp);
		no_quotes = remove_quotes(expanded);
		free(expanded);
		return (no_quotes);
	}
	return (no_quotes);
}

char	**expand_arguments(char **args, char **envp)
{
	char	**expanded;
	size_t	size;
	size_t	i;

	size = 0;
	while (args[size])
		size++;
	expanded = (char **)malloc((size + 1) * sizeof(char *));
	if (expanded == NULL)
		panic("malloc");
	i = -1;
	while (++i < size)
		expanded[i] = expand_argument(args[i], envp);
	expanded[i] = NULL;
	return (expanded);
}