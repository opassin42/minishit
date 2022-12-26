/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:36 by opassin           #+#    #+#             */
/*   Updated: 2022/11/16 02:04:33 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*push_top(t_gc **head, size_t data_size)
{
	t_gc	*new_node;

	new_node = (t_gc*) malloc (sizeof(t_gc));
	if (!new_node)
	{
		gc_free();
		return (NULL);
	}
	new_node->addr =  (void*)malloc(data_size);
	if (!new_node->addr)
	{
		gc_free();
		free(new_node);
		return (NULL);
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node->addr);
	}

void	printList(t_gc *node)
{
	while (node != NULL)
	{
		printf("node : [ %p ]\n", node->addr);
		node = node->next;
	}
}

void	gc_free(void)
{
	t_gc	*current;

	current = start;
	while (current != NULL)
	{
		start = start->next;
		free(current->addr);
		current->next = NULL;
		free(current);
		current = start;
	}
}
