/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnuncio- <gnuncio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:12 by acesar-l          #+#    #+#             */
/*   Updated: 2023/06/03 23:14:29 by gnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_starting_orientation(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'N')
	{
		data->player.vertical_dir = NORTH;
		data->player.rotation_angle = 0.5 * PI;
	}
	if (data->map[y][x] == 'S')
	{
		data->player.vertical_dir = SOUTH;
		data->player.rotation_angle = 1.5 * PI;
	}
	if (data->map[y][x] == 'E')
	{
		data->player.horizontal_dir = EAST;
		data->player.rotation_angle = 0;
	}
	if (data->map[y][x] == 'W')
	{
		data->player.horizontal_dir = WEST;
		data->player.rotation_angle = PI;
	}
}

void	set_player_starting_position(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (data->map[y][x])
		{
			if ((data->map[y][x] == 'N')
				|| (data->map[y][x] == 'S')
				|| (data->map[y][x] == 'W')
				|| (data->map[y][x] == 'E'))
			{
				data->player.x = x;
				data->player.y = y;
				set_player_starting_orientation(data, x, y);
			}
			x++;
		}
		y++;
	}
	data->player.x += TILE_SIZE * MINIMAP_SCALE / 2;
	data->player.y += TILE_SIZE * MINIMAP_SCALE / 2;
}

void	set_player_info(t_data *data)
{
	data->player.ray = 0;
	data->player.ray_angle = 0;
	data->player.walk_direction = 0;
	data->player.turn_direction = 0;
	data->player.walk_speed = 100;
	data->player.turn_speed = 45 * (PI / 180);
}

static void	get_map_info(t_data *data)
{
	int	longest_line;
	int	y;
	int	x;

	longest_line = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
			x++;
		if (x > longest_line)
			longest_line = x;
		y++;
	}
	data->columns = longest_line;
	data->rows = y;
}

void	set_textures_info(t_data *data, char **cubfile_content)
{
	data->no_txtr.path = get_texture_path(cubfile_content, "NO ");
	if (!data->no_txtr.path)
	{
		ft_free_str_array(cubfile_content);
		error_manager(ERROR_MALLOC, MALLOC_ERROR, data);
	}
	data->so_txtr.path = get_texture_path(cubfile_content, "SO ");
	if (!data->so_txtr.path)
	{
		ft_free_str_array(cubfile_content);
		error_manager(ERROR_MALLOC, MALLOC_ERROR, data);
	}
	data->ea_txtr.path = get_texture_path(cubfile_content, "EA ");
	if (!data->ea_txtr.path)
	{
		ft_free_str_array(cubfile_content);
		error_manager(ERROR_MALLOC, MALLOC_ERROR, data);
	}
	data->we_txtr.path = get_texture_path(cubfile_content, "WE ");
	if (!data->we_txtr.path)
	{
		ft_free_str_array(cubfile_content);
		error_manager(ERROR_MALLOC, MALLOC_ERROR, data);
	}
}

t_data	*setup_data(char **cubfile_content)
{
	t_data	*data;

	data = create_data();
	data->map = ft_copy_str_array(&cubfile_content[NUM_OF_ELEM_BEFORE_MAP]);
	if (!data->map)
		error_manager(ERROR_MALLOC, MALLOC_ERROR, data);
	get_map_info(data);
	set_textures_info(data, cubfile_content);
	ft_free_str_array(cubfile_content);
	get_map_info(data);
	set_player_starting_position(data);
	set_player_info(data);
	return (data);
}
