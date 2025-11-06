/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:36:31 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/05 15:54:18 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	verify_content(char *content)
{
	if (ft_strncmp(content, "A ", 2) == 0)
		return (verify_ambient(content));
	if (ft_strncmp(content, "C ", 2) == 0)
		return (verify_camera(content));
	if (ft_strncmp(content, "L ", 2) == 0)
		return (verify_light(content));
	if (ft_strncmp(content, "sp ", 3) == 0)
		return (verify_sphere(content));
	if (ft_strncmp(content, "pl ", 3) == 0)
		return (verify_plane(content));
	if (ft_strncmp(content, "cy ", 3) == 0)
		return (verify_cylinder(content));
	return (-1); // unknown ID
}

int verify_pn_list(t_parse_node *pnlist)
{
	t_parse_node	*tmp;
	
	tmp = pnlist;
	while (tmp)
	{
		if (verify_content == -1)
			return (-1);
		tmp = tmp->next;
	}
}