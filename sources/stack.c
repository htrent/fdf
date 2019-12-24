/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/24 14:33:30 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_stack		*new_node(int z, int color)
{
	t_stack 	*node;
	if (!(node = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	node->z = z;
	node->color = color;
	node->next = NULL;
	return (node);
}

void	push(t_stack **stack, t_stack *node)
{
	if (!stack)
		return ;
	if (!*stack)
		*stack = node;
	else
	{
		node->next = *stack;
		*stack = node;
	}
}

void	free_stack(t_stack *stack)
{
	t_stack *to_del;

	while(stack)
	{
		to_del = stack;
		stack = stack->next;
		free(to_del);
	}
}

void	print_stack(t_stack *stack)
{
	if (!stack)
		return ;
	while (stack)
	{
		ft_putstr("z: ");
		ft_putnbr(stack->z);
		ft_putchar(' ');
		ft_putnbr(stack->color);
		ft_putchar('\n');
		stack = stack->next;
	}
}