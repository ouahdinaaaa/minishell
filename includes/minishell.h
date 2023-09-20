/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:56:25 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/20 18:18:28 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_HISTORY_SIZE 100
# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <stdint.h>
# define BUFFER_SIZE 42
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define BLEU_E "\033[34m"
# define ROSE_C "\033[38;225m"
# define YELLOW "\033[33m"
# define BLANC "\033[107m"
# define MARRON "\033[38;10;94m"
# define SAPIN "\033[38;2;0;96;50m"
# define JAUNE "\033[38;5;208m"
# define RED "\033[31m"
# define EMERAUDE "\033[38;2;0;196;140m"
# define GRIS "\033[255;113;30m"
# define GREEN "\033[32m"
# define ROSE "\033[38;2;169;30;80m"
# define VERT "\033[38m"
# define ORANGE "\033[38;5;166m"
# define BLUE "\033[34m"
# define RESET "\033[1;97m"
# define VIOLET "\033[75;762;9m"
# define SURLIGNEUR "\033[38;2;0;102;112m"


typedef struct s_cmd
{
	char	*files[2];
	char	*arg;
	char	*cmd;
	int		prev_pipe;
	int		nbmots;
	int		nbcmd;
	int		*pids;
	int		i;
	int		ret;
	char	*res;
	int		file;
	int		fd[2];
	int		infile;
	int		outfile;
	int		here_doc;

}			t_cmd;

typedef struct s_info
{
	char *mots;      // mot recu sans aucune modif avec tout.
	char *new_mot;   // mots transformée avec simple ou double quote
	int simplequote; // le nombre de simple quote à réafficher
	int doublequote; // le nombre de double quotte à réafficher
	int		debut;
	// si on mets 2 alors on aura commencée avec simple quote si 1 on aura commencer avec double
}			t_info;

typedef struct s_pipex
{
	char *delimiteur; // mot delimiteur
	char *str_path;   // msg de echo/ export / Unset
	char	**start_fd;
	char *files[2];   // file[0] : in || files[1] : out
	char *path;       // pour stocker le path de cd
	char **env;       // stock environement
	char **fake_env;  // env export solo
	char *cmd;        // cmd avec ces argument ecrire avec seulement un espace
	char	**infiles;
	char	**outfiles;
	int		nbinfiles;
	int		nboutfiles;
	int export_cmd;   // if cmd == export
	int dollar;       // i on detecte $? ou $(variable)
	int size;         // size of cmd
	int pwd;          // si on détécte builtins pwd
	int in;           // si on détécte fichier in
	int cd;           // si on detecte builtins cd
	int out;          // si on detecte fichier out
	int exit;         // si on detecte exit
	int echo;         // si on detecte builtins echo
	int envi;         // si on detecte builtins env
	int unset;        // builtins unset
	int append;       // si on detete<< mettre 1
	int echo_n;       // si on détécte on option -n mettre 1 et 1 echo
	int here_doc;     // si on detecte here_doc
	int		index_char;
	int		indexmot;
	int		erreur;
	int		sq;
	int		dq;
	char	*commande;
	int	aya;
}			t_pipex;

extern int ctrl_c_signo;

