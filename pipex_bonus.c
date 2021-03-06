/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:51:01 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/14 09:55:37 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;
	int			in_file;
	int			out_file;

	if (argc < 5 || check_args(argv + 1))
	{
		write(1, "Error: \n", 8);
		write(1, argv[0], 7);
		write(1, " in_file cmd1 ... cmdn out_file\n", 46);
		return (1);
	}
	command = get_data(argv);
	in_file = open_file(argv[1], 0);
	out_file = open_file(argv[argc - 1], 1);
	replace_commands(&command, envp);
	exec_pipes(command, envp, in_file, out_file);
	ft_free_command(&command);
	return (0);
}
