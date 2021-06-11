/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:49:05 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/11 19:29:06 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_command *command;
	if (argc != 5)
	{
		write(1, "Error: \n", 8);
		write(1, argv[0], 7);
		write(1, " in_file cmd1 cmd2 out_file\n", 42);
		return (1);
	}
	command = get_data(argv);
	replace_commands(&command, envp);
	print_commands(command);
	//exec_pipe(command);
	return (0);
}

void	exec_pipe(t_command *command, char *in_file, char *out_file)
{
	int			stdin_fd;
	int			stdout_fd;
	int			pipe_fds[2];
	t_command	*tmp_cmd;
	int			pid;

	tmp_cmd = command;
	if (tmp_cmd != NULL)
	{
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
		}
	}
	open_file(in_file, 0, &stdin_fd);
	open_file(out_file, 1, &stdout_fd);
	reset_files(stdin_fd, stdout_fd);
}
