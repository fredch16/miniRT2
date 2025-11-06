/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:35:08 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/06 13:16:06 by fredchar         ###   ########.fr       */
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