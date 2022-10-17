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

void	close_pipe_ends(t_vault *data)
{
	int	x;

	x = 0;
	while (x < data->nbr_cmd - 1)
	{
		close (data->pipe_ends[x][p_read]);
		close (data->pipe_ends[x][p_write]);
		free (data->pipe_ends[x]);
		x++;
	}
	return ;
}

int	check_error(void)
{
	if (errno != 0)
		perror("Error");
	return (errno);
}

void	check_fd_in(t_vault *data)
{
	data->fd_in = open("infile", O_RDONLY);
	if (data->fd_in == -1)
		check_error();
}

void	check_fd_out(t_vault *data)
{
	data->fd_out = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!data->fd_out)
		check_error();
}
/***** POUR DEBUG ****
void	check_paths(t_vault *data)
{
	size_t	x;

	x = 0;
	while (data->path_names[x])
	{
		fprintf(stderr, "Path_name #%zu : %s\n", x, data->path_names[x]);
		x++;
	}
	return ;
}

void	check_options(t_vault *data)
{
	size_t	x;

	x = 0;
	while (data->cmd.options[x])
	{
		fprintf(stderr, "Options #%zu : %s\n", x, data->cmd.options[x]);
		x++;
	}
	return ;
}

void	check_argv(t_vault *data)
{
	size_t	x;

	x = 0;
	while (data->argv[x])
	{
		fprintf(stderr, "Args #%zu : %s\n", x, data->argv[x]);
		x++;
	}
	return ;
}
*/
