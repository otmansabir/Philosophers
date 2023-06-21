/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:52:08 by osabir            #+#    #+#             */
/*   Updated: 2023/06/19 09:17:52 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

typedef struct s_info
{
	pthread_mutex_t		print_status;
	pthread_mutex_t		curr_status;
	pthread_mutex_t		curr_t;
}				t_info;

typedef struct s_arg
{
	long					number_of_philosophers;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					eat_limits;
}				t_arg;

typedef struct s_philo
{
	long					philo_id;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					last_meal;
	long					eat_limit;
	pthread_mutex_t			left_fork;
	struct s_info			*info;
	struct s_philo			*next;
}							t_philo;

void			ft_arg(int ac, char **av, t_arg *arg);
long			ft_atoi(const char *str);
int				check_error(int ac, char **av);
int				check__error(char **av);
int				check_plus(char *s);
int				check_char(char *s);
void			ft_malloc_infox(t_info *infox);
void			give_info_to_philo(t_philo **new_philo,
					t_arg *arg, t_info *infox, int i);
void			make_philo(t_philo **philo, t_info *infox, t_arg *arg, int i);
void			make_circle(t_philo **philo);
void			make_philo_and_circle(t_philo **philo,
					t_info *infox, t_arg *arg);
long			ft_time(void);
void			ft_sleep(time_t sleep, t_philo *philo);
void			print_status(char *s, t_philo *philo);
void			*routine(void *philo);
void			send_phlo_and_wait(t_philo *philo, t_arg *arg);
void			check_die(t_philo **_philo);
void			routine2(t_philo *philo);
int				check_spice_int(char *s);

#endif