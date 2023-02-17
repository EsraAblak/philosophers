/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:55:06 by eablak            #+#    #+#             */
/*   Updated: 2023/01/26 14:55:08 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef unsigned long long	t_time;

typedef struct t_struct
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				*is_death;
	long long		last_eat;
	long long		start_time;
	int				each_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*death;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	int				num_of_philos;
}	t_philo;

void			fill_philo(t_philo *philo, char **av, int ac, int *is_all_dead);
void			create_mutex(t_philo *philo);
void			create_thread(t_philo *philo);
void			*get_room(void *philo);
int				eat(t_philo *philo);
int				check_dead(t_philo *philo);
void			time_pass(int time);
unsigned long	get_passed_time(unsigned long time);
unsigned long	get_current_time(void);
int				check_av(int ac, char **av);
int				ft_printf(t_philo *philo, char *str);
int				ft_atoi(const char *str);
void			ft_clean(t_philo *philo);
int				check_eat(t_philo *philo);
void			check_cases(t_philo *philo);

#endif
