/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:17:51 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/11 15:24:39 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	check_cmd(t_vault *data)
{
	if (ft_strchr(data->cmd.options[0], '/') != NULL)
		return (1);
	return (0);
}

int	message(t_vault *data, char *str1, char *str2, int error_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	if (error_code == 9)
		close_pipe_ends(data);
	else if (error_code == 8)
		free_dbl_ptr((void **)data->cmd.options);
	return (error_code);
}

void	exit_on_error(t_vault *data, int error_code)
{
	if (error_code == 7)
		free_dbl_ptr((void **)data->path_names);
	else
		exit (error_code);
}

void	check_fd_in(t_vault *data)
{
	data->fd_in = open(data->argv[1], O_RDONLY, 0644);
	if (data->fd_in == -1)
		exit_on_error(data, message(data, "FD_in error.", "", 9));
	close(data->fd_in);
	data->fd_in = open(data->argv[1], O_RDONLY, 0644);
}

void	check_fd_out(t_vault *data)
{
	data->fd_out = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == -1)
		exit_on_error(data, message(data, "FD_out error.", "", 9));
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
