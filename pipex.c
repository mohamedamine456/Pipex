/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:49:05 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/23 12:31:23 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;

	if (argc != 5 || check_args(argv + 1))
	{
		write(1, "Error: \n", 8);
		write(1, argv[0], 7);
		write(1, " in_file cmd1 cmd2 out_file\n", 42);
		return (1);
	}
	command = get_data(argv);
	exec_pipe(command, argv[1], argv[argc - 1], envp);
	ft_free_command(&command);
	sleep(20);
	return (0);
}
