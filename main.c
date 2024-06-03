/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:04:02 by bcai              #+#    #+#             */
/*   Updated: 2024/06/03 14:48:54 by eprzybyl         ###   ########.fr       */
=======
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:04:02 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 09:43:43 by bcai             ###   ########.fr       */
>>>>>>> f6c2271deb67e8e0089cdd3efbaac3ed0c30397d
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lastset_run(t_m *m)
{
	last_set(m->final_tree, m);
	runcmd(m->final_tree, m);
}

int	main(int argc, char **argv, char **envp)
{
	t_m					m;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
<<<<<<< HEAD
	
	initial_setup(&m, envp);
	
=======
	initial_setup(&m, envp);
>>>>>>> f6c2271deb67e8e0089cdd3efbaac3ed0c30397d
	while (1)
	{
		signal_tracking(&sa, &m);
		m.input = readline("minishell$ ");
		if (!m.input)
		{
			lastfree_restore();
			exit(1);
		}
		add_history(m.input);
		update_history_file(&m);
		m.input = expand_input_check(m.input, &m);
		partial_reinit_m(&m);
		m.final_tree = parsecmd(m.input, &m);
		if (m.final_tree != NULL)
			lastset_run(&m);
		free(m.input);
	}
}
