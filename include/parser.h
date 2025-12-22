/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:35:08 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/22 15:17:51 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"
# define ERR_SPHERE_DIAMETER "Sphere's diameter can't be negative"
# define ERR_SPHERE_COLOUR "Sphere Colour out of range 0 - 255"
# define ERR_PLANE_COLOUR "Plane Colour out of range 0 - 255"
# define ERR_CYLINDER_COLOUR "Cylinder Colour out of range 0 - 255"
# define ERR_PLANE_ORIENT "Plane orientation vector is not normalised"
# define ERR_CYLINDER_ORIENT "Cylinder orientation vector is not normalised"
# define ERR_AMBIENT_INTENS "Ambient light intensity out of range 0 - 1"
# define ERR_AMBIENT_COLOUR "Ambient light colour out of range 0 - 255"
# define ERR_LIGHT_INTENS "Point Light intensity out of range 0 - 1"
# define ERR_LIGHT_COLOUR "Point Light colour out of range 0 - 255"
# define ERR_CAMERA_ORIENT "Camera orientation vector is not normalised"
# define ERR_CAMERA_FOV "Camera FOV is out of range 0 - 180"

t_parse_node	*pn_new(char *content);
void			pn_add_back(t_parse_node **pnlist, t_parse_node *n);
void			pn_clear(t_parse_node **pnlist);

/* Build a null-terminated linked list of parse nodes from a file */
// parser.c
int				parse_that_jawn(t_world *world, char *filename);

// parser_file.c
t_parse_node	*pn_from_file(const char *filepath);

// parser_utils.c
void			pn_print(t_parse_node *head);
void			cleanup_pn_list(t_parse_node *head, char *ln, int fd);
int				process_line(char **ln, t_parse_node **head);
int				check_file_extension(const char *filepath);

// validate.c
int				verify_pn_list(t_parse_node *pnlist);

// verify_line_objs.c

int				verify_plane(t_parse_node *n);
int				verify_cylinder(t_parse_node *n);
int				verify_sphere(t_parse_node *n);

// verify_line_other.c

int				verify_camera(t_parse_node *n);
int				verify_light(t_parse_node *n);
int				verify_ambient(t_parse_node *n);
int				full_empty(char *content);

/* parser helper utilities */
char			*skip_spaces(char *p);
char			*move_to_space(char *str);
int				parse_double_range(char **src, double min,
					double max, double *out);
int				parse_rgb_triplet(char **src, t_colour *out);

// pnlist_to_world.c

int				construct_world(t_world *w, t_parse_node *n);

// parse_utils.c

t_colour		atocol(char *str);
t_vec			ato3dcrds(char *str);
int				allowed_chars(char *str);
char			*move_next(char *str);
int				parse_error(t_world *w, int error_code, char *err_msg);
char			*move_skip(char *str);

// parse_line_other.c

t_colour		default_light(void);
int				parse_ambient(t_world *w, t_parse_node *n);
int				parse_light(t_world *w, t_parse_node *n);
int				parse_camera(t_world *w, t_parse_node *n);

// parse_line_objs.c (all)

int				parse_sphere(t_world *w, t_parse_node *n);
int				parse_plane(t_world *w, t_parse_node *n);
int				parse_cylinder(t_world *w, t_parse_node *n);
int				parse_sphere_color(t_obj *sp, char *p);
t_mat			get_plane_transform(t_vec centre, t_vec normal);
t_mat			rotation_from_axis_angle(t_vec axis, double angle);
t_material		material_default_pl(void);
t_material		material_default_sp(void);

// verify_utils.c

int				verify_colours(t_colour col);
int				verify_3dnorm(t_vec	vec);

#endif