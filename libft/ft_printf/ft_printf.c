/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 01:02:14 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/07 15:46:11 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_state		state;
	va_list		args;
	int			result;
	t_printf	*tmp;

	state.str = format;
	state.head = NULL;
	state.start = 0;
	state.end = 0;
	parse_printf_string(&state);
	va_start(args, format);
	state.head->flags->fd = 1;
	process_format_nodes(state.head, &args);
	va_end(args);
	result = 0;
	while (state.head)
	{
		tmp = state.head->next;
		result += state.head->output_len;
		free(state.head->flags);
		free(state.head->input);
		free(state.head);
		state.head = tmp;
	}
	return (result);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_state		state;
	va_list		args;
	int			result;
	t_printf	*tmp;

	state.str = format;
	state.head = NULL;
	state.start = 0;
	state.end = 0;
	parse_printf_string(&state);
	va_start(args, format);
	state.head->flags->fd = fd;
	process_format_nodes(state.head, &args);
	va_end(args);
	result = 0;
	while (state.head)
	{
		tmp = state.head->next;
		result += state.head->output_len;
		free(state.head->flags);
		free(state.head->input);
		free(state.head);
		state.head = tmp;
	}
	return (result);
}
