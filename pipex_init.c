/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:15:25 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/17 19:15:25 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_vault(t_vault *data, int argc, char **argv, char **envp)
{
	data->paths = NULL;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->nbr_cmd = argc - 3;
	data->error_flag = 0;
	data->fd_in = -1;
	data->fd_out = -1;
}
