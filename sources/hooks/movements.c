/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnuncio- <gnuncio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:27:49 by gnuncio-          #+#    #+#             */
/*   Updated: 2023/06/19 23:27:53 by gnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_utils(t_data *data);
static void	turn_utils(t_data *data);

int	move_and_turn(t_data *data)
{
	if (data->player.move == UP && ft_iswall(data->map,
			data->player.y - WALK_SPEED * sin(data->player.angle),
			data->player.x + WALK_SPEED * cos(data->player.angle)) == 1)
	{
		data->player.x += WALK_SPEED * cos(data->player.angle);
		data->player.y -= WALK_SPEED * sin(data->player.angle);
	}
	else if (data->player.move == DOWN && ft_iswall (data->map,
			data->player.y + WALK_SPEED * sin(data->player.angle),
			data->player.x - WALK_SPEED * cos(data->player.angle)) == 1)
	{
		data->player.x -= WALK_SPEED * cos(data->player.angle);
		data->player.y += WALK_SPEED * sin(data->player.angle);
	}
	move_utils (data);
	turn_utils (data);
	render(data);
	return (0);
}

static void	move_utils(t_data *data)
{
	if (data->player.move == RIGHT && ft_iswall(data->map,
			data->player.y + WALK_SPEED * cos(data->player.angle),
			data->player.x + WALK_SPEED * sin(data->player.angle)) == 1)
	{
		data->player.x += WALK_SPEED * sin(data->player.angle);
		data->player.y += WALK_SPEED * cos(data->player.angle);
	}
	else if (data->player.move == LEFT && ft_iswall(data->map,
			data->player.y - WALK_SPEED * cos(data->player.angle),
			data->player.x - WALK_SPEED * sin(data->player.angle)) == 1)
	{
		data->player.x -= WALK_SPEED * sin(data->player.angle);
		data->player.y -= WALK_SPEED * cos(data->player.angle);
	}
}

static void	turn_utils(t_data *data)
{
	if (data->player.turn == LEFT)
		data->player.angle = normalize_radian_angle(data->player.angle
				+ (PI / 90));
	if (data->player.turn == RIGHT)
		data->player.angle = normalize_radian_angle(data->player.angle
				- (PI / 90));
}
