#include "othello_func.h"

int main(int argc, char **argv)
{
	char	board[8][8];
	char	player_color;
	int		line;
	int		col;
	int		my_turn;

	my_turn = 0;
	if ((player_color = starting_color()) == BLACK)
		my_turn = 1;
	init_board(board);
	if (argc == 2)
		read_from_file(board, argv[1], &my_turn, player_color);
    print_board(board);
	while (!game_over(board, player_color))
	{
		if (my_turn)
		{
			if (input_is_valid(&line, &col))
			{
				if(play(board, line, col, player_color))
					my_turn = 0;
			}
		}
		else
		{
			pc_play(board, player_color);
			my_turn = 1;
		}
		print_board(board);
	}
	check_winner(board, player_color);
	return (0);
}