/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbhatia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:00:08 by dbhatia           #+#    #+#             */
/*   Updated: 2023/11/03 13:01:28 by dbhatia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_back(t_list **list, char *buff)
{
	t_list	*new;
	t_list	*last;

	last = ft_lstlast(*list);
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	if (!last)
		*list = new;
	else
		last->next = new;
	new->content = buff;
	new->next = NULL;
}

int	newline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	line_length(t_list *list)
{
	int	i;
	int	j;

	j = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
			{
				i++;
				return (j + 1);
			}
			i++;
			j++;
		}
		list = list->next;
	}
	return (j);
}

t_list	*ft_lstlast(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	copy_line(t_list *list, char *buff)
{
	int	i;
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				buff[j++] = '\n';
				buff[j] = '\0';
				return ;
			}
			buff[j++] = list->content[i++];
		}
		list = list->next;
	}
	buff[j] = '\0';
}
