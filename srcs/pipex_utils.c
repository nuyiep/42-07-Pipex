/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:30:46 by plau              #+#    #+#             */
/*   Updated: 2022/12/16 20:59:25 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Initalize struct */
void	init_struct(t_prg *prg, int ac)
{
	if (ac < 5)
		print_error("Invalid number of arguments");
	prg->fd_in = 0;
	prg->fd_out = 0;
	prg->ac = ac;
	prg->npath = 0;
	prg->cmd_1st = NULL;
	prg->cmd_2nd = NULL;
	prg->path = NULL;
	prg->cmd1 = NULL;
	prg->cmd2 = NULL;
}

/* Check whether can open input and output file */
void	check_open(t_prg *prg, char **av)
{
	prg->fd_in = open(av[1], O_RDONLY);
	if (prg->fd_in < 0)
		exit_error(av[1]);
	prg->fd_out = open(av[prg->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (prg->fd_out < 0)
		exit_error(av[prg->ac - 1]);
}

/* Prints specific error message */
int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_printf("\n");
	exit (1);
}

/* Exit and prints error */
void	exit_error(char *str)
{
	perror(str);
	exit(1);
}

/* Find number of path */
void	find_npath(t_prg *prg)
{
	int	k;

	k = 0;
	while (prg->path[k] != NULL)
		k++;
	prg->npath = k;
}
