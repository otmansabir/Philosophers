/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_and_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:14:08 by osabir            #+#    #+#             */
/*   Updated: 2023/06/19 14:38:18 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_arg(int ac, char **av, t_arg *arg)
{
	if (!av || !arg)
		return ;
	arg->number_of_philosophers = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->eat_limits = ft_atoi(av[5]);
	else
		arg->eat_limits = -1;
}

void	ft_malloc_infox(t_info *infox)
{
	if (!infox)
		return ;
	pthread_mutex_init(&infox->print_status, NULL);
	pthread_mutex_init(&infox->curr_status, NULL);
	pthread_mutex_init(&infox->curr_t, NULL);
}

int	check__error(char **av)
{
	int	i;

	i = 1;
	if (!av)
		return (0);
	while (av[i])
	{
		if (av[i][0] == '\0')
			return (0);
		if (!check_char(av[i++]))
			return (0);
	}
	i = 1;
	while (av[i])
	{
		if (!check_plus(av[i++]))
			return (0);
	}
	return (1);
}

int	check_error(int ac, char **av)
{
	int	i;

	i = 1;
	if (!av || !av[0])
		return (0);
	while (av[i])
	{
		if (!check_spice_int(av[i++]))
			return (0);
	}
	i = 1;
	while (i < 5)
	{
		if (ft_atoi(av[i++]) <= 0)
			return (0);
	}
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (0);
	return (1);
}
