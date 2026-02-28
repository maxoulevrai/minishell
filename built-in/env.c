/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:20:49 by maleca            #+#    #+#             */
/*   Updated: 2026/02/28 15:22:45 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bultins.h"

   Exit status:
       125    if the env command itself fails

       126    if COMMAND is found but cannot be invoked

       127    if COMMAND cannot be found

       -      the exit status of COMMAND otherwise