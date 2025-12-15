/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:30:00 by swied            #+#    #+#             */
/*   Updated: 2025/12/15 15:30:00 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/libft/libft.h"
#include <stdlib.h>

static void	add_object(t_world *world, t_obj *obj)
{
	t_obj	*curr;

	if (!world->obj_list)
		world->obj_list = obj;
	else
	{
		curr = world->obj_list;
		while (curr->next)
			curr = curr->next;
		curr->next = obj;
	}
}

/* Parse sphere: sp position(x,y,z) diameter R,G,B
 * Example: sp -0.5,1,0.5 2 25,255,128 */
int	parse_sphere(char *line, t_world *world)
{
	char		**tokens;
	t_vec		pos;
	double		diameter;
	t_colour	colour;
	t_obj		*sphere;

	tokens = ft_split_whitespace(line + 2);
	if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
	{
		parser_error("Invalid sphere format");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_vector(tokens[0], &pos) < 0)
	{
		parser_error("Invalid sphere position");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_double(tokens[1], &diameter) < 0 || diameter <= 0.0)
	{
		parser_error("Invalid sphere diameter");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_colour(tokens[2], &colour) < 0)
	{
		parser_error("Invalid sphere colour");
		ft_free_array(tokens);
		return (-1);
	}
	sphere = malloc(sizeof(t_obj));
	if (!sphere)
	{
		ft_free_array(tokens);
		return (-1);
	}
	sphere->type = OT_SPHERE;
	sphere->transform = scaling(diameter / 2.0, diameter / 2.0, diameter / 2.0);
	sphere->transform = mat_mul_mat(translation(pos.x, pos.y, pos.z),
		sphere->transform);
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.3;
	sphere->material.shininess = 200.0;
	sphere->material.colour = colour;
	sphere->next = NULL;
	add_object(world, sphere);
	ft_free_array(tokens);
	return (0);
}

/* Parse plane: pl position(x,y,z) normal(x,y,z) R,G,B
 * Example: pl 0,0,0 0,1,0 255,230,230 */
int	parse_plane(char *line, t_world *world)
{
	char		**tokens;
	t_vec		pos;
	t_vec		normal;
	t_colour	colour;
	t_obj		*plane;
	t_vec		up;
	t_vec		axis;
	double		angle;
	double		x_comp;
	double		y_comp;
	double		z_comp;
	double		s;
	double		c;
	double		t;

	tokens = ft_split_whitespace(line + 2);
	if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
	{
		parser_error("Invalid plane format");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_vector(tokens[0], &pos) < 0)
	{
		parser_error("Invalid plane position");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_vector(tokens[1], &normal) < 0)
	{
		parser_error("Invalid plane normal");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_colour(tokens[2], &colour) < 0)
	{
		parser_error("Invalid plane colour");
		ft_free_array(tokens);
		return (-1);
	}
	plane = malloc(sizeof(t_obj));
	if (!plane)
	{
		ft_free_array(tokens);
		return (-1);
	}
	plane->type = OT_PLANE;
	normal = tuple_norm(vector(normal.x, normal.y, normal.z));
	up = vector(0, 1, 0);
	if (fabs(normal.y - 1.0) < 0.001)
		plane->transform = mat_idt();
	else if (fabs(normal.y + 1.0) < 0.001)
		plane->transform = rotation_x(M_PI);
	else
	{
		axis = tuple_cro(up, normal);
		axis = tuple_norm(axis);
		angle = acos(tuple_dot(up, normal));
		x_comp = axis.x;
		y_comp = axis.y;
		z_comp = axis.z;
		s = sin(angle);
		c = cos(angle);
		t = 1.0 - c;
		plane->transform = (t_mat){{
			{t * x_comp * x_comp + c, t * x_comp * y_comp + z_comp * s,
				t * x_comp * z_comp - y_comp * s, 0},
			{t * x_comp * y_comp - z_comp * s, t * y_comp * y_comp + c,
				t * y_comp * z_comp + x_comp * s, 0},
			{t * x_comp * z_comp + y_comp * s, t * y_comp * z_comp - x_comp * s,
				t * z_comp * z_comp + c, 0},
			{0, 0, 0, 1}
		}};
	}
	plane->transform = mat_mul_mat(translation(pos.x, pos.y, pos.z),
		plane->transform);
	plane->material.ambient = 0.1;
	plane->material.diffuse = 0.7;
	plane->material.specular = 0.3;
	plane->material.shininess = 200.0;
	plane->material.colour = colour;
	plane->next = NULL;
	add_object(world, plane);
	ft_free_array(tokens);
	return (0);
}

