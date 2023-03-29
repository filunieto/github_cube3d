/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:58:11 by anramire          #+#    #+#             */
/*   Updated: 2023/03/29 02:42:30 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map/Map.h"


extern void	loop_column_up(t_map *map, t_player *player, t_4vertex *sq1, int *auxiliar_values);

extern void	loop_column_down(t_map *map, t_player *player, t_4vertex *sq1, int *auxiliar_values);
extern void loop_draw_map(t_map *map, t_player *player, t_4vertex *sq, int *auxiliar_values);

void	init_map(t_map *map, t_player *player, t_pars *parsing_str)
{
	unsigned int	i;
	unsigned int	j;
	
	i = 0;
	map->semi_len = 150;
	map->width = 40;
	map->height = 40;
	map->rows = parsing_str->nb_endline_map - parsing_str->nb_line_map;
	printf("rows: %d\n", map->rows);
	map->columns = parsing_str->max_leng_map;
	printf("columns: %d\n", map->columns);

	map->map = (char **) malloc((map->rows) * sizeof(char *));
	printf("texture: %s\n", parsing_str->north.path);
	map->NO = mlx_load_png(parsing_str->north.path);
	map->SO = mlx_load_png(parsing_str->south.path);
	map->EA = mlx_load_png(parsing_str->east.path);
	map->WE = mlx_load_png(parsing_str->west.path);
	map->ceil_color = parsing_str->heaven.rgb;
	map->floor_color = parsing_str->ground.rgb;
	
	while (i <= map->rows)
	{	
		// printf("%s\n", parsing_str->map_normal[i]);
		map->map[i] = ft_strdup(parsing_str->map_normal[i]); //we use this strdup!!!!!!!!!!!!,
										  //instead ft_strdup should be used
		j = 0;
		while (parsing_str->map_normal[i][j] != '\0')
		{
			//printf("%c", parsing_str->map_normal[i][j]);
			if (parsing_str->map_normal[i][j] == 'N' || parsing_str->map_normal[i][j] == 'S'
					|| parsing_str->map_normal[i][j] == 'E' || parsing_str->map_normal[i][j] == 'W')
			{
				player->pos_x = (j * map->width) + (map->width / 2);
				player->pos_y = (i * map->height) + (map->height / 2);
				//printf("\nx: %d, y: %d\n", i, j);
				break ;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while(i <= map->rows)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
	free_parser(parsing_str);
}

/*
 *Function to make the main loop drawing map
 * aux=> 0 -> offset_x, 1 -> auxiliar, 2 -> y
 * */

void	draw_map(t_map *map, t_player *player)
{
	unsigned int	rest;
	int				color;
	t_4vertex		sq;
	int				aux[3];
	t_line			line;

	aux[2] = (int)player->pos_y % map->height;
	rest = (map->semi_len - ((int)player->pos_x % map->width)) % map->width;
	aux[1] = 2 * map->semi_len;
	check_outside_colors(map, player, &color, aux);
	insert_point(&(sq.p0), player->center_point->x - map->semi_len,
		player->center_point->y - aux[2]);
	insert_point(&(sq.p1), sq.p0.x + rest, sq.p0.y);
	insert_point(&(sq.p2), sq.p0.x + rest, sq.p0.y + map->height);
	insert_point(&(sq.p3), sq.p0.x, sq.p0.y + map->height);
	draw_square_filled(player->img, &sq, color, 1);
	aux[1] -= rest;
	insert_points_line(&line, &(sq.p0), &(sq.p1));
	draw_column_up(map, player, &line, aux);
	insert_points_line(&line, &(sq.p2), &(sq.p3));
	draw_column_down(map, player, &line, aux);
	while (aux[1] > 0)
		loop_draw_map(map, player, &sq, aux);
}

/*
 * Function to draw the upper part of the column
 *
 * aux=> 0 -> offset_x, 1 -> auxiliar, 2 -> y
 * params=> 0 -> offset_x, 1 -> aux_2, 2 -> aux_3
*/
void	draw_column_up(t_map *map, t_player *player, t_line *line, int *aux)
{	
	t_4vertex		sq1;
	int				color;
	int				params[3];

	params[0] = aux[0];
	params[1] = map->semi_len - aux[2];
	params[2] = (int)player->pos_y - map->height;
	if (params[2] < 0)
		color = 0x000000FF;
	else
		check_color(map->map[params[2] / map->height][params[0]], &color);
	insert_point(&(sq1.p3), line->p0->x, line->p0->y);
	insert_point(&(sq1.p2), line->p1->x, line->p1->y);
	insert_point(&(sq1.p0), sq1.p3.x, sq1.p3.y - map->height);
	insert_point(&(sq1.p1), sq1.p2.x, sq1.p0.y);
	draw_square_filled(player->img, &sq1, color, 1);
	params[1] -= map->height;
	while (params[1] > 0)
		loop_column_up(map, player, &sq1, params);
}

/*
 *Function to draw the down part of the column
 * aux=> 0 -> offset_x, 1 -> auxiliar, 2 -> y
 * params=> 0 -> offset_x, 1 -> aux_2, 2 -> aux_3
 */
void	draw_column_down(t_map *map, t_player *player, t_line *line, int *aux)
{
	t_4vertex	sq1;
	int			color;
	int			params[3];

	params[0] = aux[0];
	params[1] = map->semi_len - (map->height - aux[2]);
	params[2] = (int)player->pos_y + map->height;
	if ((params[2] / map->height) >= map->rows)
		color = 0x000000FF;
	else
		check_color(map->map[params[2] / map->height][params[0]], &color);
	insert_point(&(sq1.p0), line->p1->x, line->p1->y);
	insert_point(&(sq1.p1), line->p0->x, line->p0->y);
	insert_point(&(sq1.p2), sq1.p1.x, sq1.p1.y + map->height);
	insert_point(&(sq1.p3), sq1.p0.x, sq1.p0.y + map->height);
	draw_square_filled(player->img, &sq1, color, 1);
	params[1] -= map->height;
	while (params[1] > 0)
		loop_column_down(map, player, &sq1, params);
}
