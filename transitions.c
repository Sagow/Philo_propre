/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:44:50 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/16 13:54:53 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	thinking_to_eating(t_philosopher *philo)
{
	take_forks(philo);
	if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		return ;
	set_val(&(philo->last_meal_mutex), relative_time(philo),
		&(philo->last_meal));
	talk(philo, "is eating");
	philo->nb_meals++;
	my_sleep(relative_time(philo) + philo->data->maxtime.eat, philo);
	put_forks(philo);
}
