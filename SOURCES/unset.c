/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprunet <gprunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:12:14 by tfauve-p          #+#    #+#             */
/*   Updated: 2024/10/30 12:53:58 by gprunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_with_equal(char *args)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	while (args[i] && args[i] != 61)
		i++;
	str = malloc ((i + 2) * 1);
	while (++j < i)
		str[j] = args[j];
	str[j] = 61;
	str[++j] = '\0';
	return (str);
}

void	ft_delete_tab_case(t_struct *data, int i, int a, int b)
{
	char	**tab;
	int		j;

	j = ft_nb_arg(data->env);
	tab = malloc ((j) * 8);
	if (!tab)
		return ;
	while (++a < j)
	{
		if (a == i)
			b = 1;
		else
		{
			if (!tab)
				return (ft_free(tab));
			tab[a - b] = ft_put_string_to_tab(data, tab, (a - b), a);
		}
	}
	tab[a - b] = NULL;
	ft_free(data->env);
	data->env = tab;
}

int	ft_unset_main(t_struct *data, char *args)
{
	char	*str;
	int		i;
	int		j;
	int		a;
	int		b;

	i = 0;
	str = ft_str_with_equal(args);
	j = 0;
	a = -1;
	b = 0;
	if (ft_strncmp(str, "?=", 2) == 1)
		return (0);
	while (data->env[j])
	{
		if (ft_strncmp(str, data->env[j], ft_strlen(str)) == 1)
		{
			ft_delete_tab_case(data, i, a, b);
			break ;
		}
		i++;
		j++;
	}
	free(str);
	return (0);
}

int	ft_unset(t_struct *data, char **args)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (args[1])
	{
		while (args[++i])
		{
			ft_unset_main(data, args[i]);
		}
	}
	return (status);
}

int	ft_unset_pipe(t_struct *data, t_args *arg, char **args, char **path)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (args[1])
	{
		while (args[++i])
		{
			ft_unset_main(data, args[i]);
		}
	}
	ft_free_child(args, data, arg, path);
	exit(status);
}
