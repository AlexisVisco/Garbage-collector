/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gc_alloc.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 13:27:33 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 13:48:58 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gc.h"

void	*gc_alloc(size_t size, char *file, int line)
{
	uintptr_t	ptr;
	t_gc_ptr	p;

	if (!(ptr = (uintptr_t)malloc(size)))
		return (NULL);
	p = (t_gc_ptr) {
		.start = ptr,
		.size = size,
		.marked = 3,
	# ifdef DEBUG
		.file = file,
		.line = line
	# endif
	};
	DEBUGP("Alloc %p with size %d in %s:%d\n", (void *)ptr, size, file, line);
	if (g_gc.min > ptr)
		g_gc.min = ptr;
	if (g_gc.max < ptr + size)
		g_gc.max = ptr + size;
	gc_list_push(&g_gc.pointer_map[HASH(ptr) % P_MAP_SIZE], p);
	g_gc.pointer_nb++;
	if (g_gc.pointer_nb >= g_gc.limit)
		gc_run();
	return ((void *)ptr);
}

void	gc_register(void *ptr, size_t size, char *file, int line)
{
	gc_list_push(&g_gc.globals, (t_gc_ptr) {
		.start = (uintptr_t)ptr,
		.size = size,
		.marked = true,
	# ifdef DEBUG
		.file = file,
		.line = line
	# endif
	});
}
