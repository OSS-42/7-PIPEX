/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:16 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/12 16:19:50 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_vault *data)
{
	find_paths(data);
	check_paths(data); //DEBUG
	find_prog(data);
}

void	dup_fds(t_vault *data)
{
	int		fd;
	int		fd_in;
	int		fd_out;
	int		reception;
	char	message_received[14];

	fd = open("test.txt", O_RDONLY);
	if (!fd)
		return ;
	fd_in = dup2(fd, 0);
	fd_out = dup2(data->pipe_ends[1], 1);
	if (!fd_out || !fd_in)
		return ;
	reception = read(fd, message_received, 13);
	if (reception == -1)
		return ;
	message_received[reception] = '\0';
	printf("le fd %d contient %s\n", fd_in, message_received);
	reception = read(fd_out, message_received, 13);
	if (reception == -1)
		return ;
	message_received[reception] = '\0';
	printf("le fd %d contient %s\n", fd_out, message_received);
}

int	piping(t_vault *data)
{
	char	secret[31];
	char	*pid_val;
	
	if (pipe(data->pipe_ends) == -1)
		return (0);
	data->pid1 = fork();
	if (data->pid1 == -1)
		return (0);
	else if (data->pid1 == 0)
	{
//		printf("#1 : OSS %d\n", getpid());
		pid_val = ft_itoa(getpid());
		close(data->pipe_ends[0]);
		strcpy(secret, pid_val);
		write(data->pipe_ends[1], secret, ft_strlen(secret));
		close(data->pipe_ends[1]);
		exit (1);
//		exec_cmd(data);
	}
	else if (data->pid1 > 0)
	{
		data->pid2 = fork();
		if (data->pid2 == -1)
			return (0);
		else if (data->pid2 == 0)
		{
			printf("#2 : OSS %d\n", getpid());
			exit (2);
//			exec_cmd(data);
		}
		else if (data->pid2 > 0)
		{
			printf("il y a 2 agents\n");
			data->return_status1 = waitpid(data->pid1, &data->status_value1, 0);
			data->return_status2 = waitpid(data->pid2, &data->status_value2, 0);
			printf("voici le premier est OSS %d\n", data->return_status1);
			if (WIFEXITED(data->status_value1))
				printf("toujours en activité (%d)\n", WEXITSTATUS(data->status_value1));
			else
				printf("il a été terminé....\n");
			printf("et le deuxième est OSS %d\n", data->return_status2);
			if (WIFEXITED(data->status_value2))
				printf("toujours en actitité (%d)\n", WEXITSTATUS(data->status_value2));
			else
				printf("il a été terminé....\n");
		}
	}
	return (0);
}
/*
	{
		close(data->pipe_ends[1]); // je ferme car j'écris rien
		waitpid(data->pid1, NULL, 0); // j'attend que pid1 soit fini (avec le close)
		printf("Salut, je récupère le message\n");
		reception = read(data->pipe_ends[0], message_received, 31);
		close(data->pipe_ends[0]);
		if (reception == -1)
			return ;
		message_received[reception] = '\0';
		printf("le message est : %s\n", message_received);
	}
*/

int	main(int argc, char **argv, char **envp)
{
//	if (argc != 5)
//		return (0);
	t_vault data;

	data.paths = NULL;
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
//	dup_fds(&data);
//	piping(&data);
	exec_cmd(&data);
	return (0);
}

/*
void	find_path(void)
{
	char *options;

	options = ;
	execve("/usr/bin/env", options, envp);
	return (0);
}
*/

// void	pipex(int fd1, int fd2)
// {
// 	int end[2];

// 	pipe(end);
// }

/*
int main(int argc, char **argv, char **envp)
{
	char *options[3] = {"ls", "-la", NULL};

	(void)argc;
	(void)argv;
	execve("/usr/bin/ls", options, envp);
	return (0);
}
*/