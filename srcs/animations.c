/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:39:30 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/13 11:46:59 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mini_render(t_mlx *game)
{
	int	x;
	int	y;

	x = game->player->pos->x;
	y = game->player->pos->y;
	put_image(game, game->map->floor.img, x, y);
	put_player(game, game->player);
}

int	animate(t_mlx *game)
{
	game->player->sprites = game->player->sprites->next;
	game->player->frame = game->player->sprites->content->img;
	mini_render(game);
	return (1);
}