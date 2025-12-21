/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_other.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:22:59 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 17:04:20 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minimath.h"

t_colour default_light()
{
	t_colour col;

	col.blue = 1;
	col.red = 1;
	col.green = 1;
	return (col);
}

int parse_ambient(t_world *w, t_parse_node *n)
{
	printf("PARSING AMBIENT\n");
	char *p;
	double intensity;

	if (!w || !n || !n->content)
		return (-1);
	p = n->content + 1;
	intensity = ft_atod(p);
	if (intensity < 0.0 || intensity > 1.0)
		return (w->parser.error_flag++, printf("Intensity of Ambient Light out of range 0 - 1\n"), -1);
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	w->ambient = atocol(p);
	if (verify_colours(w->ambient) < 0)
		return (w->parser.error_flag++, printf("Ambient Light out of range 0 - 255\n"), -1);
	w->ambient = colour_scm(intensity, w->ambient);
	w->parser.a_count++;
	return (0);
}

int parse_light(t_world *w, t_parse_node *n)
{
	printf("parsing light\n");
	char *p;

	if (!w || !n || !n->content)
		return (-1);
	p = n->content + 1;
	w->light.position = ato3dcrds(p);
	w->light.position.w = 1;
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	w->light.intensity = ft_atod(p);
	if (w->light.intensity < 0.0 || w->light.intensity > 1.0)
		return (printf("Intensity of Ambient Light out of range 0 - 1\n"), -1);
	p = move_to_space(p);
	w->light.colour = atocol(p);
	if (verify_colours(w->light.colour) < 0)
		return (w->parser.error_flag++, printf("Point Light out of range 0 - 255\n"), -1);
	printf("Light colour:\n");
	print_colour(w->light.colour);
	w->parser.l_count++;
	return (0);
}

int parse_camera(t_world *w, t_parse_node *n)
{
	printf("Parsing camera\n");
	char *p;
	t_vec pos;
	t_vec up;
	t_vec to;
	t_camera cam;
	double FOV;
	if (!w || !n || !n->content)
		return (-1);
	p = n->content + 1;
	p = skip_spaces(p);
	pos = ato3dcrds(p);
	pos.w = 1;
	p = move_to_space(p);
	p = skip_spaces(p);
	to = ato3dcrds(p);
	if (equal_tuple(to, vector(0, 1, 0)))
		up = (vector(0, 0, -1));
	else if (equal_tuple(to, vector(0, -1, 0)))
		up = (vector(0, 0, 1));
	else
		up = (vector(0, 1, 0));
	print_vec4(to);
	to = tuple_norm(to);
	if (verify_3dnorm(to) < 0)
		return (w->parser.error_flag++, printf("Camera vector not normalised\n"), -1);
	to = tuple_add(pos, to);
	to.w = 1;
	p = move_to_space(p);
	p = skip_spaces(p);
	FOV = ft_atod(p);
	printf("FOV parsed as |%10.5f|\n", FOV);
	if (FOV < 0 || FOV > 180)
		return (printf("FOV out of range |0-180|\n"), -1);
	cam = camera(WIDTH, HEIGHT, (M_PI / 180.0) * FOV);
	// if normal business
	// cam.transform = view_transform(pos, to, vector(0, 1, 0));
	// if camera is pointing down or up need new vector of
	cam.transform = view_transform(pos, to, up);

	w->camera = cam;
	print_mat(w->camera.transform);
	w->parser.c_count++;
	return (0);
}
