/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 20:26:37 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 20:30:52 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char	*move_next(char *str)
{
	str = skip_spaces(str);
	str = move_to_space(str);
	str = skip_spaces(str);
	return (str);
}

char	*move_skip(char *str)
{
	str = move_to_space(str);
	str = skip_spaces(str);
	return (str);
}

int	parse_error(t_world *w, int error_code, char *err_msg)
{
	printf("Error: %s\n", err_msg);
	w->parser.error_flag++;
	return (error_code);
}
