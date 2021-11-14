/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 22:25:02 by krain             #+#    #+#             */
/*   Updated: 2021/11/14 13:40:27 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	*life_tracking(void *p)
{
	t_philosopher *philo;

	philo = (t_philosopher *)p;
	//printf("angel %d started\n", philo->id);
	while (1)
	{
		if (get_val(&(philo->last_meal_mutex), &(philo->last_meal)) + philo->data->maxtime.death
		<= relative_time(philo))
		{
		//	printf("a\n");
			set_val(&(philo->data->death_mutex), philo->id, &(philo->data->dead));
			break ;
		}
		if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		{
		//	printf("b\n");
			set_val(&(philo->die_mutex), 1, &(philo->die));
			break ;
		}
		usleep(20);
	}
	//printf("angel %d exited\n", philo->id);
	return (NULL);
}

void	observing_philos(t_philosopher *philos, t_data *data)
{
	int	i;
	pthread_t	*observers;

	if (ft_malloc((void **)&observers, sizeof(pthread_t) * data->nb_philos))
		return ;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create((observers + i), NULL, &life_tracking, (philos + i));
		pthread_detach(*(observers + i));
		i++;
	}
}
