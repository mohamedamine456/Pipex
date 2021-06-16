/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:49:05 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/14 09:52:24 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;
	int			in_file;
	int			out_file;

	if (argc != 5 || check_args(argv + 1))
	{
		write(1, "Error: \n", 8);
		write(1, argv[0], 7);
		write(1, " in_file cmd1 cmd2 out_file\n", 42);
		return (1);
	}
	command = get_data(argv);
	in_file = open_file(argv[1], 0);
	out_file = open_file(argv[4], 1);
	exec_pipe(command, in_file, out_file, envp);
	ft_free_command(&command);
	return (0);
}
