/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:25:08 by fnieves-          #+#    #+#             */
/*   Updated: 2023/03/19 22:20:17 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

#include "../Screen.h"

/* Error messages */
#define ERR_MS "Error\n"
#define ERRNBINP_MES	"Wrong number of inputs\n"
#define ERR_TEXT_INP_MES	"more than 2 arguments in texture line\n"
#define ERR_COLOR_INP_MES	"more than 2 arguments in colour line\n"
#define ERR_COLOR_INP2_MES	"more than 3 values for RGB definition \n"
#define ERR_COLOR_INP3_MES	"RGB values not integers or not in range [0-255] \n"
#define ERR_TEXT_PATH_MES	"impossible to open the path to texture\n"
#define ERR_INP_MAP_MES		"repetdio punto cardinal o falta o el mapa no tiene simbolos correctos\n"

#define USAGE	"Please provide correct format \
<./cube3d> <file>'\n"

#define ERR_MAP_INPT_MES	"The input map , has a problem \
as above message indicates'\n"

/* Error codes return values */

enum	code_error //podemos usarlo?
{
	ERRNBINP = 10,
	ERR_MAP_INPT,
	ERR_TEXT_INP,
	ERR_INP_MAP,
	ERR_TEXT_PATH,
	ERR_COLOR_INP,
	ERR_COLOR_INP2,
	ERR_COLOR_INP3,
	DRAFT,

};


int	print_error(char *error_msg, int return_val);


#endif