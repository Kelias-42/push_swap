/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algautie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:11:16 by algautie          #+#    #+#             */
/*   Updated: 2019/09/25 12:14:49 by algautie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int		get_first_one(t_dlist **beg_a, int mask)
{
	t_dlist *tmp;

	tmp = *beg_a;
	while (tmp)
	{
		if (tmp->value & mask)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int		are_zeros_left(t_dlist **beg_a, int mask)
{
	t_dlist *tmp;

	tmp = *beg_a;
	while (tmp)
	{
		if (!(tmp->value & mask))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	back_to_first(t_dlist **beg_a, t_dlist **beg_ins, int first_one)
{
	t_dlist	*tmp;
	int		pos;

	tmp = *beg_a;
	pos = 0;
	while (tmp->value != first_one && ++pos)
		tmp = tmp->next;
	while ((*beg_a)->value != first_one)
	{
		if (pos * 2 > ft_lstlen(*beg_a))
			ps_reverse_rotate(beg_a, beg_ins, RR_A);
		else
			ps_rotate(beg_a, beg_ins, R_A);
	}
}

void	radix(t_dlist **beg_a, t_dlist **beg_b, t_dlist **beg_ins)
{
	int mask;
	int first_one;

	mask = 1;
	while (!is_sorted(*beg_a))
	{
		if ((first_one = get_first_one(beg_a, mask)) != 0)
		{
			while (are_zeros_left(beg_a, mask))
			{
				if (is_sorted(*beg_a) && ft_lstlen(*beg_b) == 0)
					break ;
				if (!((*beg_a)->value & mask))
					ps_push(beg_a, beg_b, beg_ins, P_B);
				if ((*beg_a)->value & mask && are_zeros_left(beg_a, mask))
					ps_rotate(beg_a, beg_ins, R_A);
			}
			if (!(is_sorted(*beg_a) && ft_lstlen(*beg_b) == 0))
				back_to_first(beg_a, beg_ins, first_one);
			push_all(beg_b, beg_a, beg_ins, P_A);
		}
		mask *= 2;
	}
}

int		main(int ac, char **av)
{
	int		i;
	t_dlist	*beg_a;
	t_dlist	*beg_b;
	t_dlist	*beg_ins;

	if (!check_args(ac, av) || ac < 2 \
			|| !(beg_a = ft_lst_create_elem(ft_atoi(av[1]))))
	{
		if (!(ac < 2))
			write(2, "Error\n", 6);
		return (0);
	}
	beg_b = NULL;
	beg_ins = NULL;
	i = 1;
	while (++i < ac)
		ft_lst_push_back(&beg_a, ft_atoi(av[i]));
	normalize(&beg_a);
	(ft_lstlen(beg_a) > 50) ? radix(&beg_a, &beg_b, &beg_ins)
		: pseudo_quick_sort(&beg_a, &beg_b, &beg_ins);
	optimize(beg_ins);
	print_ins(beg_ins);
	ft_lst_free(beg_a);
	ft_lst_free(beg_b);
	ft_lst_free(beg_ins);
}
