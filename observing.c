/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 22:25:02 by krain             #+#    #+#             */
/*   Updated: 2021/11/16 13:54:26 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	*life_tracking(void *p)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p;
	while (1)
	{
		if (get_val(&(philo->last_meal_mutex), &(philo->last_meal))
			+ philo->data->maxtime.death <= relative_time(philo))
		{
			set_val(&(philo->die_mutex), 1, &(philo->die));
			set_val(&(philo->data->death_mutex), philo->id,
				&(philo->data->dead));
			break ;
		}
		if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		{
			set_val(&(philo->die_mutex), 1, &(philo->die));
			break ;
		}
		usleep(20);
	}
	return (NULL);
}

void	observing_philos(t_philosopher *philos, t_data *data)
{
	int			i;
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