/* Parse cylinder: cy position(x,y,z) axis(x,y,z) diameter height R,G,B
 * Example: cy 0,0,0 0.0,1.0,0 2 5 100,100,255 */
int	parse_cylinder(char *line, t_world *world)
{
	char		**tokens;
	t_vec		pos;
	t_vec		axis;
	double		diameter;
	double		height;
	t_colour	colour;
	t_obj		*cyl;
	t_vec		up;
	t_vec		rot_axis;
	double		angle;
	double		x_comp;
	double		y_comp;
	double		z_comp;
	double		s;
	double		c;
	double		t;
	t_mat		scale;

	tokens = ft_split_whitespace(line + 2);
	if (!tokens || !tokens[0] || !tokens[1] || !tokens[2] || !tokens[3]
		|| !tokens[4])
	{
		parser_error("Invalid cylinder format");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_vector(tokens[0], &pos) < 0)
	{
		parser_error("Invalid cylinder position");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_vector(tokens[1], &axis) < 0)
	{
		parser_error("Invalid cylinder axis");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_double(tokens[2], &diameter) < 0 || diameter <= 0.0)
	{
		parser_error("Invalid cylinder diameter");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_double(tokens[3], &height) < 0 || height <= 0.0)
	{
		parser_error("Invalid cylinder height");
		ft_free_array(tokens);
		return (-1);
	}
	if (parse_colour(tokens[4], &colour) < 0)
	{
		parser_error("Invalid cylinder colour");
		ft_free_array(tokens);
		return (-1);
	}
	cyl = malloc(sizeof(t_obj));
	if (!cyl)
	{
		ft_free_array(tokens);
		return (-1);
	}
	cyl->type = OT_CYLINDER;
	cyl->min_y = 0;
	cyl->max_y = height;
	cyl->closed = true;
	axis = tuple_norm(vector(axis.x, axis.y, axis.z));
	up = vector(0, 1, 0);
	if (fabs(axis.y - 1.0) < 0.001)
		cyl->transform = mat_idt();
	else if (fabs(axis.y + 1.0) < 0.001)
		cyl->transform = rotation_x(M_PI);
	else
	{
		rot_axis = tuple_cro(up, axis);
		rot_axis = tuple_norm(rot_axis);
		angle = acos(tuple_dot(up, axis));
		x_comp = rot_axis.x;
		y_comp = rot_axis.y;
		z_comp = rot_axis.z;
		s = sin(angle);
		c = cos(angle);
		t = 1.0 - c;
		cyl->transform = (t_mat){{
			{t * x_comp * x_comp + c, t * x_comp * y_comp + z_comp * s,
				t * x_comp * z_comp - y_comp * s, 0},
			{t * x_comp * y_comp - z_comp * s, t * y_comp * y_comp + c,
				t * y_comp * z_comp + x_comp * s, 0},
			{t * x_comp * z_comp + y_comp * s, t * y_comp * z_comp - x_comp * s,
				t * z_comp * z_comp + c, 0},
			{0, 0, 0, 1}
		}};
	}
	scale = scaling(diameter / 2.0, 1, diameter / 2.0);
	cyl->transform = mat_mul_mat(cyl->transform, scale);
	cyl->transform = mat_mul_mat(translation(pos.x, pos.y, pos.z),
		cyl->transform);
	cyl->material.ambient = 0.1;
	cyl->material.diffuse = 0.7;
	cyl->material.specular = 0.3;
	cyl->material.shininess = 200.0;
	cyl->material.colour = colour;
	cyl->next = NULL;
	add_object(world, cyl);
	ft_free_array(tokens);
	return (0);
}
