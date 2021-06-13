/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 15:04:45 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/13 15:47:03 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fatal(t_command **command, char **paths)
{
	ft_free_command(command);
	ft_free_args(paths);
	write(1, "./pipex command not found\n", 26);
	exit(1);
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
			printf(" (%d): %15s", i + 1, tmp->args[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}
