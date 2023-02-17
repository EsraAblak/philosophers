/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:35:13 by eablak            #+#    #+#             */
/*   Updated: 2023/01/31 13:19:44 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fill_mutual(t_mutual *mutual, char **av)
{
	mutual->num_of_philos = ft_atoi(av[1]);
	mutual->time_to_die = ft_atoi(av[2]);
	mutual->time_to_eat = ft_atoi(av[3]);
	mutual->time_to_sleep = ft_atoi(av[4]);
	mutual->start_time = get_current_time();
	if (av[5])
		mutual->must_eat = ft_atoi(av[5]);
	else
		mutual->must_eat = -1;
}

void	fill_philo(t_philo *philo, t_mutual *mutual)
{
	int	i;

	i = 0;
	while (i < mutual->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].each_time = 0;
		philo[i].last_eat = get_current_time();
		philo[i].mutual = mutual;
		i++;
	}
}

void	create_semaphores(t_mutual *mutual)
{
	const char	*forks;
	const char	*eat;
	const char	*print;

	forks = "/forks";
	eat = "/eat";
	print = "/print";
	sem_unlink(forks);
	sem_unlink(eat);
	sem_unlink(print);
	mutual->forks = sem_open(forks, O_CREAT, 0777, mutual->num_of_philos);
	mutual->eat = sem_open(eat, O_CREAT, 0777, 1);
	mutual->print = sem_open(print, O_CREAT, 0777, 1);
}

void	close_processes(t_mutual*data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->num_of_philos)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < data->num_of_philos)
			{
				kill(data->philo[i].pid, SIGINT);
			}
			break ;
		}
		i++;
	}	
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/eat");
	sem_close(data->eat);
	sem_close(data->forks);
	sem_close(data->print);
}

int	main(int ac, char **av)
{
	t_mutual	*mutual;
	t_philo		*philo;

	if ((ac != 5 && ac != 6) || check_av(ac, av) == 1)
	{
		printf("invalid arugument\n");
		return (1);
	}
	mutual = malloc(sizeof(t_mutual));
	fill_mutual(mutual, av);
	philo = malloc(sizeof(t_philo) * mutual->num_of_philos);
	fill_philo(philo, mutual);
	mutual->philo = philo;
	create_semaphores(mutual);
	create_proccess(mutual);
	close_processes(mutual);
}
