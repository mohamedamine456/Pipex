/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:49:05 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/12 17:25:17 by mlachheb         ###   ########.fr       */
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
	//print_commands(command);
	exec_pipe(command, envp, argv[1], argv[4]);
	return (0);
}

void	exec_pipe(t_command *command, char **envp, char *in_file, char *out_file)
{
	int			stdin_fd;
	int			stdout_fd;
	int			fds[2];
	t_command	*tmp_cmd;
	int			pid;

	stdout_fd = 0;
	tmp_cmd = command;
	open_file(in_file, 0, &stdin_fd);
	pipe(fds);
	while (tmp_cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (tmp_cmd->next != NULL)
				dup_pipe(0, fds);
			else
			{
				dup_pipe(1, fds);
				open_file(out_file, 1, &stdout_fd);
			}
			execve(tmp_cmd->name, tmp_cmd->args, envp);
		}
		tmp_cmd = tmp_cmd->next;
	}
	close(fds[0]);
	close(fds[1]);
	reset_files(stdin_fd, stdout_fd);
}
