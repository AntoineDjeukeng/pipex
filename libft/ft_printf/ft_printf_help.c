/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 01:02:14 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/07 15:49:07 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnchr(char c, int n)
{
	int	j;

	j = 0;
	while (j++ < n)
		write(1, &c, 1);
	return (n);
}

int	ft_dputnchr(int fd,char c, int n)
{
	int	j;

	j = 0;
	while (j++ < n)
		write(fd, &c, 1);
	return (n);
}

void	process_format_node(t_printf *node, va_list *args)
{
	if (!node->flags)
		node->flags = ft_find_flags_id((const char *)node->input);
	if (node->flags->specifier == 'd' || node->flags->specifier == 'i')
		node->output_len = ft_print_int(node->flags, args);
	else if (node->flags->specifier == 'u')
		node->output_len = ft_print_uint(node->flags, args);
	else if (node->flags->specifier == 'x' || node->flags->specifier == 'X')
		node->output_len = ft_print_hex(node->flags, args);
	else if (node->flags->specifier == 'p')
		node->output_len = ft_print_ptr(node->flags, args);
	else if (node->flags->specifier == 's' || node->flags->specifier == 'c')
		node->output_len = ft_format_str_or_char(node->flags, args);
	else if (node->flags->specifier == '%')
		node->output_len = ft_flag_percent(node->flags);
	else
		node->output_len += write(node->flags->fd, node->output, ft_strlen(node->input));
}

void	process_format_nodes(t_printf *head, va_list *args)
{
	while (head)
	{
		if (head->type && head->include)
			process_format_node(head, args);
		else
			head->output_len = write(head->flags->fd, head->input, ft_strlen(head->input));
		head = head->next;
	}
}
