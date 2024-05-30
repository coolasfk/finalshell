/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_set1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:57:24 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 19:01:01 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_temp2(char **temp)
{
	while (**temp && **temp != '/' && (**temp != '$' || (**temp == '$' && (*(*temp
						+ 1) == ' ' || *(*temp + 1) == '\0' || *(*temp
						+ 1) == '"' || *(*temp + 1) == '$'))))
		(*temp)++;
}

char	*replace_d(t_execcmd *ecmd, int i)
{
	char	*temp;
	char	*s_cpy;
	char	*e_cpy;
	char	*first_part;
	char	*new;

	new = NULL;
	temp = ecmd->cmd_args[i];
	s_cpy = temp;
	e_cpy = temp + ft_strlen(temp) - 1;
	while (*temp && *(temp + 1))
	{
		update_temp2(&temp);
		//test
		printf("1.after update_temp2 temp %c\n", *temp);
		//
		first_part = m_sub(s_cpy, 0, temp - s_cpy, NULL);
		new = get_newstr2(temp, e_cpy, ecmd, first_part);
		temp = new;
		update_temp2(&temp);
				//test
		printf("2.after update_temp2 temp %c\n", *temp);
		//
		s_cpy = new;
		e_cpy = new + ft_strlen(new) - 1;
		//test
		printf("new %s\n", new);
		//
	}
	if (!new)
		new = ft_strdup(ecmd->cmd_args[i]);
	return (new);
}

void	parse_left_right(t_cmd *left, t_cmd *right, t_m *m)
{
	last_set(left, m);
	last_set(right, m);
}

void	last_set(t_cmd *cmd, t_m *m)
{
	int	type;

	if (cmd == NULL)
		return ;
	type = cmd->type;
	if (type == EXEC)
		set_exec(cmd, m);
	else if (type == REDIR)
		last_set((((t_redircmd *)cmd)->cmd), m);
	else if (type == HEREDOC)
	{
		m->heredoc_flag = 1;
		((t_heredoc *)cmd)->envp = m->envp;
		last_set((((t_heredoc *)cmd)->cmd), m);
	}
	else if (type == PIPE)
		parse_left_right(((t_pipecmd *)cmd)->left, ((t_pipecmd *)cmd)->right,
			m);
	else if (type == LIST)
		parse_left_right(((t_listcmd *)cmd)->left, ((t_listcmd *)cmd)->right,
			m);
	else if (type == AND)
		parse_left_right(((t_and *)cmd)->left, ((t_and *)cmd)->right, m);
	else if (type == OR)
		parse_left_right(((t_or *)cmd)->left, ((t_or *)cmd)->right, m);
}

void	get_strlen(char *temp, int *i)
{
	*i = 0;
	while (temp[*i] && temp[*i + 1] != ' ' && temp[*i + 1] != '"' && \
		temp[*i + 1] != '\0' && ft_strchr("!@#$%^", temp[*i + 1]) == 0)
		(*i)++;
}
