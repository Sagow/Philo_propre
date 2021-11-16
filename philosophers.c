/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:07:24 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/16 15:09:29 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	suicide(t_philosopher *philo)
{
	if (!get_val(&(philo->die_mutex), &(philo->die)))
		return (0);
	return (1);
}

void	my_sleep(int target, t_philosopher *philo)
{
	while (relative_time(philo) < target
		&& !get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		usleep(15);
}

void	*philosophing(void *p)
{
	t_data			*data;
	t_philosopher	*philo;

	philo = (t_philosopher *)p;
	data = philo->data;
	while (data->maxtime.max_meals == -1 || (philo)->nb_meals
		< data->maxtime.max_meals)
	{
		if (suicide((philo)))
			break ;
		thinking_to_eating(philo);
		if (suicide((philo)))
			break ;
		talk(philo, "is sleeping");
		my_sleep(relative_time(philo) + data->maxtime.sleep, philo);
		if (suicide((philo)))
			break ;
		talk(philo, "is thinking");
	}
	set_val(&(philo->life_mutex), 0, &(philo->alive));
	return (NULL);
}

void	start_philos(t_philosopher *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].alive = 1;
		philos[i].nb_meals = 0;
		philos[i].die = 0;
		pthread_mutex_init(&philos[i].die_mutex, NULL);
		set_forks(philos + i, data);
		philos[i].data = data;
		pthread_mutex_init(&philos[i].life_mutex, NULL);
		philos[i].last_meal = 0;
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		philos[i].perso_start = current_time(data);
		pthread_create(&(philos[i].thread), NULL, &philosophing, philos + i);
		pthread_detach(philos[i].thread);
		i++;
	}
	philos[i].id = 0;
}

void	one_philo(t_data *data)
{
	printf("%d %d has taken a fork\n", current_time(data), 1);
	usleep(data->maxtime.death * 1000);
	printf("%d %d died\n", current_time(data), 1);
}

int	main(int ac, char **av)
{
	t_philosopher	*philos;
	t_data			*data;
	int				i;
	int				survivors;

	if (ft_malloc((void **)&data, sizeof(t_data)))
		return (1);
	if (parsing(ac, av, &philos, data))
		return (1);
	if (data->nb_philos == 1)
		one_philo(data);
	else
	{
		start_philos(philos, data);
		observing_philos(philos, data);
		while (!data->dead)
			usleep(10);
		pthread_mutex_lock(&(data->micro));
		printf("%d %d died\n", current_time(data), data->dead);
		pthread_mutex_unlock(&(data->micro));
		survivors = 1;
		while (survivors)
		{
			survivors = 0;
			i = -1;
			while (philos[++i].id)
				survivors += get_val(&(philos[i].life_mutex), &(philos[i].alive));
		}
	}
	free_all(philos, data);
	return (0);
}
