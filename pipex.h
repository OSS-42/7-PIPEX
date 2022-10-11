/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:04 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/06 20:37:59 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "includes/libft/libft.h"

typedef struct s_vault
{
	char	*paths;
	char	**path_names;
	char	*prog_search;
	char	**argv;
	int		argc;
	char	**envp;
	t_pid	pid1;
	t_pid	pid2;
	t_pid	status_child;
	int		*pipe_ends[2];
}	t_vault;

/***** Initialisation *****/
void	find_paths(t_vault *data);
void	find_prog(t_vault *data);
void	exec_cmd(t_vault * data);

/***** POUR DEBUG *****/
void	check_paths(t_vault *data);

#endif