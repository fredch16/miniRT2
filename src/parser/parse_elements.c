/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:30:00 by swied            #+#    #+#             */
/*   Updated: 2025/12/15 15:30:00 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/libft/libft.h"
#include <math.h>

/* Parse ambient lighting: A ratio R,G,B
 * Example: A 0.2 255,255,255 */
int	parse_ambient(char *line, t_world *world)
{
	char	**tokens;
	double	ratio;

	if (world->parser.A_count > 0)
	{
		parser_error("Multiple ambient light definitions");
		return (-1);
	}
	tokens = ft_split_whitespace(line + 1);
	if (!tokens || !tokens[0] || !tokens[1])
	{
		parser_error("Invalid ambient light format");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_double(tokens[0], &ratio) < 0 || ratio < 0.0 || ratio > 1.0)
	{
		parser_error("Invalid ambient ratio");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_colour(tokens[1], &world->ambient) < 0)
	{
		parser_error("Invalid ambient colour");
		ft_free_array(tokens);
		return (-1);
	}
	world->ambient.red *= ratio;
	world->ambient.green *= ratio;
	world->ambient.blue *= ratio;
	world->parser.A_count++;
	ft_free_array(tokens);
	return (0);
}

/* Parse point light: L position(x,y,z) intensity R,G,B
 * Example: L 0.0,10.0,10.0 0.8 255,255,255 */
int	parse_light(char *line, t_world *world)
{
	char	**tokens;
	t_vec	pos;
	double	intensity;

	if (world->parser.L_count > 0)
	{
		parser_error("Multiple light definitions");
		return (-1);
	}
	tokens = ft_split_whitespace(line + 1);
	if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
	{
		parser_error("Invalid light format");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_vector(tokens[0], &pos) < 0)
	{
		parser_error("Invalid light position");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_double(tokens[1], &intensity) < 0 || intensity < 0.0 || intensity > 1.0)
	{
		parser_error("Invalid light intensity");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_colour(tokens[2], &world->light.colour) < 0)
	{
		parser_error("Invalid light colour");
		ft_free_array(tokens);
		return (-1);
	}
	world->light.position = point(pos.x, pos.y, pos.z);
	world->light.intensity = intensity;
	world->parser.L_count++;
	ft_free_array(tokens);
	return (0);
}

/* Parse camera: C position(x,y,z) orientation(x,y,z) fov
 * Example: C 0,0,-50 0,0,1 70 */
int	parse_camera(char *line, t_world *world)
{
	char	**tokens;
	t_vec	pos;
	t_vec	orient;
	double	fov;
	double	half_view;
	double	aspect;

	if (world->parser.C_count > 0)
	{
		parser_error("Multiple camera definitions");
		return (-1);
	}
	tokens = ft_split_whitespace(line + 1);
	if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
	{
		parser_error("Invalid camera format");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_vector(tokens[0], &pos) < 0)
	{
		parser_error("Invalid camera position");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_vector(tokens[1], &orient) < 0)
	{
		parser_error("Invalid camera orientation");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_double(tokens[2], &fov) < 0 || fov < 0.0 || fov > 180.0)
	{
		parser_error("Invalid camera FOV");
		ft_free_array(tokens);
		return (-1);
	}
	world->camera.hsize = WIDTH;
	world->camera.vsize = HEIGHT;
	world->camera.field_of_view = fov * M_PI / 180.0;
	orient = tuple_norm(vector(orient.x, orient.y, orient.z));
	world->camera.transform = view_transform(
		point(pos.x, pos.y, pos.z),
		point(pos.x + orient.x, pos.y + orient.y, pos.z + orient.z),
		vector(0, 1, 0)
	);
	half_view = tan(world->camera.field_of_view / 2.0);
	aspect = (double)WIDTH / (double)HEIGHT;
	if (aspect >= 1)
	{
		world->camera.half_width = half_view;
		world->camera.half_height = half_view / aspect;
	}
	else
	{
		world->camera.half_width = half_view * aspect;
		world->camera.half_height = half_view;
	}
	world->camera.pixel_size = (world->camera.half_width * 2) / WIDTH;
	world->parser.C_count++;
	ft_free_array(tokens);
	return (0);
}
