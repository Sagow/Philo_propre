/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:59:35 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/18 17:12:36 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	get_val(pthread_mutex_t *mutex, int	*val)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_val(pthread_mutex_t *mutex, int val, int *where)
{
	pthread_mutex_lock(mutex);
	*where = val;
	pthread_mutex_unlock(mutex);
}

int	ft_malloc(void **ptr, int size)
{
	*ptr = NULL;
	*ptr = malloc((size_t) size);
	if (*ptr == NULL)
		return (-1);
	return (0);
}

long int	ft_atoi(const char *number)
{
	int			i;
	long int	res;

	if (!number || number[0] < '0' || number[0] > '9')
		return (ERR_ARG_ATOI);
	i = 0;
	res = 0;
	while (number[i] >= '0' && number[i] <= '9')
	{
		res = res * 10 + number[i] - '0';
		i++;
	}
	if (number[i])
		return (-1);
	return (res);
}

int	free_all(t_philosopher *philosophers, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(philosophers[i].die_mutex));
		pthread_mutex_destroy(&(philosophers[i].last_meal_mutex));
		pthread_mutex_destroy(&(philosophers[i].life_obs_mutex));
		i++;
	}
	free(philosophers);
	free(data->forks);
	if (data->observers)
		free(data->observers);
	pthread_mutex_destroy(&(data->death_mutex));
	pthread_mutex_destroy(&(data->all_eaten_mutex));
	pthread_mutex_destroy(&(data->micro));
	free(data);
	return (0);
}
