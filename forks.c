/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:22:21 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/18 16:07:56 by krain            ###   ########.fr       */
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

int	even(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left);
	talk(philo, "has taken a fork");
	pthread_mutex_lock(philo->right);
	if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		return (1);
	}
	talk(philo, "has taken a fork");
	return (0);
}

int	odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right);
	talk(philo, "has taken a fork");
	pthread_mutex_lock(philo->left);
	if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		return (1);
	}
	talk(philo, "has taken a fork");
	return (0);
}

int	take_forks(t_philosopher *philo)
{
	if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		return (1);
	if (philo->id % 2 == 0)
		return (even(philo));
	return (odd(philo));
}

void	put_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
