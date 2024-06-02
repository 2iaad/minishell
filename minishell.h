/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:45:46 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/02 22:25:24 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>


typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char	*token;
	int		type;
	int		index;
	struct s_token	*next;
}				t_token;

typedef struct s_list
{
	char	**cmd;
	t_env	*env;
}	t_list;

typedef enum s_meta
{
	WORD,
	CMD,
	OPTION,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	IN_FILE,
	OUT_FILE,
	AOUT_FILE,
	DELIMITER
} t_meta;

typedef struct s_final
{
	char	*cmd;
	char	**args;
	char	**in_file;
	char	**out_file;
	char	**aout_file;
	char	**heredoc;
	char	**exec_cmd;
	t_env	*env;
} 	t_final;


//*----------------------------------TOOLS------------------------------------------*//
//*---Parsing---*
char	**split_line(char *line);
int		ft_strlen(char *s);
int		whitespaces(char s);
void	ft_putstr_fd(char *s, int fd);
int		ft_isalnum(int c);
int		ft_isnum(int n);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsiz);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin_parse(char *s1, char *s2);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
//*//*---Execution---*
int		ft_isalpha(int c);
int		valid_check(char *str);
void    ft_free(char **str);
int     flag_check(char *s1);
long	ft_atol(char *str);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *s, char c);
int		ft_strncmp(char *s1, char *s2, int len);
char	**custumized_ft_split(const char *str, char c);
char	*ft_strnstr(const char *haystack, const char *needle, int len);

//*----------------------------------linked_list------------------------------------------*//
//*---Parsing---*
t_token	*ft_lstnew_parse(char *content, int type);
t_token	*ft_lstlast_parse(t_token *lst);
t_env	*ft_lstlast2_parse(t_env *lst);
void	ft_lstadd_back_parse(t_token **lst, t_token *new);
void	ft_lstadd_back_2_parse(t_env **lst, t_env *new);
//*---Execution---*
t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstclear(t_env **lst);
void	ft_lstadd_back(t_env **lst, t_env *newn);

//*----------------------------------PARSING--------------------------------------------------------------*//

void	read_from_input(t_final *final_cmd);
void	parce_line(char *line, t_env **env);
char	*parse_protec(char *line);

//*----------------------CHECK_QOUTES-----------------------------*//

int		check_quotes(char *line);
int		valid_meta(char *line, int i, int j, int valid);
int		valid_meta2(char *line, int i, int j, int valid);

//*----------------------REMOVE_QOUTES---------------------------*//

void	token_quotes(t_token **token);
char	*remove_quotes(char *line);
void	token_quotes(t_token **token);

//*----------------------ADD_SPACE--------------------------*//

int		space_len(char *line, int i);
char	*space(char *line, int i, int j);
void	spaces_sing_quot(char *new_line, char *line, int *j, int i);
void	spaces_doubl_quot(char *new_line, char *line, int *j, int i);
char	*trim_line(char *line);

//*----------------------EXPANDING---------------------------*//

int		delimiters(char c);
t_env	*get_env(char **envp);
char	*expand_env(char *line, t_env **env);

//*----------------------SYNTAX_ERROR---------------------------*//

int		is_operator(char *line, int *i);
void	skip_spaces(char *line, int *i, int inc);
int		syntax_error(char *line);

//*----------------------TOKENIZER---------------------------*//

void	tokenizer(char **splited, t_token **token);
t_token	*ft_get_token(char *content, int type);
int		is_oper(char *tok, int asc, int len);

//*----------------------STRUCT---------------------------*//

t_final	*struct_init(t_token **token);
t_final	*init_final(t_token **nodee);
int		count_len(t_token *node, int type);

// *------------------------------------------------------------------------------------------------------------------------------------------*//

// *--------------------------------------EXECUTION----------------------------------------------------* //

//*---------------------BUILTINS--------------------------*//

void    echo(t_list	*lst);
void    cd(t_list *lst);
void    pwd(void);
void    env(t_list *cmd);
void	unset(t_list	*lst);
void	export_command(t_list *lst);
void	exit_command(char **cmd);

//*---------------------EXECUTION--------------------------*//

void	ft_free(char **tab);
void	error(char *str, int a);
char	*look_for_paths(char **env);
void	pipex(char *cmd, char **env);
void	first_child(char **av, char **ev);
void	heredoc_limiter(char **av, int ac);
char	*right_path(char *cmd, char **env);
void	execute_cmd(char *cmd, char **env);
void	heredoc_file_opener(int ac, char **av);
int		normal_file_opener(int a, char *file);
void	init_env(t_final *lst, char **env);



#endif