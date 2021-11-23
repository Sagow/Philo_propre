/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:03:43 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/18 16:56:10 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "color.h"

# define ERR_ARG_NB -1
# define ERR_ARG_ATOI -2
# define ERR_MALLOC -3
# define ERR_PARSING -4
# define ERR_MUTEX_INIT -5

typedef struct s_timespan
{
	int				death;
	int				eat;
	int				sleep;
	int				max_meals;
}					t_timespan;

typedef struct s_data
{
	int				start;
	pthread_mutex_t	*forks;
	int				nb_philos;
	t_timespan		maxtime;
	pthread_mutex_t	micro;
	int				dead;
	pthread_mutex_t	death_mutex;
	int				all_eaten;
	pthread_mutex_t	all_eaten_mutex;
	pthread_t		*observers;
}					t_data;

typedef struct s_philosopher
{
	int				id;
	int				alive;
	pthread_mutex_t	life_mutex;
	int				obs;
	pthread_mutex_t	life_obs_mutex;
	int				die;
	pthread_mutex_t	die_mutex;
	int				last_meal;
	pthread_mutex_t	last_meal_mutex;
	int				nb_meals;
	//pthread_mutex_t	nb_meals_mutex;
	int				perso_start;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_data			*data;
}					t_philosopher;

typedef struct s_tracking_activity
{
	int				fork;
	int				eating;
	int				sleeping;
	int				thinking;
}					t_tracking_activity;

/*
** error_messages.c
*/
int		err_arg_nb(int ac);
int		err_arg_nbphilo(char *number);
int		err_arg_time(void);

/*
** forks.c
*/
void	set_forks(t_philosopher *philo, t_data *data);
int		take_forks(t_philosopher *philo);
void	put_forks(t_philosopher *philo);

/*
** observing.c
*/
void	observing_philos(t_philosopher *philos, t_data *data);

/*
** parsing.c
*/
int		parsing(int ac, char **av, t_philosopher **philosophers, t_data *data);

/*
** printing.c
*/
void	talk(t_philosopher *philo, char *thing);
void	announce_death(t_philosopher *philo);
void	announce_end(t_data *data);

/*
** transitions.c
*/
void	thinking_to_eating(t_philosopher *philo);
void	my_sleep(int target, t_philosopher *philo);

/*
** utils_process.c
*/
int		suicide(t_philosopher *philo);
void	my_sleep(int target, t_philosopher *philo);
void	one_philo(t_data *data);

/*
** utils_time.c
*/
int		current_time(t_data *data);
int		relative_time(t_philosopher *philo);

/*
** utils.c
*/
int		get_val(pthread_mutex_t *mutex, int	*val);
void	set_val(pthread_mutex_t *mutex, int val, int *where);
int		ft_malloc(void **ptr, int size);
int		ft_atoi(const char *number);
int		free_all(t_philosopher *philosophers, t_data *data);

#endif