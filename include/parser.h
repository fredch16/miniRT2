/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:30:00 by swied            #+#    #+#             */
/*   Updated: 2025/12/15 15:30:00 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"
# include "types.h"
# include <fcntl.h>
# include <stdio.h>

/* parse_scene.c */
int			parse_scene(const char *filename, t_world *world);
void		free_world(t_world *world);

/* parse_utils.c */
int			parse_vector(char *str, t_vec *vec);
int			parse_colour(char *str, t_colour *colour);
int			parse_double(char *str, double *value);
int			skip_whitespace(char **str);
char		**ft_split_whitespace(char *str);

/* parse_elements.c */
int			parse_ambient(char *line, t_world *world);
int			parse_light(char *line, t_world *world);
int			parse_camera(char *line, t_world *world);

/* parse_objects.c */
int			parse_sphere(char *line, t_world *world);
int			parse_plane(char *line, t_world *world);
int			parse_cylinder(char *line, t_world *world);

/* Error handling */
void		parser_error(const char *msg);

#endif
