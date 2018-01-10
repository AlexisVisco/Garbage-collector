/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gc_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 13:12:10 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 13:28:39 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gc.h"

size_t	gc_ptr_index(uintptr_t ptr, t_gc_list **e)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (++i < P_MAP_SIZE)
	{
		*e = g_gc.pointer_map[i];
		while (*e)
		{
			if (ptr >= (*e)->data.start &&
			(*e)->data.start + (*e)->data.size >= ptr)
				return (j);
			*e = (*e)->next;
			j++;
		}
	}
	return (-1);
}

void	gc_mark_stack(uint8_t *mark_bits)
{
	gc_mark(mark_bits, g_gc.stack_start, (uint8_t *)STACK_PT);
}

void	swap_ptr(uint8_t *a, uint8_t *b)
{
	uint8_t *tmp;

	tmp = a;
	a = b;
	b = tmp;
}