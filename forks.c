/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:22:21 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/13 23:36:25 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	set_forks(t_philosopher *philo, t_data *data)
{
	philo->left = data->forks + (philo->id - 1);
	if (philo->id == data->nb_philos)
		philo->right = data->forks;
	else
		philo->right = data->forks + philo->id;
}

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		talk(philo, "has taken a fork");
		pthread_mutex_lock(philo->right);
		talk(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		talk(philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		talk(philo, "has taken a fork");
	}

}

void	put_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
