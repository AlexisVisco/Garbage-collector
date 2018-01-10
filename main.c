/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 13:33:17 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 13:46:29 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gc.h"

void	lol(void **h)
{
	void **hello;
	void *hi;

	hello = gc_alloc(10);
	*hello = gc_alloc(11);
	*hello += 3;
	*h = *hello;
}

int		main(int argc, char *argv[])
{
	void *h;

	gc_init(&argc, 1);
	lol(&h);
	printf("pointer: %p\n", h);
	gc_alloc(1);
	gc_run();
}
