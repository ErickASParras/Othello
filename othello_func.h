#ifndef OTHELLO_FUNC_H
# define OTHELLO_FUNC_H

# define WHITE 'o'
# define BLACK 'x'
# define POINT '.'
# define INVALID 0

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void	init_board(char board[][8]);

void	print_board(char board[][8]);

int		play(char board[][8], int line, int col, char player_color);

int		flanked(char board[][8], int line, int col, char color);

int		count_flips_dir(char board[][8], int line, int col, int delta_line, int delta_col, char color);

int		game_over(char board[][8], char player_color);

void	check_winner(char board[][8], char player_color);

char	starting_color(void);

int		input_is_valid(int *line, int *col);

void	check_directions_and_flip(char board[][8], int line, int col, char color, char opp_color);

void	flip_pieces(char board[][8], int line, int col, int delta_line, int delta_col, char color, char opp_color);

void	pc_play(char board[][8], char player_color);

int		check_available_plays(char board[][8], int *line, int *col, char color, int pc);

void	read_from_file(char board[][8], char *file_name, int *my_turn, char player_color);

char	opponent_color(char color);

#endif