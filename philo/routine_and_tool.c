/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_and_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:19:37 by osabir            #+#    #+#             */
/*   Updated: 2023/06/19 14:59:08 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	struct timeval	_time;
	long			curr_time;
	static long		start_time;

	gettimeofday(&_time, NULL);
	curr_time = _time.tv_sec * 1000 + _time.tv_usec / 1000;
	if (!start_time)
		start_time = curr_time;
	return (curr_time - start_time);
}

void	ft_sleep(time_t sleep, t_philo *philo)
{
	long	start;

	if (!philo || !philo->info)
		return ;
	pthread_mutex_lock(&philo->info->curr_status);
	start = ft_time();
	pthread_mutex_unlock(&philo->info->curr_status);
	while (ft_time() - start < sleep)
		usleep(100);
}

void	print_status(char *s, t_philo *philo)
{
	if (!s || !philo || !philo->info)
		return ;
	pthread_mutex_lock(&philo->info->print_status);
	printf("%ld %ld %s\n", ft_time(), philo->philo_id, s);
	pthread_mutex_unlock(&philo->info->print_status);
}

void	routine2(t_philo *philo)
{
	if (!philo || !philo->next || !philo->info)
		return ;
	pthread_mutex_lock(&philo->left_fork);
	print_status("has taken a fork", philo);
	pthread_mutex_lock(&philo->next->left_fork);
	print_status("has taken a fork", philo);
	print_status("is eating", philo);
	pthread_mutex_lock(&philo->info->curr_t);
	philo->last_meal = ft_time();
	pthread_mutex_unlock(&philo->info->curr_t);
	ft_sleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->next->left_fork);
	print_status("is sleeping", philo);
	ft_sleep(philo->time_to_sleep, philo);
	print_status("is thinking", philo);
	pthread_mutex_lock(&philo->info->curr_t);
	if (philo->eat_limit > 0)
		philo->eat_limit--;
	pthread_mutex_unlock(&philo->info->curr_t);
}

void	*routine(void *_philo)
{
	t_philo			*philo;

	philo = (t_philo *)_philo;
	if (!philo || !philo->info)
		return (NULL);
	if (philo->philo_id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&philo->info->curr_t);
		philo->last_meal = ft_time();
	pthread_mutex_unlock(&philo->info->curr_t);
	while (1)
	{
		routine2(philo);
		pthread_mutex_lock(&philo->info->curr_t);
		if (philo->eat_limit == 0)
		{
			pthread_mutex_unlock(&philo->info->curr_t);
			break ;
		}
		pthread_mutex_unlock(&philo->info->curr_t);
	}
	return (NULL);
}
