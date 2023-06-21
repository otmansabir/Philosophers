/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:51:37 by osabir            #+#    #+#             */
/*   Updated: 2023/06/19 14:55:02 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_char(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[0] == '\0')
			return (0);
		if ((s[i] < '0' || s[i] > '9') && s[i] != '+' && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_spice_int(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ' && (s[i + 1] >= '0' && s[i + 1] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_plus(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9' && (s[i + 1] == '+' || s[i + 1] == '-'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_clean(t_philo **_philo, t_info *infox, t_arg *arg)
{
	t_philo		*philo;
	int			i;

	if (!_philo || !arg || !infox)
		return ;
	philo = *_philo;
	i = 0;
	while ((i < arg->number_of_philosophers) && (philo))
	{
		pthread_mutex_destroy(&philo->left_fork);
		philo = philo->next;
		i++;
	}
	pthread_mutex_destroy(&infox->curr_status);
	pthread_mutex_destroy(&infox->curr_t);
	pthread_mutex_destroy(&infox->print_status);
	free(infox);
}

int	main(int ac, char **av)
{
	t_arg		arg;
	t_info		*infox;
	t_philo		*philo;

	if ((ac == 5 || ac == 6) && check_error(ac, av) && check__error(av))
	{
		infox = NULL;
		philo = NULL;
		ft_arg(ac, av, &arg);
		infox = malloc(sizeof(t_info));
		if (!infox)
			return (0);
		ft_malloc_infox(infox);
		make_philo_and_circle(&philo, infox, &arg);
		send_phlo_and_wait(philo, &arg);
		ft_clean(&philo, infox, &arg);
	}
	else
		write(2, "Error\n", 6);
	return (0);
}
