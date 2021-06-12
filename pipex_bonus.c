/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:51:01 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/12 20:21:22 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_command *command;
	if (argc < 5)
	{
		write(1, "Error: \n", 8);
		write(1, argv[0], 7);
		write(1, " in_file cmd1 ... cmdn out_file\n", 46);
		return (1);
	}
	command = get_data(argv);
	replace_commands(&command, envp);
	exec_pipes(command, envp, argv[1], argv[argc - 1]);
	return (0);
}

void	exec_pipes(t_command *command, char **envp, char *in_file, char *out_file)
{
	int			stdin_fd;
	int			stdout_fd;
	int			fds[2];
	t_command	*tmp_cmd;
	int			pid;
	int			pip_in;
	int			len;

	stdout_fd = 0;
	pip_in = 0;
	tmp_cmd = command;
	len = 0;
	open_file(in_file, 0, &stdin_fd);
	while (tmp_cmd != NULL)
	{
		pipe(fds);
		pid = fork();
		if (pid == 0)
		{
			dup_pipes(1, fds, &pip_in);
			if (tmp_cmd->next == NULL)
			{	
				open_file(out_file, 1, &stdout_fd);
			}
			execve(tmp_cmd->name, tmp_cmd->args, envp);
		}
		pip_in = fds[0];
		tmp_cmd = tmp_cmd->next;
	}
	reset_files(stdin_fd, stdout_fd);
}
