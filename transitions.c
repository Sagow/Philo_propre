/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:44:50 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/13 23:14:43 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	thinking_to_eating(t_philosopher *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->last_meal = timeval_to_milli(&time) - philo->data->start;
	talk((t_philosopher *)philo, "is eating");
	((t_philosopher *)philo)->nb_meals++;
}
