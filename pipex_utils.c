/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:17:51 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/06 20:17:51 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_paths(t_vault *data) //DEBUG
{
	size_t	x;

	x = 0;
	while (data->path_names[x])
	{
		printf("Path_name #%zu : %s\n", x, data->path_names[x]);
		x++;
	}
	return ;
}
