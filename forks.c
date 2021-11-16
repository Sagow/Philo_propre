/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:22:21 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/16 13:52:22 by krain            ###   ########.fr       */
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

void	even(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left);
	talk(philo, "has taken a fork");
	if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		pthread_mutex_unlock(philo->left);
	else
	{
		pthread_mutex_lock(philo->right);
		talk(philo, "has taken a fork");
	}
}

void	odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right);
	talk(philo, "has taken a fork");
	if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		pthread_mutex_unlock(philo->right);
	else
	{
		pthread_mutex_lock(philo->left);
		talk(philo, "has taken a fork");
	}
}

void	take_forks(t_philosopher *philo)
{
	if (get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		return ;
	if (philo->id % 2 == 0)
		even(philo);
	else
		odd(philo);
}

void	put_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
