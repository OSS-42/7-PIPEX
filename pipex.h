/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:01:12 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/17 19:01:12 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "includes/libft/libft.h"

enum	e_pipe_ends_name
{
	p_read,
	p_write
};

typedef struct s_cmd
{
	char	*name;
	char	**options;
	int		id;
}	t_cmd;

typedef struct s_vault
{
	char	*paths;
	char	**path_names;
	char	**argv;
	int		nbr_cmd;
	int		argc;
	char	**envp;
	pid_t	pid;
	int		child_id;
	int		status;
	int		*pipe_ends[2];
	int		fd_in;
	int		fd_out;
	t_cmd	cmd;
	int		error_flag;
}	t_vault;

/***** Initialisation *****/
void	find_paths(t_vault *data);
void	find_prog(t_vault *data, int y);

/***** Logique *****/
int		piping(t_vault *data);
void	forking(t_vault *data, int y);
int		dup_fds(t_vault *data, int y);
void	check_fd_in(t_vault *data);
void	check_fd_out(t_vault *data);
int		check_cmd(t_vault *data);
int		check_error(void);
int		message(char *str1, char *str2, char *str3, int error_code);

/***** Exiting *****/
void	close_pipe_ends(t_vault *data);

/***** POUR DEBUG *****/
void	check_paths(t_vault *data);
void	check_options(t_vault *data);
void	check_argv(t_vault *data);

#endif