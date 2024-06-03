/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:57:04 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 10:03:32 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_intype(char **start)
{
	int	type;

	type = **start;
	(*start)++;
	if (**start == '<')
	{
		type = 'h';
		(*start)++;
	}
	return (type);
}

int	check_unexpected_token1(char **start)
{
	if (ft_strchr("<!#&(); ", **start))
	{
		printf("minishell: syntax error near unexpected token %c\n", **start);
		return (127);
	}
	if (**start == '.' && ft_strchr("& ", *(*start + 1)))
	{
		printf("minishell: .: Is a directory\n");
		return (127);
	}
	if (**start == '.' && ft_strchr("<()", *(*start + 1)))
	{
		printf("minishell: syntax error near unexpected token %c\n", *(*start + 1));
		return (127);
	}
	return (0);
}

int	check_unexpected_token2(char **start)
{
	if (**start == '.' && *(*start + 1) == '.' && ft_strchr("& ", *(*start + 2)))
	{
		printf("minishell: ..: Is a directory\n");
		return (127);
	}
	if (**start == '.' && *(*start + 1) == '.' && ft_strchr("<()", *(*start + 2)))
	{
		printf("minishell: syntax error near unexpected token %c\n", *(*start + 2));
		return (127);
	}
	return (0);
}

int	check_unexpected_token3(char **start)
{
	if (ft_strchr("<>!#&(); ", **start))
	{
		printf("minishell: syntax error near unexpected token %c\n", **start);
		return (127);
	}
	if (**start == '.' && ft_strchr("& ", *(*start + 1)))
	{
		printf("minishell: .: Is a directory\n");
		return (127);
	}
	if (**start == '.' && ft_strchr("<()", *(*start + 1)))
	{
		printf("minishell: syntax error near unexpected token %c\n", *(*start + 1));
		return (127);
	}
	return (0);
}

int	get_outtype(char **start)
{
	int	type;

	type = **start;
	(*start)++;
	if (check_unexpected_token1(start) == 127 || check_unexpected_token2(start) == 127)
		return (127);	
	if (**start == '>')
	{
		type = '+';
		(*start)++;
		if (check_unexpected_token2(start) == 127 || check_unexpected_token3(start) == 127)
			return (127);
	}
	return (type);
}

/*
int	get_atype(char **start, char *end)
{
	int		type;
	int		quote_num;
	t_gl	*gl;

	gl = get_gl();
	quote_num = 0;
	type = 'a';
	//test
	printf("in get_atype, start %c\n", **start);
	//
	while (*start < end && !ft_strchr(gl->spaces, **start)
		&& !ft_strchr(gl->signs, **start) && **start != '"' && **start != 39)
	{
		if (**start == '"' || **start == 39)
		{
			//test
			printf("for what case?\n");
			//
			quote_num++;
		}
		(*start)++;
	}
	if (quote_num == 1)
	{
		while (*start < end && (**start != '"' || **start != 39))
			(*start)++;
	}
	//test
	printf("after get_atype start %c before start %c\n", **start, *(*start - 1));
	//
	return (type);
}*/
