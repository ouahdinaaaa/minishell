/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:56:25 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/10 04:30:20 by ayael-ou         ###   ########.fr       */
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
	int		erreur;
	int		sq;
	int		dq;
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
void		exec_cmd(t_pipex *pipex, t_cmd data, char **env, int boolean);
void		is_child(t_cmd *data, const int index, t_pipex *pipex);
void		child_process(t_cmd data, char **env, t_pipex *pipex);
void		write_file(t_cmd data, char *outfile, int append);
void		edit_env(char **str, t_pipex *pipex);
void		readfile(t_cmd data, char *infile);
void		dup_and_close(int fd, int re);
void		free_data(char **option);
void		free_dataa(t_cmd *data);
char		**split_cmd(char *av);
char		**export_fake_env(char **env);
char		*get_next_line(int fd, t_cmd *data, int boolean);
int			error_syntaxe(t_pipex *pipex);
void		initdata(t_cmd *data, int nbcm);
void		create_nino(char **env, char **option);
int			end_function(t_cmd data, t_pipex *pipex);
void		print_pipex(t_pipex *pipex);
char    	**double_cut(char *str);
char    	*ft_replace_status(int status, char *str);
void		redirect_of_man(t_cmd *data, t_pipex *pipex);
void		create_here_doc(char *infile, char *limiter, t_pipex *pipex, int sta);
void		create_every_files(char **files);
// void		create_here_doc(char *infile, char *limiter, t_cmd *data);
void		create_path(t_pipex *pipex, t_cmd data, char **env, char **option);
int			ft_strncmp_here(char *s1, char *s2, size_t n, int nb);
int			second_pipex(t_cmd data, t_pipex *pipex, char **env, int sta);
int			pipex_main(char **env, t_pipex *pipex, int status);
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
char		*print_directory(void);
int			cmd_env(char **env);
int			cmd_pwd(void);
char		*ft_itoa(int nb);
char		*replace_every(char *str, int status, t_pipex *pipex);
char		*replace_str_here(char *src, int status, t_pipex *pipex);
int			size_path(char *str);
int			cmd_cd(char *str_path);
void		add_fake_env(char *str_path, t_pipex *pipex, int place);
int			cmd_echo(char *msg, int nb);
void		print_verif(t_pipex *builtins);
int			choice_of_builtins(t_pipex *built, int i);
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

void		checkUnset(t_pipex *pipex, int ip);
void		checkBuiltins(t_pipex *pipex, int ip);
void		checkExport(t_pipex *pipex, int ip);
void		checkCd(t_pipex *pipex, int ip);
void		checkEcho(t_pipex *pipex, int ip);
void		checkPwd(t_pipex *pipex, int ip);
void		checkEnv(t_pipex *pipex, int ip);
void		strcpyEchoN(t_pipex *pipex, int ip);
char		*strcpyOption(t_pipex *pipex, int index_pipe);
char		*strcpyCd(t_pipex *pipex, int index_pipe);
char		*strcpyUnset(t_pipex *pipex, int index_pipe);
char		*strcpyExport(t_pipex *pipex, int index_pipe);
char		*strcpyEcho(t_pipex *pipex, int index_pipe);
char		*strcpySpecial(char *src, char deli, t_pipex *pipex, int *tab);
char		*strcpySpecialSq(char *src, t_pipex *pipex, int *tab);
char		*strcpySpecialDq(char *src, t_pipex *pipex, int *tab);

// Initialisation & Free

t_pipex		*init_pipex(int parts, char **env);
void		free_pipex(t_pipex *pipex);
void		free_tab_pipex(t_pipex *pipex, int parts);
void		free_char_double(char **array);
void		free_double(char **tab);

// Parsing

void		heredocDq(char **p, t_pipex *pi, int ip);
void		heredocSq(char **p, t_pipex *pi, int ip);
void		heredocFile(char **p, t_pipex *pi, int ip);
void		infileHeredoc(char **p, t_pipex *pi, int ip);
void		parsing(char *commande, t_pipex *pi, char **env);
void		infileSpaceFile(char **p, t_pipex *pi, int ip);
void		infileSpaceDq(char **p, t_pipex *pi, int ip);
void		infileSpaceSq(char **p, t_pipex *pi, int ip);
void		infileFile(char **p, t_pipex *pi, int ip);
void		infile(char **p, t_pipex *pi, int ip);
void		outfileAppend(char **p, t_pipex *pi, int ip);
void		outfileSpaceFile(char **p, t_pipex *pi, int ip);
void		outfileSpaceDq(char **p, t_pipex *pi, int ip);
void		outfileSpaceSq(char **p, t_pipex *pi, int ip);
void		outfileFile(char **p, t_pipex *pi, int ip);
void		outfile(char **p, t_pipex *pi, int ip);
void		stockage_commande(char **p, t_pipex *pi, int ip);

// Utils

// Count
int			countPipes(char *commande);
int			count_words(const char *str, char c);
int			countWordsCd(char *commande);
int			countSingleQuotes(const char *str);
int			countDoubleQuotes(const char *str);
int			countParentheses(const char *str);
// Contains
int			containsdollarsign(const char *str);
int			onlySpaces(char *str);
// Check
int			checkInfile(char *commande, int debut);
int			checkOutfile(char *commande, int debut, t_pipex *pipex, int ip);
int			checkFileAppend(char *commande, int debut, t_pipex *pipex, int ip);
int			checkFileHeredoc(char *commande, int debut);
void		checkExit(t_pipex *pipex, int ip);
// Display
void		displayPipex(t_pipex *pipex, int parts);
void		displayPipexEssential(t_pipex *pipex, int parts);
//
void		write_env(t_pipex *pipex, char **env);
void		spaceManagement(t_pipex *pipex, int ip);
void		cmdopt(t_pipex *pipex, int ip, char *str, char **p);
int			nombremots(char *str);
int			isEven(int num);
int			ft_strncp(const char *s1, const char *s2);
int			strncpSpecial(const char *s1, const char *s2, size_t n);
int			skipFirstSpaces(char *commande);
size_t		ft_strlen(const char *s);
char		**ft_split(char const *s, char c);
char		**write_mots(char *str, int nb);
char		*append_char(char *str, char c);
char		*ft_strcpy(char *dest, const char *src);
char		*wordDup(const char *str, int start, int finish);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*createHeredocFiles(int index);
char		*ft_strchr(const char *str, int character);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*extractsubstring(char *str);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*clear_cmd(char *str);
void		bzero_pipex(int i, t_pipex *pipex);
char		*simpleFTdouble(char *str);
char		*word_dup(const char *str, int start, int finish);
// Les last

int			countWords(char *str);
int			*allocWords(char *str);
char		**words(char *str);
int			countDollars(char *str);
char		*convertirDollarEnEuro(char *str);
void		remplirTableauDeZeros(int *tableau, int taille);
int			isThereChar(char *str, char c);
char		*ft_strcat(char *dest, const char *src);
char		*strjoinExtremites(char *str, char c);
char		*putQuotes(char *str);
char		**quotes(char *str);
char		*collerMots(char **mots, int taille);

int			countPipes(char *s);
char		**splitPipes(char *s);

#endif
