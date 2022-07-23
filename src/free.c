
# include "minishell.h"

void	ft_free_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		ft_free_str(&split[i]);
		i++;
	}
	free(split);
	return(NULL);
}

void ft_free_all(void)
{
	if (g_env)
		ft_free_split(g_env);
	rl_clear_history();
}