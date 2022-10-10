/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:16 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/09 21:48:06 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    find_prog(t_vault *data)
{
    size_t  x;
    int y;
    char    **options;

    x = 0;
    y = 0;
    options = malloc(sizeof(char *) * data->argc + 1);
    if (!options)
        return ;
    options[data->argc + 1] = '\0';
    while(data->argv[y])
    {
        options[y] = data->argv[y + 1];
        printf("options #%d : %s\n", y, options[y]);
        y++;
    }
    options[y] = '\0';
    while (data->path_names[x])
    {
        data->prog_search = ft_strjoin(data->path_names[x], "/");
        data->prog_search = ft_strjoin(data->prog_search, options[0]);
        if (execve(data->prog_search, options, data->envp) == -1)
        {
            x++;
            printf("path for prog : %s - %s\n", data->path_names[x], data->prog_search);
        }
    }
    return ;
}

void    find_paths(t_vault *data)
{
    size_t  x;
    size_t  slen;

    x = 0;
    while (data->envp[x])
    {
        if (ft_strnstr(data->envp[x], "PATH", 4) != NULL)
        {
            data->paths = ft_strdup(data->envp[x]);
            break ;
        }
        x++;
    }
    data->path_names = ft_split(data->paths, ':');
    slen = ft_strlen(data->path_names[0]);
    data->path_names[0] = ft_substr(data->path_names[0], 5, slen);
    return ;
}

int main(int argc, char **argv, char **envp)
{

    t_vault data;

    data.paths = NULL;
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
    find_paths(&data);
    check_paths(&data); //DEBUG
    find_prog(&data);
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