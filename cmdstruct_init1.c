/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdstruct_init1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:55:41 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 20:39:02 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execcmd	*execcmd_init(t_m *m)
{
	t_execcmd	*execcmd;

	execcmd = (t_execcmd *)safe_malloc(1, EXEC, NULL);
	execcmd->type = EXEC;
	execcmd->cmd_args = NULL;
	execcmd->cmdargs = NULL;
	execcmd->path_prob = 0;
	execcmd->qflags = NULL;
	execcmd->cqflags = NULL;
	execcmd->m = m;
	return (execcmd);
}

t_redircmd	*redircmd_init(t_cmd *subcmd, char *s_token, size_t size)
{
	t_redircmd	*redircmd;
	redircmd = (t_redircmd *)safe_malloc(1, REDIR, subcmd);
	redircmd->type = REDIR;
	redircmd->cmd = subcmd;
	redircmd->file = safe_malloc(size+2, CHAR, (t_cmd *)redircmd);	
	ft_strlcpy_special(redircmd->file, s_token, size);
	return (redircmd);
}

size_t	ft_strlcpy_special(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;

	if (dstsize < 1)
		return (ft_strlen(src));
	i = 0;
	k = 0;
	while (src[k] && i < dstsize - 1)
	{
		if(src[k] == '/' || src[k] == '\\')
		{
			k++;
			dstsize += 10;
		}
		dst[i] = src[k];
		i++;
		k++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

void	init_mode_fd(t_redircmd *rcmd, int mode, int fd)
{
	rcmd->mode = mode;
	rcmd->fd = fd;
}

t_heredoc	*hdinit(t_cmd *subcmd, char *s_token, size_t size, int fd)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)safe_malloc(1, HEREDOC, subcmd);
	heredoc->type = HEREDOC;
	heredoc->cmd = subcmd;
	heredoc->delimiter = safe_malloc(size, CHAR, (t_cmd *)heredoc);
	ft_strlcpy(heredoc->delimiter, s_token, size);
	heredoc->fd = fd;
	heredoc->is_quoted = 0;
	heredoc->tmp_file = NULL;
	return (heredoc);
}
