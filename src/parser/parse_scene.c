/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:30:00 by swied            #+#    #+#             */
/*   Updated: 2025/12/15 15:30:00 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/libft/libft.h"
#include "../../include/libft/get_next_line.h"
#include <stdlib.h>

static int	parse_line(char *line, t_world *world)
{
	if (!line || !*line || *line == '\n')
		return (0);
	while (*line && ft_isspace(*line))
		line++;
	if (!*line || *line == '\n')
		return (0);
	if (line[0] == 'A' && ft_isspace(line[1]))
		return (parse_ambient(line, world));
	else if (line[0] == 'L' && ft_isspace(line[1]))
		return (parse_light(line, world));
	else if (line[0] == 'C' && ft_isspace(line[1]))
		return (parse_camera(line, world));
	else if (line[0] == 's' && line[1] == 'p' && ft_isspace(line[2]))
		return (parse_sphere(line, world));
	else if (line[0] == 'p' && line[1] == 'l' && ft_isspace(line[2]))
		return (parse_plane(line, world));
	else if (line[0] == 'c' && line[1] == 'y' && ft_isspace(line[2]))
		return (parse_cylinder(line, world));
	else
	{
		parser_error("Unknown element type");
		return (-1);
	}
}

static int	validate_scene(t_world *world)
{
	if (world->parser.A_count == 0)
	{
		parser_error("Missing ambient light definition");
		return (-1);
	}
	if (world->parser.L_count == 0)
	{
		parser_error("Missing light definition");
		return (-1);
	}
	if (world->parser.C_count == 0)
	{
		parser_error("Missing camera definition");
		return (-1);
	}
	if (!world->obj_list)
	{
		parser_error("No objects in scene");
		return (-1);
	}
	return (0);
}

void	free_world(t_world *world)
{
	t_obj	*curr;
	t_obj	*next;

	if (!world)
		return ;
	curr = world->obj_list;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	world->obj_list = NULL;
}

/* Parse scene from .rt file */
int	parse_scene(const char *filename, t_world *world)
{
	int		fd;
	char	*line;
	int		ret;

	if (!filename || !world)
		return (-1);
	if (ft_strlen(filename) < 3 || ft_strcmp(filename + ft_strlen(filename) - 3,
			".rt") != 0)
	{
		parser_error("Invalid file extension (must be .rt)");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		parser_error("Failed to open file");
		return (-1);
	}
	ft_bzero(world, sizeof(t_world));
	line = get_next_line(fd);
	while (line)
	{
		ret = parse_line(line, world);
		free(line);
		if (ret < 0)
		{
			close(fd);
			free_world(world);
			return (-1);
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (validate_scene(world) < 0)
	{
		free_world(world);
		return (-1);
	}
	return (0);
}