/*-------------------------------LOOP/main-------------------------------------*/
void		loop(char **env);
int			ft_strcmp(const char *s1, const char *s2);
int			exit_case(char *commande);
void		print_env(char **env);
/*---------------------------------PARSE_SECOND-------------------------------*/
int			is_option(char option);
void		free_pipex(t_pipex *pipex);
int			exit_case(char *commande);
int			empty_case(char *commande);
int			is_chevron_inf(char chevron);
int			is_chevron_sup(char chevron);
/*--------------------------------------PARSE---------------------------------*/
void		free_all_sep(char **env);
char    *add_write_str(char *str1, char *str2, char *str3, char *str4);
/*-----------------------------------SIGNAL---------------------------------------*/
void		signal_ctrl_slash(int signo);
void		signal_ctrl_d(void);
void		signal_ctrl_c(int signo);
/*-------------------------------EXEC/REDIRECTION---------------------------------*/
void		exec_cmd(t_pipex *pipex, t_cmd data, char *pwd, int boolean);
void		is_child(t_cmd *data, const int index, t_pipex *pipex);
void		child_process(t_cmd data, t_pipex *pipex, int status, char *pwd);
void		write_file(t_cmd data, char *outfile, int append);
void		edit_env(char **str, t_pipex *pipex);
void		readfile(t_cmd data, char *infile);
void		dup_and_close(int fd, int re);
void		free_data(char **option);
void		free_dataa(t_cmd *data);
char		**split_cmd(char *av);
char		**export_fake_env(char **env);
char    	*ft_strcpy_mall(char *src);
char		*get_next_line(int fd, t_cmd *data, int boolean);
char		*add2write(char *dest, char *str3, char *str4, int j);
int			error_syntaxe(t_pipex *pipex);
void		initdata(t_cmd *data, int nbcm);
void		create_nino(char **env, char **option);
char		*right_directory(char *str);
int			end_function(t_cmd data, t_pipex *pipex);
void		print_pipex(t_pipex *pipex);
char		*new_str_special(char *src);
char    	**double_cut(char *str);
void		init_cmd(t_pipex *pipex, char *commande);
char		*replace_echo(t_pipex *pipex, int status, char *new);
void		end_function_cmd(char **new_str, t_pipex *pipex, char *str);
void		end_function_str_path(char **new_str, t_pipex *pipex, char *str);
void		end_function_path(char **new_str, t_pipex *pipex, char *str);
void		end_function_limiteur(char **new_str, t_pipex *pipex, char *str);
void		end_function_files_in(char **new_str, t_pipex *pipex, char *str);
void		end_function_files_out(char **new_str, t_pipex *pipex, char *str);

char    	*ft_replace_status(int status, char *str);
void		redirect_of_man(t_cmd *data, t_pipex *pipex);
void		create_here_doc(t_pipex *pipex, t_cmd *data,  int *tab, char *pwd);
void		create_every_files(t_pipex *pipex);
// void		create_here_doc(char *infile, char *limiter, t_cmd *data);
void		create_path(t_pipex *pipex, t_cmd data, char *pwd, char **option);
int			ft_strncmp_here(char *s1, char *s2, size_t n, int nb);
int			second_pipex(t_cmd data, t_pipex *pipex, int sta, char *pwd);
int			pipex_main(char **env, t_pipex *pipex, int status, char *pwd);
char		**ft_strcpy_double(char **env_copy);
int			valid_print(char *str);

/*-------------------------------REPLACE DOLLAR----------------------------------*/
void		sort_new_env(char ***env, int size, int index);
char		*replace_all(t_pipex *pipex, char *str, int status);
void		replace_str_cmd(t_pipex *pipex, int status);
void		replace_every_struct(t_pipex *pipex, int status);
void		replace_str_path(t_pipex *pipex, int status);
void		replace_path(t_pipex *pipex, int status);
void		replace_out(t_pipex *pipex, int status);
void		replace_files(t_pipex *pipex, int status);
void		replace(t_pipex pipex);
char		*ft_add_quote(char *str);
char		*add_dollar(char *str);
char		*ft_stradd(char *str, char *srt2);
int			detect_dollar(char *str);
int			search_len_place(char *str, t_pipex *pipex);
char		*search_and_replace(char *str, t_pipex *pipex);
int			detect_dollar(char *str);
char		*ft_strjoin_gnl(char *s1, char *s2);
/*-------------------------------BUILTINS----------------------------------------*/
void		add_path(char *add_path, t_pipex *builtins, int place);
void		delete_unset(char **env, char *path, t_pipex *pipex);
void		edit_env(char **str, t_pipex *pipex);
char		**restruct(char **str, int place);
int			cmd_exit(t_pipex *builtins, int i);
char		*get_directory(char *pwd);
int			size_of_env(char **env);
char		*replace_str(char *cmd);
void		init_fake_env(t_pipex *pipex, char **env);
char		*print_directory(char **new_str, char *pwd);
int			cmd_env(char **env);
int			cmd_pwd(void);
int			find_end_path(char *str);
char		*ft_itoa(int nb);
char		**add_export(char **env_cpy);
char		*replace_every(char *str, int status, t_pipex *pipex);
char		*replace_str_here(char *src, int status, t_pipex *pipex);
int			size_path(char *str);
void	signal_ctrl_c_here(int signo);
//void	signal_ctrl_c_here(t_pipex *pipex, t_cmd *data, int *tab, char *pwd);
int			cmd_cd(char *str_path, char **new_env);
char		**replace_export(char **env, int i);
char	*ft_strcpy_sp(char *dest, char *src);
void	ft_ctrl_here(char *limiteur);
void	free_files(char *s1, char *s2, char *s3);
char	*replace_status_doll(char **next, int status);
char	*delete_char(char *src);
char	*replace_no_env(char **next);
void	delete_here_doc(t_pipex *pipex);
char	*ft_strjoin_str2(char *s1, char *s2);
void		add_fake_env(char *str_path, t_pipex *pipex, int place);
int			cmd_echo(char *msg, int nb, int status, t_pipex *pipex);
void		print_verif(t_pipex *builtins);
int			choice_of_builtins(t_pipex *built, int i, int status);
int			cmd_unset(t_pipex *builtins, t_pipex *pipex);
int			cmd_export(t_pipex *builtins, t_pipex *pipex, int i);
void		edit_fake_env(char **str, t_pipex *pipex);
char		**write_of_str(char **str, int len_str, t_pipex builtins,
				int place);
