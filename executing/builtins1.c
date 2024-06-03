/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:45:38 by bcai              #+#    #+#             */
/*   Updated: 2024/06/03 19:07:49 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (ft_strncmp(cmd_args[0], "cd", 2) == 0)
		builtin_cd(cmd, m);
	else if (ft_strncmp(cmd_args[0], "echo", 4) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd_args[0], "pwd", 3) == 0)
		builtin_pwd(cmd, m);
	else if (ft_strncmp(cmd_args[0], "export", 6) == 0)
		builtin_export(cmd, m);
	else if (ft_strchr(cmd_args[0], '='))
		set_envvar(cmd, m);
	else if (ft_strncmp(cmd_args[0], "unset", 5) == 0)
		builtin_unset(cmd, m);
	else if (ft_strncmp(cmd_args[0], "env", 3) == 0)
		builtin_env(cmd, m);
	else if (ft_strncmp(cmd_args[0], "exit", 4) == 0)
		builtin_exit(cmd, m);
}

void	update_pwd(t_m *m, t_cmd *cmd)
{
	char	*cwd;
	char	*buffer;
	size_t	size;

	(void)cmd;
	size = 1024;
	while (1)
	{
		buffer = safe_malloc(size, CHAR, m->final_tree);
		cwd = getcwd(buffer, size);
		if (cwd)
		{
			free(buffer);
			break ;
		}
		else
			resize_or_free(buffer, m, &size);
	}
	update_envvars(ft_strdup("PWD"), ft_strdup(cwd), 1);
	set_oldpwd(m, cwd);
}

void	set_oldpwd(t_m *m, char *add_pwd)
{
	t_gl	*gl;
	t_list	*ptr;

	(void)m;
	gl = get_gl();
	ptr = gl->oldpwd_list;
	if (gl->oldpwd_list == NULL || ft_strcmp((char *)ptr->content,
			add_pwd) != 0)
		build_files_list(&gl->oldpwd_list, add_pwd);
	if (gl->oldpwd_list->next != NULL)
	{
		update_envvars(ft_strdup("OLDPWD"),
			ft_strdup(gl->oldpwd_list->next->content), 1);
	}
}
void	builtin_cd(t_cmd *cmd, t_m *m)
{
	char		**cmd_args;
	t_envvar	*home;

	(void)m;
	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (cmd_args[1] == NULL || ft_strcmp(cmd_args[1], "~") == 0)
	{
		home = get_envvar("HOME");
		if (chdir(home->value) != 0)
			perror("cd: ");
	}
	else if (cmd_args[1] == NULL || ft_strcmp(cmd_args[1], "-") == 0)
	{
		cd_back_case(m);
		return ;
	}
	else
	{
		if (chdir(cmd_args[1]) != 0)
		{
			perror("cd: ");
			m->exit_status = 1;
		}
	}
	update_pwd(m, cmd);
}

void	cd_back_case(t_m *m)
{
	t_gl	*gl;

	gl = get_gl();
	if (gl->oldpwd_list->next == NULL)
	{
		printf("cd: OLDPWD not set\n");
		return ;
	}
	update_envvars(ft_strdup("PWD"), ft_strdup(get_envvar("OLDPWD")->value), 1);
	if (chdir(gl->oldpwd_list->next->content) != 0)
		perror("cd: ");
	set_oldpwd(m, gl->oldpwd_list->next->content);
}

void	builtin_echo(t_cmd *cmd)
{
	char	**cmd_args;
	int		n_flag;
	int		i;
	t_qflag	*cqflags;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	cqflags = ((t_execcmd *)cmd)->cqflags->next;
	if (cmd_args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	i = 1;
	n_flag = 0;
	if (cmd_args[1] && ft_strcmp(cmd_args[1], "-n") == 0)
		update_eles(&n_flag, &cqflags, &i);
	while (cmd_args[i] != NULL)
	{
		print_helper(cmd_args, &i, cqflags);
		cqflags = cqflags->next;
	}
	((t_execcmd *)cmd)->m->exit_status = 0;
	if (n_flag == 0)
		printf("\n");
}

void	resize_or_free(char *buffer, t_m *m, size_t *size)
{
	free(buffer);
	if (errno == ERANGE)
		(*size) = (*size) * 2;
	else
	{
		perror("getcmd");
		free_tree(m->final_tree, m);
		lastfree_restore();
		exit(1);
	}
}
