/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:52:51 by eablak            #+#    #+#             */
/*   Updated: 2023/01/31 11:53:32 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_struct
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	long long			start_time;
	int					num_of_philos;
	struct s_sturct2	*philo;
	int					is_dead;
	sem_t				*forks;
	sem_t				*eat;
	sem_t				*print;
}						t_mutual;

typedef struct s_sturct2
{
	int					id;
	int					each_time;
	long long			last_eat;
	t_mutual			*mutual;
	pthread_t			thread;
	pid_t				pid;
}						t_philo;

int						check_av(int ac, char **av);
int						ft_atoi(const char *str);
unsigned long			get_current_time(void);
void					create_proccess(t_mutual *mutual);
unsigned long			get_passed_time(unsigned long time);
void					time_pass(int time, t_philo *philo);
void					ft_eat(t_philo *philo);
void					my_print(t_philo *philo, char *str);
void					close_processes(t_mutual *data);

#endif
