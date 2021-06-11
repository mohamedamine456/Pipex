/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions_second.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:51:30 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/11 17:29:03 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_args_size(char **args)
{
	int i;

	i = 0;
	while (args != NULL && args[i] != NULL)
		i++;
	return (i);
}

char	**ft_args_dup(char **args)
{
	int	len;
	int	i;
	char **new_args;

	i = 0;
	len = ft_args_size(args);
	new_args = (char **)malloc((len + 1) * sizeof(char *));
	while (args != NULL && args[i] != NULL)
	{
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}

char	**ft_strjoin_args(char **tab, char *str)
{
	int i;

	i = 0;

	if (tab == NULL || str == NULL)
		return (NULL);
	while (tab[i] != NULL)
	{
		tab[i] = ft_strjoin(tab[i], str);
		i++;
	}
	free(str);
	return (tab);
}

/**
 * funtion to free all elements in a table of strings and also the table
*/

void	ft_free_args(char **args)
{
    int     i;

    i = 0;
    if (args != NULL)
    {
        while (args[i] != NULL)
        {
            free(args[i]);
            i++;
        }
        free(args);
        args = NULL;
    }
}

void	ft_free_command(t_command *command)
{
	if (command->name != NULL)
		free(command->name);
	ft_free_args(command->args);
	free(command);
	command = NULL;
}
