/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:55:36 by legrandc          #+#    #+#             */
/*   Updated: 2023/12/09 20:04:40 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line_bonus.h"
# include <bsd/string.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define HEX_UP "0123456789ABCDEF"
# define HEX_LOW "0123456789abcdef"
# define DEC "0123456789"
# define FLAGS "-0# +"

typedef struct s_list
{
	void			*content;
	int				n;
	struct s_list	*next;
}					t_list;

/* FUNCTIONS */
void				exit_error(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strjoin3(char const *s1, char const *s2,
						char const *s3);
char				*get_next_line(int fd);
void				free_matrix(char **t);
unsigned int		ft_abs(int n);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
char				*ft_itoa_base(unsigned long n, char *base);
char				*ft_strtrim(char const *s1, char const *set);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content, int n);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *s);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isprint(int c);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isspace(int c);
int					ft_isdigit(int c);
void				*ft_memcpy(void *dest, const void *src, size_t n);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

// printf

typedef struct s_struct
{
	int				dash;
	int				zero;
	int				space;
	int				plus;
	int				star;
	size_t			width;
	int				dot;
	int				precision;
	va_list			ap;
	char			*string;
	int				len;
	int				percent;
	char			specifier;
	int				is_nul;
	int				is_pos;
	int				is_neg;
	int				hex_low;
	int				hex_up;
	int				is_str;
	int				hash;
}					t_struct;
/* FUNCTIONS */
int					pad(t_struct *vars);
int					handle_string(char *s, t_struct *vars);
int					handle_ptr(size_t ptr, t_struct *vars);
int					handle_int(int n, t_struct *vars);
int					handle_unsigned(unsigned int n, t_struct *vars, char *base);
int					ft_printf(const char *s, ...);
void				init(t_struct *vars);
void				setflag(char c, t_struct *vars);

# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_COLOR_RESET "\x1b[0m"

#endif
