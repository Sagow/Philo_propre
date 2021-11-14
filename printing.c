/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:20:53 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/14 13:28:53 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	talk(t_philosopher *philo, char *thing)
{
	if (!get_val(&(philo->data->death_mutex), &(philo->data->dead)))
	{
		pthread_mutex_lock(&(philo->data->micro));
		if (!(philo->data->dead))
			printf("%d %d %s\n", current_time(philo->data), philo->id, thing);
		pthread_mutex_unlock(&(philo->data->micro));
	}
}
/*
void	announce_end(t_data *data)
{
	struct timeval	timestamp;

	pthread_mutex_lock(&(data->micro));
	gettimeofday(&timestamp, NULL);
	printf("%d all philosophers have eaten %d time(s)\n",
		current_time(data), data->maxtime.max_meals);
	pthread_mutex_unlock(&(data->micro));
}
*/