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
# include "includes/libft/libft.h"

typedef struct s_vault
{
	char *paths;
	char **path_names;
	char *prog_search;
}	t_vault;

/***** Initialisation *****/
void    find_paths(t_vault *path_list, char **envp);

/***** POUR DEBUG *****/
void    check_paths(t_vault *path_list);

#endif