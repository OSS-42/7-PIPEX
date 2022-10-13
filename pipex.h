/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:04 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/13 12:18:16 by ewurstei         ###   ########.fr       */
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

typedef struct s_vault
{
	char	*paths;
	char	**path_names;
	char	*prog_search;
	char	**argv;
	int		nbr_args;
	int		argc;
	char	**envp;
	pid_t	*pid;
	int		child_id;
	int		status;
	int		*pipe_ends[2];
	int		fd;
	int		fd_in;
	int		fd_out;
}	t_vault;

/***** Initialisation *****/
void	find_paths(t_vault *data);
void	find_prog(t_vault *data);
void	exec_cmd(t_vault *data, int x);

/***** POUR DEBUG *****/
void	check_paths(t_vault *data);

#endif