/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_and_circle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:24:17 by osabir            #+#    #+#             */
/*   Updated: 2023/06/19 14:50:52 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_info_to_philo(t_philo **new_philo,
		t_arg *arg, t_info *infox, int i)
{
	t_philo		*philo;

	if (!arg || !new_philo || !*new_philo)
		return ;
	philo = *new_philo;
	philo->eat_limit = arg->eat_limits;
	philo->time_to_die = arg->time_to_die;
	philo->time_to_eat = arg->time_to_eat;
	philo->time_to_sleep = arg->time_to_sleep;
	philo->philo_id = i;
	philo->info = infox;
	philo->next = NULL;
}

void	make_philo(t_philo **philo, t_info *infox, t_arg *arg, int i)
{
	t_philo		*new_philo;
	t_philo		*path;

	if (!philo)
		return ;
	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return ;
	give_info_to_philo(&new_philo, arg, infox, i);
	if (*philo == NULL)
	{
		*philo = new_philo;
		return ;
	}
	path = *philo;
	while (path->next != NULL)
		path = path->next;
	path->next = new_philo;
}

void	make_circle(t_philo **philo)
{
	t_philo		*philo_circle;

	if (!philo || !*philo)
		return ;
	philo_circle = *philo;
	while (philo_circle->next != NULL)
		philo_circle = philo_circle->next;
	philo_circle->next = *philo;
}

void	make_philo_and_circle(t_philo **philo, t_info *infox, t_arg *arg)
{
	t_philo		*philo_fork;
	int			i;

	i = 0;
	if (!philo || !arg)
		return ;
	while (i < arg->number_of_philosophers)
	{
		make_philo(philo, infox, arg, (i + 1));
		i++;
	}
	philo_fork = *philo;
	while (philo_fork)
	{
		pthread_mutex_init(&philo_fork->left_fork, NULL);
		philo_fork = philo_fork->next;
	}
	make_circle(philo);
}
