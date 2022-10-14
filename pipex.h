/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:04 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/14 11:02:15 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
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
	int		fd;
	t_cmd	cmd;
}	t_vault;

/***** Initialisation *****/
void	find_paths(t_vault *data);
void	find_prog(t_vault *data, int y);
void	exec_cmd(t_vault *data, int y);

/***** POUR DEBUG *****/
void	check_paths(t_vault *data);

#endif