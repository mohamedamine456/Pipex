/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 15:04:45 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/13 18:59:55 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fatal(t_command **command, char **paths)
{
	ft_free_command(command);
	ft_free_args(paths);
	write(1, "./pipex: command not found\n", 27);
	exit(127);
}

void	fatal_file(t_command **command, char *in_file)
{
	char	*error;

	error = strerror(errno);
	ft_free_command(command);
	write(1, "./pipex ", 8);
	write(1, error, ft_strlen(error));
	write(1, ": ", 2);
	write(1, in_file, ft_strlen(in_file));
	write(1, "\n", 1);
	exit(0);
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
