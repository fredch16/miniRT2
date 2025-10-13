/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:17:55 by fredchar          #+#    #+#             */
/*   Updated: 2025/03/13 17:12:20 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

// functions

int		ft_printf(const char *text, ...);

// printer functions

int		print_char(char c);
int		print_str(char *str);
int		print_nbr_base(int nbr, char *base);
int		print_nbr_base_u(unsigned int nbr, char *base);
int		print_pointer(void *ptr);

#endif