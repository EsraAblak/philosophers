/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:49:31 by eablak            #+#    #+#             */
/*   Updated: 2023/01/31 11:49:33 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dead(void *pp)
{
	t_philo	*philo;

	philo = pp;
	while (1)
	{
		sem_wait(philo->mutual->eat);
		if (get_passed_time(philo->last_eat)
			> (unsigned long)philo->mutual->time_to_die)
		{
			my_print(philo, "is dead");
			philo->mutual->is_dead = 1;
			exit(1);
		}
		sem_post(philo->mutual->eat);
		usleep(1000);
		if (philo->mutual->is_dead == 1)
			break ;
	}
	return (NULL);
}

void	get_room(t_philo *philo)
{
	pthread_create(&philo->thread, NULL, &check_dead, philo);
	pthread_detach(philo->thread);
	if (philo->id % 2 == 0)
		usleep(10000);
	while (philo->mutual->is_dead == 0)
	{
		ft_eat(philo);
		if (philo->each_time >= philo->mutual->must_eat
			&& philo->mutual->must_eat != -1)
			break ;
		my_print(philo, "is sleeping");
		time_pass(philo->mutual->time_to_sleep, philo);
		my_print(philo, "is thinking");
	}
	pthread_join(philo->thread, NULL);
	if (philo->mutual->is_dead == 1)
		exit(1);
	exit(0);
}

void	create_proccess(t_mutual *mutual)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < mutual->num_of_philos)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("fork can't open\n");
			exit(1);
		}
		else if (pid == 0)
		{
			mutual->philo[i].pid = pid;
			get_room(&mutual->philo[i]);
		}
		i++;
	}
}
