/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:16:18 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/10 16:16:39 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, int type, int *fd)
{
	int	tmp_fd;
	int	new_fd;

	*fd = dup(type);
	if (*fd < 0)
		return (-1);
	if (type)
		new_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	else
		new_fd = open(file, O_RDONLY, S_IWUSR | S_IRUSR);
	if (new_fd < 0)
		return (-1);
	tmp_fd = dup2(new_fd, type);
	if (tmp_fd < 0)
	{
		close(new_fd);
		return (-1);
	}
	close(new_fd);
	return (0);
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
