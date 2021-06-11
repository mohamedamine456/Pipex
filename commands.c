/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:01:31 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/11 17:30:31 by mlachheb         ###   ########.fr       */
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
		if (argv[i + 1] == NULL)
			break ;
		tmp->next = (t_command *)malloc(sizeof(t_command));
		tmp = tmp->next;	
	}
	return (command);
}

void	print_commands(t_command *command)
{
	t_command	*tmp;
	int			i;

	tmp = command;
	while (tmp != NULL)
	{
		i = 0;
		printf("name: %15s, args:  ", tmp->name);
		while (tmp->args[i] != NULL)
		{
			printf(" (%d): %15s", i + 1, tmp->args[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

char	**get_paths(char **envp)
{
	char    **tab;
	char    *path;
	int     i;

	i = 0;
	path = NULL;
	tab = NULL;
	while (envp != NULL && envp[i]!= NULL)
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
		}
		i++;
	}
	return (tab);
}

void	replace_commands(t_command **command, char **envp)
{
	char		**paths;
	char		*command_file;
	t_command	*tmp;
	int			i;
	int			fd;

	tmp = *command;
	paths = get_paths(envp);
	paths = ft_strjoin_args(paths, ft_strdup("/"));
	while (tmp != NULL && paths != NULL)
	{
		i = 0;
		fd = -1;
		while (paths != NULL && paths[i] != NULL)
		{
			command_file = ft_strjoin(ft_strdup(paths[i]), tmp->name);
			fd = open(command_file, O_RDONLY);
			if (fd >= 0)
			{
				close(fd);
				free(tmp->name);
				tmp->name = ft_strdup(command_file);
				tmp->args[0] = ft_strdup(command_file);
				free(command_file);
				break ;
			}
			free(command_file);
			i++;
		}
		if (fd == -1)
		{
			ft_free_command(*command);
			ft_free_args(paths);
			write(1, "./pipex command not found\n", 26);
			exit(1);
		}
		tmp = tmp->next;
	}
}
