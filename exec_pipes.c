/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:08:09 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/14 17:34:44 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_fork(t_exec_data *e_data, int in_file, int out_file, char **envp)
{
	pipe(e_data->fds);
	e_data->pid = fork();
	if (e_data->pid == 0)
	{
		if (e_data->len == 0)
		{
			dup_file(in_file, 0, &(e_data->stdin_fd));
			dup_pipe(0, e_data->fds);
		}
		else
		{
			dup_pipe(0, e_data->fds);
			dup_pipes(e_data->pip_in);
		}
		if (e_data->tmp_cmd->next == NULL)
		{
			dup_pipe(1, e_data->fds);
			dup_file(out_file, 1, &(e_data->stdout_fd));
		}
		e_data->tmp_cmd->name = replace_commands(e_data->tmp_cmd->name, envp);
		execve(e_data->tmp_cmd->name, e_data->tmp_cmd->args, envp);
	}
	e_data->pip_in = e_data->fds[0];
	close(e_data->fds[1]);
}

void	exec_pipes(t_command *command, char **envp,
		int in_file, int out_file)
{
	t_exec_data	e_data;

	e_data.stdout_fd = 0;
	e_data.pip_in = 0;
	e_data.tmp_cmd = command;
	e_data.len = 0;
	while (e_data.tmp_cmd != NULL)
	{
		pipe_fork(&e_data, in_file, out_file, envp);
		e_data.tmp_cmd = e_data.tmp_cmd->next;
		(e_data.len)++;
	}
	reset_files(e_data.stdin_fd, e_data.stdout_fd);
}

void	exec_pipe(t_command *command, char *infile, char *outfile, char **envp)
{
	int 		fds[2];
	int			pid1;
	int			pid2;
	int			fd0;
	int			fd1;
	int			child_state2;

	if (pipe(fds) == -1)
		fatal("pipe function failed!");
	pid1 = fork();
	if (pid1 == -1)
		fatal("fork function failed!");
	else if (pid1 == 0)
	{
		dup_file(open_file(infile, STDIN), STDIN, &fd0);
		close(fds[0]);
		dup2(fds[1], STDOUT);
		close(fds[1]);
		command->name = replace_commands(command->name, envp);
		if (execve(command->name, command->args, envp) == -1)
			fatal_execve();
	}
	pid2 = fork();
	if (pid2 == -1)
		fatal("fork function failed!");
	else if (pid2 == 0)
	{
		close(fds[1]);
		dup2(fds[0], STDIN);
		close(fds[0]);
		dup_file(open_file(outfile, STDOUT), STDOUT, &fd1);
		command->next->name = replace_commands(command->next->name, envp);
		if (execve(command->next->name, command->next->args, envp) == -1)
			fatal_execve();
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(pid2, &child_state2, 0);
	if (WIFEXITED(child_state2))
	{
		//free all
		//reset fdss
		exit(WEXITSTATUS(child_state2));
	}
}