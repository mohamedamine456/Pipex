/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:16:18 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/13 19:57:11 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, int type)
{
	int	new_fd;

	if (type)
		new_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	else
		new_fd = open(file, O_RDONLY, S_IWUSR | S_IRUSR);
	if (new_fd < 0)
	{
		fatal_file(file);
		return (-1);
	}
	return (new_fd);
}

int	dup_file(int file_fd, int type, int *fd)
{
	int	tmp_fd;

	if (file_fd != -1)
	{
		*fd = dup(type);
		tmp_fd = dup2(file_fd, type);
		if (tmp_fd < 0)
		{
			close(file_fd);
			return (-1);
		}
		return (0);
	}
	return (-1);
}

int	reset_files(int stdin_fd, int stdout_fd)
{
	if (dup2(0, stdin_fd) < 0)
	{
		close(stdin_fd);
		return (-1);
	}
	if (dup2(1, stdout_fd) < 0)
	{
		close(stdout_fd);
		return (-1);
	}
	return (0);
}

int	dup_pipe(int last, int fds[2])
{
	if (last == 1)
	{
		if (close(fds[1]) == -1)
			return (-1);
		if (dup2(fds[0], 0) == -1)
			return (-1);
		if (close(fds[0]) == -1)
			return (-1);
	}
	else if (last == 0)
	{
		if (close(fds[0]) == -1)
			return (-1);
		if (dup2(fds[1], 1) == -1)
			return (-1);
		if (close(fds[1]) == -1)
			return (-1);
	}
	return (0);
}

int	dup_pipes(int pip_in)
{
	if (dup2(pip_in, 0) == -1)
		return (-1);
	if (close(pip_in) == -1)
		return (-1);
	return (0);
}
