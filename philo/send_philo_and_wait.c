/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_philo_and_wait.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:18:15 by osabir            #+#    #+#             */
/*   Updated: 2023/06/19 15:06:55 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_die(t_philo **_philo)
{
	t_philo		*philo;

	if (!_philo)
		return ;
	philo = *_philo;
	while (philo && philo->info)
	{
		pthread_mutex_lock(&philo->info->curr_t);
		if (philo->eat_limit == 0)
			break ;
		if (ft_time() - philo->last_meal >= philo->time_to_die)
		{
			pthread_mutex_lock(&philo->info->print_status);
			printf("%ld %ld is dead\n", ft_time(),
				philo->philo_id);
			break ;
		}
		pthread_mutex_unlock(&philo->info->curr_t);
		philo = philo->next;
		usleep(100);
	}
}

void	send_phlo_and_wait(t_philo *philo, t_arg *arg)
{
	pthread_t	*thread;
	int			i;

	if (!philo || !arg)
		return ;
	thread = malloc(arg->number_of_philosophers * sizeof(pthread_t));
	if (!thread)
		return ;
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		if (pthread_create(&thread[i], NULL, &routine, philo))
			printf("error\n");
		if (pthread_detach(thread[i]))
			printf("error\n");
		philo = philo->next;
		i++;
	}
	check_die(&philo);
	free(thread);
}
