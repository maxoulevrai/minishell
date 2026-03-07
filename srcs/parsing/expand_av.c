
#include "../../includes/minishell.h"

char	**expand_av(char **av, t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (av && av[i])
	{
		expanded = expand_word(av[i], shell);
		if (!expanded)
			return (av);
		free(av[i]);
		av[i] = expanded;
		i++;
	}
	return (av);
}
