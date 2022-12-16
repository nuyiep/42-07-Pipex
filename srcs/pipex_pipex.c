/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:39:40 by plau              #+#    #+#             */
/*   Updated: 2022/12/16 20:59:32 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* To get the "PATH=" line from envp */
void	get_path(t_prg *prg, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			prg->path = ft_split(path, ':');
			free (path);
		}
		i++;
	}
}

/* Check cmd access */
void	cmd_access(t_prg *prg, int i)
{
	int		j;
	char	*temp;
	char	*cmd;

	j = -1;
	while (++j < prg->npath)
	{
		temp = ft_strjoin(prg->path[j], "/");
		if (i == 2)
			cmd = ft_strjoin(temp, prg->cmd1[0]);
		if (i == 3)
			cmd = ft_strjoin(temp, prg->cmd2[0]);
		if (access(cmd, F_OK) == 0)
		{
			if (i == 2)
				prg->cmd_1st = cmd;
			if (i == 3)
				prg->cmd_2nd = cmd;
			free(temp);
			return ;
		}
		free(cmd);
		free(temp);
	}
	exit_error("Invalid command");
}

/* Find cmd in PATH */
void	get_cmdpath(t_prg *prg, char *av, int i)
{
	if (!av || (ft_strcmp(av, "") == 0))
		exit_error("Empty command");
	if (i == 2)
		prg->cmd1 = ft_split(av, ' ');
	if (i == 3)
		prg->cmd2 = ft_split(av, ' ');
	find_npath(prg);
	cmd_access(prg, i);
}

/* Free everything */
void	free_all(t_prg *prg)
{
	free(prg->cmd_1st);
	free(prg->cmd_2nd);
	ft_freesplit(prg->cmd1);
	ft_freesplit(prg->cmd2);
	ft_freesplit(prg->path);
}

/* Main function for piping */
void	pipex(t_prg *prg, char **av, char **envp)
{
	get_path(prg, envp);
	get_cmdpath(prg, av[2], 2);
	get_cmdpath(prg, av[3], 3);
	create_child(prg, envp);
	free_all(prg);
}
