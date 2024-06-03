/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:07:19 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 17:47:43 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parsecmd(char *input, t_m *m)
{
	t_cmd	*cmd;
	char	*start;
	char	*end;

	start = input;
	if (ft_strlen(input) == 0)
		return (NULL);
	end = input + ft_strlen(input);
	cmd = parselist(&start, end, m);
	if (cmd == NULL)
		m->exit_status = 258;
	return (cmd);
}

t_cmd	*parselist(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parse_and_or(start, end, m);
	if (**start == ';')
	{
		if (cmd == NULL)
			return (NULL);
		(*start)++;
		right_cmd = parselist(start, end, m);
		if (right_cmd == NULL)
			return (NULL);
		cmd = (t_cmd *)listcmd_init(cmd, right_cmd);
		if (right_cmd == NULL)
			return (NULL);
	}
	return (cmd);
}

<<<<<<< HEAD
t_cmd	*parse_and_or(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
=======
t_cmd	*handle_orcmd(char **start, char *end, t_m *m, t_cmd *left_cmd)
{
	t_cmd *cmd;
>>>>>>> f6c2271deb67e8e0089cdd3efbaac3ed0c30397d
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

<<<<<<< HEAD
	cmd = parsepipe(start, end, m);
	if (cmd == NULL)
		return (NULL);
	if (**start == '&' && *(*start + 1) == '&')
	{
		gettoken(start, end, &s_token, &e_token);
		right_cmd = parse_and_or(start, end, m);
		cmd = (t_cmd *)andcmd_init(cmd, right_cmd);
		if (right_cmd == NULL)
			return (NULL);
	}
	else if (**start == '|' && *(*start + 1) == '|')
	{
		gettoken(start, end, &s_token, &e_token);
		right_cmd = parse_and_or(start, end, m);
		cmd = (t_cmd *)orcmd_init(cmd, right_cmd);
		if (right_cmd == NULL)
			return (NULL);
	}
	else if (**start == '&' && *(*start + 1) != '&')
	{
=======
	gettoken(start, end, &s_token, &e_token);
	right_cmd = parse_and_or(start, end, m);
	cmd = (t_cmd *)orcmd_init(left_cmd, right_cmd);
	if (right_cmd == NULL)
		return (NULL);
	return (cmd);
}

t_cmd	*handle_andcmd(char **start, char *end, t_m *m, t_cmd *left_cmd)
{
	t_cmd *cmd;
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

	gettoken(start, end, &s_token, &e_token);
	right_cmd = parse_and_or(start, end, m);
	cmd = (t_cmd *)andcmd_init(left_cmd, right_cmd);
	if (right_cmd == NULL)
		return (NULL);
	return (cmd);
}

t_cmd	*parse_and_or(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;

	cmd = parsepipe(start, end, m);
	if (cmd == NULL)
		return (NULL);
	if (**start == '&' && *(*start + 1) == '&' && *(*start + 2) != '\0')
		return (handle_andcmd(start, end, m, cmd));
	else if (**start == '|' && *(*start + 1) == '|' && *(*start + 2) != '\0')
		return (handle_orcmd(start, end, m, cmd));
	else if ((**start == '&' && *(*start + 1) == '&' && *(*start + 2) == '\0') \
		|| (**start == '|' && *(*start + 1) == '|' && *(*start + 2) == '\0'))
	{
		printf("minishell: syntaxt error: unexpected end of file\n");
		free_memory(cmd);
		return (NULL);
	}
	else if (**start == '&' && *(*start + 1) != '&')
	{
		printf("minishell: syntax error: unexpected token &\n");
>>>>>>> f6c2271deb67e8e0089cdd3efbaac3ed0c30397d
		free_memory(cmd);
		return (NULL);
	}
	return (cmd);
}

<<<<<<< HEAD
=======

>>>>>>> f6c2271deb67e8e0089cdd3efbaac3ed0c30397d
t_cmd	*parsepipe(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parseexec(start, end, m);
	if (**start == '|' && *(*start + 1) != '|')
	{
		if (((t_execcmd *)cmd)->cmdargs == NULL)
		{
			printf("minishell: syntax error: unexpected token near `%c`\n", **start);
			return (NULL);
		}
		(*start)++;
		if (*start == end)
		{
			printf("minishell: syntax error: unexpected end of file.");
			free_memory(cmd);
			return (NULL);
		}
		right_cmd = parsepipe(start, end, m);
		cmd = (t_cmd *)pipecmd_init(cmd, right_cmd);
		if (right_cmd == NULL)
			return (NULL);
	}
	return (cmd);
}
