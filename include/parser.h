/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:35:08 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/05 13:02:52 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_parse_node	*pn_new(char *content);
void			pn_add_back(t_parse_node **pnlist, t_parse_node *n);

/* Build a null-terminated linked list of parse nodes from a file */
t_parse_node	*pn_from_file(const char *filepath);
void		pn_print(t_parse_node *head);