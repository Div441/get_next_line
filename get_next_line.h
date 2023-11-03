
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstlast(t_list *list);
char	*extract_line(t_list *list);
void	copy_line(t_list *list, char *buff);
int		line_length(t_list *list);
void	remaining(t_list **list);
char	*get_next_line(int fd);
void	free_list(t_list **list, t_list *new, char *buff);
void	read_and_link(t_list **list, int fd);
int		newline(char *str);
void	add_back(t_list **list, char *buff);

#endif
