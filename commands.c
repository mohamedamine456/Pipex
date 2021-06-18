/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:01:31 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/14 09:55:20 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	*get_data(char **argv)
{
	t_command	*command;
	t_command	*tmp;
	int			i;
	char		**tab;

	command = (t_command *)malloc(sizeof(t_command));
	tmp = command;
	i = 2;
	while (argv[i + 1] != NULL)
	{	
		tab = ft_split(argv[i], ' ');
		tmp->name = ft_strdup(tab[0]);
		tmp->args = ft_args_dup(tab);
		tmp->next = NULL;
		i++;
		ft_free_args(tab);
		if (argv[i + 1] == NULL)
			break ;
		tmp->next = (t_command *)malloc(sizeof(t_command));
		tmp = tmp->next;
	}
	return (command);
}

char	**get_paths(char **envp)
{
	char	**tab;
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	tab = NULL;
	while (envp != NULL && envp[++i] != NULL)
	{
		tab = ft_split(envp[i], '=');
		if (tab != NULL && tab[0] != NULL)
		{
			if (!ft_strcmp(tab[0], "PATH"))
			{
				path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 4);
				ft_free_args(tab);
				tab = ft_split(path, ':');
				free(path);
				return (tab);
			}
			ft_free_args(tab);
			tab = NULL;
		}
	}
	return (tab);
}

char	*replace_commands(char *str, char **envp)
{
	char		**paths;
	char		*command_file;

	command_file = NULL;
	paths = get_paths(envp);
	if (paths == NULL)
		return (str);
	paths = ft_strjoin_args(paths, ft_strdup("/"));
	str = replace_path(str, paths, command_file);
	ft_free_args(paths);
	return (str);
}

char	*replace_path(char *str, char **paths, char *command_file)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (paths != NULL && paths[i] != NULL)
	{
		command_file = ft_strjoin(ft_strdup(paths[i]), str);
		fd = open(command_file, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			free(str);
			str = ft_strdup(command_file);
			free(command_file);
			return (str);
		}
		free(command_file);
		i++;
	}
	if (fd == -1)
		fatal_command();
	return (NULL);
}

int	check_args(char **args)
{
	int	i;

	i = 0;
	while (args != NULL && args[i] != NULL)
	{
		if (!ft_strcmp(args[i], ""))
			return (1);
		i++;
	}
	return (0);
}
