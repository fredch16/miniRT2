/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_other.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:22:59 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/07 18:30:58 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minimath.h"

int	parse_ambient(t_world *w, t_parse_node *n)
{
	printf("PARSING AMBIENT\n");
	char		*p;
	double		intensity;

	if (!w || !n || !n->content)
		return (-1);
	p = n->content + 1;
	intensity = ft_atod(p);
	if (intensity < 0.0 || intensity > 1.0)
		return (printf("Intensity of Ambient Light our of range 0 - 1\n"), -1);
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	w->ambient = atocol(p);
	w->ambient = colour_scm(intensity, w->ambient);
	// verify colours innit
	return (0);
}

int	parse_light(t_world *w, t_parse_node *n)
{
	printf("parsing light\n");
	char		*p;

	if (!w || !n || !n->content)
		return (-1);
	p = n->content + 1;
	w->light.position = ato3dcrds(p);
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	w->light.intensity = ft_atod(p);
	if (w->light.intensity < 0.0 || w->light.intensity > 1.0)
		return (printf("Intensity of Ambient Light our of range 0 - 1\n"), -1);
	p = move_to_space(p);
	w->light.colour = atocol(p);
	printf("Light colour:\n");
	print_colour(w->light.colour);
	return (0);
}