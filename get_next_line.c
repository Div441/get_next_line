
#include "get_next_line.h"

void	free_list(t_list **list, t_list *new, char *buff)
{
	t_list	*tmp;

	while (*list != NULL)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (!new)
	{
		free(new);
		return ;
	}
	if (new->content[0] != '\0')
		*list = new;
	else
	{
		free(buff);
		free(new);
	}
}

void	remaining(t_list **list)
{
	t_list	*last;
	t_list	*new;
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buff = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_list));
	if (!buff || !new)
		return ;
	last = ft_lstlast(*list);
	while (last->content[i] != '\0' && last->content[i] != '\n')
		i++;
	while (last->content[i] != '\0')
		buff[j++] = last->content[++i];
	buff[j] = '\0';
	new->content = buff;
	new->next = NULL;
	free_list(list, new, buff);
}

char	*extract_line(t_list *list)
{
	char	*str;

	if (!list)
		return (NULL);
	str = malloc((line_length(list)) + 1);
	if (!str)
		return (NULL);
	copy_line(list, str);
	return (str);
}

void	read_and_link(t_list **list, int fd)
{
	int		bytes;	
	char	*buff;
	t_list	*last;

	if (*list != NULL && (newline((*list)->content) == 1))
		return ;
	while (1)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(buff);
			if (bytes < 0)
				free_list(list, NULL, buff);
			return ;
		}
		buff[bytes] = '\0';
		add_back(list, buff);
		last = ft_lstlast(*list);
		if (newline(last->content) == 1)
			return ;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_link(&list, fd);
	if (!list)
		return (NULL);
	line = extract_line(list);
	remaining(&list);
	return (line);
}