int			find_env(char **env, char *str_path, int place);

///////////////////////////////////////////////////////////////
//////////////////////////// KAMEL ////////////////////////////
///////////////////////////////////////////////////////////////

// Builtins

void		checkBuiltins(t_pipex *pipex, int ip, char **motscmd);
void		checkUnset(t_pipex *pipex, int ip, char **cmd);
void		checkExport(t_pipex *pipex, int ip, char **cmd);
void		checkCd(t_pipex *pipex, int ip, char **cmd);
void		checkEcho(t_pipex *pipex, int ip, char **cmd);
void		checkPwd(t_pipex *pipex, int ip, char **cmd);
void		checkEnv(t_pipex *pipex, int ip);

// Initialisation & Free

t_pipex		*init_pipex(int parts, char **env);
//void		free_pipex(t_pipex *pipex);
void		free_pipex_infiles_outfiles_env(t_pipex *pipex, int i);
void		free_char_double(char **array);
void		case_command_null(char *pwd, char *commande, char **new_env);
// Parsing

void		parsing(char *commande, t_pipex *pi, char **env);

// Count

int			ft_count_files(char c, char *str);
int			ft_count_words(const char *str, char c);
int			ft_count_simple_quotes(const char *str);
int			ft_count_double_quotes(const char *str);
int			ft_count_parentheses(const char *str);
int			ft_count_pipes(char *s);
int			ft_countwords(char *str);
int			ft_count_dollars(char *str);

// Check

int			check_only_spaces(char *str);
void		check_exit(t_pipex *pipex, int ip, char **cmd);
int			check_is_even(int num);

// Display

void		display_pipex(t_pipex *pipex, int parts);

//

void		ft_write_env(t_pipex *pipex, char **env);
int			ft_strncp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		**ft_split(char const *s, char c);
char		*ft_strcpy(char *dest, const char *src);
char		*wordDup(const char *str, int start, int finish);
char		*word_dup(const char *str, int start, int finish);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*createHeredocFiles(int index);
char		*ft_strchr(const char *str, int character);
char		*ft_strncpy(char *dest, const char *src, size_t n);
void		bzero_pipex(int i, t_pipex *pipex);
int			*allocWords(char *str);
char		**words(char *str);
char		*convertirDollarEnEuro(char *str);
void		remplirTableauDeZeros(int *tableau, int taille);
int			isThereChar(char *str, char c);
char		*ft_strcat(char *dest, const char *src);
char		*strjoinExtremites(char *str, char c);
char		*putQuotes(char *str);
char		**quotes(char *str);
char		*collerMots(char **mots, int taille);
char		**splitPipes(char *s);
char		**decoupage(char *str);
int			isstartingwith(char *base, char *start);
int			conditionsquotesimpaires(char **p, int ip);
void		quotesimpaires(char **p, t_pipex *pipex, int ip);
char		*concatwithspace(char *str1, char *str2);

#endif

// ls | cat -e | pwd | export kamel=hello aya=coucou | wc -l | exit 12 12 | unset kamel | echo $USER | cat -e
