/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:44:50 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/18 18:55:01 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	thinking_to_eating(t_philosopher *philo)
{
	if (take_forks(philo))
		return ;
	set_val(&(philo->last_meal_mutex), relative_time(philo),
		&(philo->last_meal));
	talk(philo, "is eating");
	philo->nb_meals++;
	/*if (philo->data->maxtime.max_meals > 0 && philo->nb_meals
		== philo->data->maxtime.max_meals)
	{
		pthread_mutex_lock(&(philo->data->all_eaten_mutex));
		philo->data->all_eaten++;
		pthread_mutex_unlock(&(philo->data->all_eaten_mutex));
	}*/
	my_sleep(relative_time(philo) + philo->data->maxtime.eat, philo);
	put_forks(philo);
}
