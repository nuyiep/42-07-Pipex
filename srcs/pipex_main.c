/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:29:36 by plau              #+#    #+#             */
/*   Updated: 2022/12/16 20:59:36 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Main function */
int	main(int ac, char **av, char **envp)
{
	t_prg	prg;

	init_struct(&prg, ac);
	check_open(&prg, av);
	pipex(&prg, av, envp);
	close(prg.fd_in);
	close(prg.fd_out);
	return (0);
}
