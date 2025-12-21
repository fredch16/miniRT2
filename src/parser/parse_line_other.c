/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_other.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:22:59 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/22 00:07:36 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minimath.h"

t_colour	default_light(void)
{
	t_colour	col;

	col.blue = 1;
	col.red = 1;
	col.green = 1;
	return (col);
}

int	parse_ambient(t_world *w, t_parse_node *n)
{
	char	*p;
	double	intensity;

	if (!w || !n || !n->content)
		return (-1);
	p = n->content + 1;
	intensity = ft_atod(p);
	if (intensity < 0.0 || intensity > 1.0)
		return (parse_error(w, -1, ERR_AMBIENT_INTENS));
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	w->ambient = atocol(p);
	if (verify_colours(w->ambient) < 0)
		return (parse_error(w, -1, ERR_AMBIENT_COLOUR));
	w->ambient = colour_scm(intensity, w->ambient);
	w->parser.a_count++;
	return (0);
}

int	parse_light(t_world *w, t_parse_node *n)
{
	char	*p;

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
		return (parse_error(w, -1, ERR_LIGHT_INTENS));
	p = move_to_space(p);
	w->light.colour = atocol(p);
	if (verify_colours(w->light.colour) < 0)
		return (parse_error(w, -1, ERR_LIGHT_COLOUR));
	w->parser.l_count++;
	return (0);
}

static int	compute_camera_vectors(char *p, t_vec pos, t_vec *to_out,
	t_vec *up_out)
{
	t_vec	norm;

	norm = ato3dcrds(p);
	if (verify_3dnorm(norm) < 0)
		return (-1);
	norm.x = norm.x * -1;
	if (equal_tuple(norm, vector(0, 1, 0)))
		*up_out = vector(0, 0, -1);
	else if (equal_tuple(norm, vector(0, -1, 0)))
		*up_out = vector(0, 0, 1);
	else
		*up_out = vector(0, 1, 0);
	*to_out = tuple_add(pos, norm);
	to_out->w = 1;
	return (0);
}

int	parse_camera(t_world *w, t_parse_node *n)
{
	char	*p;
	t_vec	pos;
	t_vec	to;
	t_vec	up;

	if (!w || !n || !n->content)
		return (-1);
	p = n->content + 1;
	p = skip_spaces(p);
	pos = ato3dcrds(p);
	pos.w = 1;
	p = move_skip(p);
	if (compute_camera_vectors(p, pos, &to, &up) < 0)
		return (parse_error(w, -1, ERR_CAMERA_ORIENT));
	p = move_skip(p);
	if (ft_atod(p) < 0 || ft_atod(p) > 180)
		return (parse_error(w, -1, ERR_CAMERA_FOV));
	w->camera = camera(WIDTH, HEIGHT, (M_PI / 180.0) * ft_atod(p));
	w->camera.transform = view_transform(pos, to, up);
	w->parser.c_count++;
	return (0);
}
