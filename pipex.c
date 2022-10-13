/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:16 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/13 16:03:58 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_vault *data, int x)
{
	find_paths(data);
	check_paths(data); //DEBUG
	find_prog(data);
}

void	dup_fds(t_vault *data, int y)
{
	int		fd;
	int		fd_in;
	int		fd_out;
	int		reception;
	char	message_received[14];

	// considerer incrementation des pipes si plusieurs commandes
	if (y == 0)
	{
		fd_in = open("test.txt", O_RDONLY);
		fd_out = dup2(data->pipe_ends[y][2 * y + 1]);
		if (!fd_in || !fd_out)
			return ;
	}
	else if (y < data->nbr_args)
	{
		fd_in = dup2(data->pipe_ends[y][2 * y - 2]);
		fd_out = dup2(data->pipe_ends[y][2 * y + 1]);
		if (!fd_in || !fd_out)
			return ;
	}
	else if (y == data->nbr_args)
	{
		fd_in = dup2(data->pipe_ends[y][2 * y - 2]);
		fd_out = write("output.txt", resultat commande, taille resultat);
		if (!fd_in || !fd_out)
			return ;
	}
	return ;
}

int	piping(t_vault *data)
{
	char	secret[31];
	char	*pid_val;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < data->nbr_args - 1)
	{
		if (pipe(data->pipe_ends[x]) == -1)
			return (0);
		x++;
	}
	while (y < data->nbr_args)
	{
		data->pid[y] = fork();
		if (data->pid[y] == -1)
			return (0);
		else if (data->pid[y] == 0)
		{
			dup_fds(data, y);
			close(data->pipe_ends[y][2 * y - 2]);
			close(data->pipe_ends[y][2 * y + 1]);
			exec_cmd(data, y + 2);
			exit (0);
		}
		y++;
	}
	x = 0;
	while (x < data->nbr_args - 1)
	{
		close (data->pipe_ends[x][1]);
		close (data->pipe_ends[x][0]);
		x++;
	}
	
	// a fermer : fd_entree et fd_sortie.
	
	data->child_id = waitpid(0, &data->status, 0);
	while (data->child_id != -1)
		data->child_id = waitpid(0, &data->status, 0);
	
//		printf("#1 : OSS %d\n", getpid());
// 		pid_val = ft_itoa(getpid());
// 		close(data->pipe_ends[0]);
// 		strcpy(secret, pid_val);
// 		write(data->pipe_ends[1], secret, ft_strlen(secret));
// 		close(data->pipe_ends[1]);
// 		exit (1);
//		exec_cmd(data);
	
// 	else if (data->pid1 > 0)
// 	{
// 		data->pid2 = fork();
// 		if (data->pid2 == -1)
// 			return (0);
// 		else if (data->pid2 == 0)
// 		{
// 			printf("#2 : OSS %d\n", getpid());
// 			exit (2);
//			exec_cmd(data);
// 		}
// 		else if (data->pid2 > 0)
// 		{
// 			printf("il y a 2 agents\n");
// 			data->return_status1 = waitpid(data->pid1, &data->status_value1, 0);
// 			data->return_status2 = waitpid(data->pid2, &data->status_value2, 0);
// 			printf("voici le premier est OSS %d\n", data->return_status1);
// 			if (WIFEXITED(data->status_value1))
// 				printf("toujours en activité (%d)\n", WEXITSTATUS(data->status_value1));
// 			else
// 				printf("il a été terminé....\n");
// 			printf("et le deuxième est OSS %d\n", data->return_status2);
// 			if (WIFEXITED(data->status_value2))
// 				printf("toujours en actitité (%d)\n", WEXITSTATUS(data->status_value2));
// 			else
// 				printf("il a été terminé....\n");
// 		}
// 	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
//	if (argc != 5)
//		return (0);
	t_vault data;

	data.paths = NULL;
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.nbr_args = argc - 3;
	piping(&data);
	return (0);
}
