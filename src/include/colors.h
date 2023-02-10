/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:52:22 by stefan            #+#    #+#             */
/*   Updated: 2023/02/10 19:33:38 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define WHITE 255, 255, 255, 255
# define BLACK 0, 0, 0, 255
# define RED 255, 0, 0, 255
# define GREEN 0, 255, 0, 255
# define BLUE 0, 0, 255, 255
# define YELLOW 255, 255, 0, 255
# define MAGENTA 255, 0, 255, 255
# define CYAN 0, 255, 255, 255
# define ORANGE 255, 165, 0, 255
# define PURPLE 128, 0, 128, 255
# define PINK 255, 192, 203, 255
# define BROWN 165, 42, 42, 255
# define GRAY 128, 128, 128, 255
# define DARK_GRAY 169, 169, 169, 255
# define LIGHT_GRAY 211, 211, 211, 255
# define DARK_RED 139, 0, 0, 255
# define DARK_GREEN 0, 100, 0, 255
# define DARK_BLUE 0, 0, 139, 255
# define DARK_YELLOW 139, 139, 0, 255
# define DARK_MAGENTA 139, 0, 139, 255
# define DARK_CYAN 0, 139, 139, 255
# define DARK_ORANGE 255, 140, 0, 255
# define DARK_PURPLE 128, 0, 128, 255
# define DARK_PINK 255, 20, 147, 255
# define DARK_BROWN 165, 42, 42, 255
# define DARK_GRAY 169, 169, 169, 255
# define LIGHT_RED 255, 0, 0, 255
# define LIGHT_GREEN 0, 255, 0, 255
# define LIGHT_BLUE 0, 0, 255, 255
# define LIGHT_YELLOW 255, 255, 0, 255
# define LIGHT_MAGENTA 255, 0, 255, 255
# define LIGHT_CYAN 0, 255, 255, 255
# define LIGHT_ORANGE 255, 165, 0, 255
# define LIGHT_PURPLE 128, 0, 128, 255
# define LIGHT_PINK 255, 192, 203, 255
# define LIGHT_BROWN 165, 42, 42, 255
# define LIGHT_GRAY 211, 211, 211, 255

int	get_rgba(int r, int g, int b, int a);

int	get_r(int rgba);

int	get_g(int rgba);

int	get_b(int rgba);

int	get_a(int rgba);

#endif
