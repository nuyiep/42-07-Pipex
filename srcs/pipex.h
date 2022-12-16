/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:12 by plau              #+#    #+#             */
/*   Updated: 2022/12/16 20:59:16 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/srcs/libft.h"
# include "../libft/srcs/get_next_line.h"
# include "../libft/srcs/ft_printf.h"
# include <sys/types.h>
# include <stdio.h>

typedef struct s_prg
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	int		ac;
	int		npath;
	char	*cmd_1st;
	char	*cmd_2nd;
	char	**path;
	char	**cmd1;
	char	**cmd2;
}	t_prg;

/* Helper */
void	init_struct(t_prg *prg, int ac);
void	check_open(t_prg *prg, char **av);
int		print_error(char *str);
void	exit_error(char *str);
void	find_npath(t_prg *prg);

/* Piping */
void	pipex(t_prg *prg, char **av, char **envp);

/* Fork */
void	create_child(t_prg *prg, char **envp);

#endif
