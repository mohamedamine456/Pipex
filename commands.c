/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:01:31 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/10 19:32:58 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	*get_data(char **argv, char **envp)
{
	t_command	*command;
	t_command	*tmp;
	int			i;
	char		**tab;

	command = (t_command *)malloc(sizeof(t_command));
	tmp = command;
	i = 2;
	while (argv[i + 1] != NULL)
	{
		tab = ft_split(argv[i], ' ');
		tmp->name = ft_strdup(tab[0]);
		tmp->args = ft_args_dup(tab);
		tmp->next = NULL;
		i++;
		if (argv[i + 1] == NULL)
			break ;
		tmp->next = (t_command *)malloc(sizeof(t_command));
		tmp = tmp->next;	
	}
	(void)envp;
	return (command);
}

void	print_commands(t_command *command)
{
	t_command	*tmp;
	int			i;

	tmp = command;
	while (tmp != NULL)
	{
		i = 0;
		printf("name: %15s, args:  ", tmp->name);
		while (tmp->args[i] != NULL)
		{
			printf("(%3d): %15s", i + 1, tmp->args[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}
