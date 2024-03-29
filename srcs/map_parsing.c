/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:58:18 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/20 13:49:50 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	checkname(const char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len <= 4 || av[len - 4] != '.' || av[len - 3] != 'b'
		|| av[len - 2] != 'e' || av[len - 1] != 'r')
		sl_error("invalid map file name");
}

void	mapchecker(t_map *map)
{
	int	i;

	i = -1;
	while (map->data[++i])
		if (ft_strlen(map->data[i]) != map->width)
			sl_error("map not rectangular");
	i = -1;
	while (map->data[0][++i])
	{
		if (map->data[0][i] != '1')
			sl_error("invaild map: map not surrounded by walls");
		if (map->data[map->length - 1][i] != '1')
			sl_error("invaild map: map not surrounded by walls");
	}
	i = 0;
	while (++i < map->length)
		if (map->data[i][0] != '1' || map->data[i][map->width - 1] != '1')
			sl_error("invaild map: map not surrounded by walls");
	object_parser(map);
	check_path(map);
}

char	**map_parser(const char *av)
{
	int		fd;
	char	**out;
	char	*line;
	int		i;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		sl_error("problem reading map");
	line = get_next_line(fd);
	out = NULL;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		out = ft_realloc(out, i * sizeof(char *), (i + 1) * sizeof(char *));
		out[i] = line;
		++i;
		line = get_next_line(fd);
	}
	close(fd);
	out = ft_realloc(out, i * sizeof(char *), (i + 1) * sizeof(char *));
	out[i] = NULL;
	return (out);
}

t_map	*map_init(const char *av)
{
	t_map	*map;
	int		i;

	i = 0;
	checkname(av);
	map = galloc(sizeof(t_map));
	map->points = NULL;
	map->score_needed = 0;
	map->data = map_parser(av);
	map->width = ft_strlen(map->data[0]);
	while (map->data[i])
		++i;
	map->length = i;
	mapchecker(map);
	return (map);
}
