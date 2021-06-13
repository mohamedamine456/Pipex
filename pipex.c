/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:49:05 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/13 18:52:34 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;

	if (argc != 5)
	{
		write(1, "Error: \n", 8);
		write(1, argv[0], 7);
		write(1, " in_file cmd1 cmd2 out_file\n", 42);
		return (1);
	}
	command = get_data(argv);
	replace_commands(&command, envp);
	exec_pipes(command, envp, argv[1], argv[argc - 1]);
	ft_free_command(&command);
	return (0);
}
