/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:35:08 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/14 15:45:22 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_parse_node	*pn_new(char *content);
void			pn_add_back(t_parse_node **pnlist, t_parse_node *n);

/* Build a null-terminated linked list of parse nodes from a file */
// parser.c
t_parse_node	*pn_from_file(const char *filepath);
void			pn_print(t_parse_node *head);
int 			verify_pn_list(t_parse_node *pnlist);

// verify_line_objs.c

int				verify_plane(t_parse_node *n);
int				verify_cylinder(t_parse_node *n);
int				verify_sphere(t_parse_node *n);

// verify_line_other.c

int				verify_camera(t_parse_node *n);
int				verify_light(t_parse_node *n);
int				verify_ambient(t_parse_node *n);
int 			full_empty(char *content);

/* parser helper utilities */
char			*skip_spaces(char *p);
char			*move_to_space(char *str);
int				parse_double_range(char **src, double min, double max, double *out);
int				parse_rgb_triplet(char **src, t_colour *out);

// pnlist_to_world.c

int				construct_world(t_world *w, t_parse_node *n);

// parse_utils.c

t_colour 		atocol(char *str);
t_vec			ato3dcrds(char *str);
int				allowed_chars(char *str);

// parse_line_other.c

t_colour		default_light();
int				parse_ambient(t_world *w, t_parse_node *n);
int				parse_light(t_world *w, t_parse_node *n);
int				parse_camera(t_world *w, t_parse_node *n);

// parse_line_objs.c

int				parse_sphere(t_world *w, t_parse_node *n);

// verify_utils.c

int				verify_colours(t_colour col);
int				verify_3dnorm(t_vec	vec);