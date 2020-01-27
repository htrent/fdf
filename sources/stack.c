/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 20:59:12 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_stack		*new_node(int z, int color)
{
	t_stack	*node;

	if (!(node = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	node->z = z;
	node->color = color;
	node->next = NULL;
	return (node);
}

void		push(t_stack **stack, t_stack *node)
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

t_stack		*pop(t_stack **stack)
{
	t_stack *pop;

	pop = NULL;
	if (stack && *stack)
	{
		pop = *stack;
		*stack = (*stack)->next;
	}
	return (pop);
}

void		free_stack(t_stack *stack)
{
	t_stack *to_del;

	while (stack)
	{
		to_del = stack;
		stack = stack->next;
		free(to_del);
	}
}

void		print_stack(t_stack *stack)
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
