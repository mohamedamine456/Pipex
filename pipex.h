/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:57:20 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/14 09:45:24 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define STDIN 0
# define STDOUT 1
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>

typedef struct s_command
{
	char				*name;
	char				**args;
	struct s_command	*next;
}						t_command;

typedef struct s_exec_data
{
	int			stdin_fd;
	int			stdout_fd;
	int			fds[2];
	t_command	*tmp_cmd;
	int			pid;
	int			pip_in;
	int			len;
	int			child_state;
}				t_exec_data;

/*
 * protorypes for exec_pipex.c file
 */

void		exec_pipe(t_command *command, char *in_file, char *out_file, char **envp);
void		exec_pipes(t_command *command, char **envp, int in_file, int out_file);
void		fork_pipe(t_exec_data *e_data, int in_file, int out_file, char **envp);

/*
 * protorypes for commands.c file
 */

t_command	*get_data(char **argv);
char		**get_paths(char **envp);
char		*replace_commands(char *str, char **envp);
char		*replace_path(char *str, char **paths, char *command_file);
int			check_args(char **args);

/*
 * protorypes for file_open_close.c file
 */

int			open_file(char *file, int type);
int			dup_file(int file_fd, int type, int *fd);
int			reset_files(int stdin_fd, int stdout_fd);
int			dup_pipe(int last, int fds[2]);
int			dup_pipes(int pip_in);

/*
 * protorypes for ft_split.c file
 */

char		**ft_split(char const *s, char c);
int			count_s(char *s, char c);
int			car_s(char *s, char c);
void		free_all(char **words, int i);

/*
 * protorypes for functions_args.c file
 */

char		**ft_args_dup(char **args);
int			ft_args_size(char **args);
char		**ft_strjoin_args(char **tab, char *str);
void		ft_free_args(char **args);
void		ft_free_command(t_command **command);

/*
 * protorypes for libft_functions.c file
 */

int			ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char const *s2);
int			ft_strcmp(const char *s1, const char *s2);

/*
 * prototypes for fatal.c
 */

void		fatal(char *error);
void		fatal_command();
void		fatal_file(char *in_file);
void		fatal_execve();
void		print_commands(t_command *command);

#endif
