/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:16 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/12 11:51:43 by ewurstei         ###   ########.fr       */
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
	if(!fd_out || !fd_in)
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

void	piping(t_vault *data)
{
	char	message_sent[31];
	char	message_received[31];
	int		reception;
	
	if (pipe(data->pipe_ends) == -1)
		return ;
	data->pid1 = fork();
	if (data->pid1 == -1)
		return ;
	else if (data->pid1 == 0)
	{
		close(data->pipe_ends[0]); // je ferme car je lis rien
		printf("coucou\n");
		strcpy(message_sent, "Comment est votre blanquette ?");
		write(data->pipe_ends[1], message_sent, ft_strlen(message_sent));
		close(data->pipe_ends[1]);
	}
	else
	{
		close(data->pipe_ends[1]); // je ferme car j'écris rien
		waitpid(data->pid1, NULL, 0); // j'attend que pid1 soit fini (avec le close)
		printf("je récupère le message\n");
		reception = read(data->pipe_ends[0], message_received, 31);
		close(data->pipe_ends[0]);
		if (reception == -1)
			return ;
		message_received[reception] = '\0';
		printf("le message est : %s\n", message_received);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vault data;

	data.paths = NULL;
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	dup_fds(&data);
//	piping(&data);
//	exec_cmd(&data);
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