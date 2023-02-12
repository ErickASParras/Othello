#include "othello_func.h"

/*****************************************FUNÇÕES PRINCIPAIS:**********************************************/

/**************************************************************
 * init_board - Esta função inicializa o tabuleiro, colocando
 * as peças brancas e pretas iniciais
 *
 * Argumentos:
 * board -- tabuleiro (matriz), ponteiro para ponteiro de char
 * Retorno:
 * sem valor, void
 * ***********************************************************/
void	init_board(char board[][8])
{
	int	line;
	int	col;

	printf("Othello Game\n\n");
	line = 0;
	while (line < 8)
	{
		col = 0;
		while (col < 8)
		{
			if (line == 3 && col == 3 || line == 4 && col == 4)
				board[line][col] = WHITE;
			else if (line == 3 && col == 4 || line == 4 && col == 3)
				board[line][col] = BLACK;
			else
				board[line][col] = POINT;
			col++;
		}
		line++;
	}
}

/***************************************************************
 * print_board - Esta função imprime o tabuleiro atual
 *
 * Argumentos:
 * board -- tabuleiro (matriz), ponteiro para ponteiro de char
 * Retorno:
 * sem valor, void
 * ************************************************************/
void    print_board(char board[][8])
{
	int	line;
	int	col;

	printf("\n  A B C D E F G H\n");
	line = 0;
	while (line < 8)
	{
		printf("%d ", line + 1);
		col = 0;
		while (col < 8)
		{
			printf("%c ", board[line][col]);
			col++;
		}
		printf("\n");
		line++;
	}
	printf("\n\n");
}

/*****************************************************************
 * play - Esta função coloca uma peça da cor color na posição
 * (line, col) e vira as peças do adversário, de acordo com as
 * regras do jogo
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * line - nº da linha em que se pretende colocar a peça, inteiro
 * col - nº da coluna em que se pretende colocar a peça, inteiro
 * player_color - cor do jogador, caractere
 * Retorno:
 * 1 - a jogada for finalizada ou o jogador perder a vez, inteiro
 * 0 - a jogada é invalida e/ou existe uma jogada disponível
 * **************************************************************/
int		play(char board[][8], int line, int col, char player_color)
{
	char	pc_color;

	pc_color = opponent_color(player_color);
	if (board[line - 1][col - 1] != POINT)
	{
		printf("Invalid move!\n\n");
		return (0);
	}
	else if (flanked(board, line, col, player_color) == INVALID)
	{
		if (!check_available_plays(board, NULL, NULL, player_color, 0))
		{
			printf("You have lost your turn!\n\n");
			return (1);
		}
		else
		{
			printf("Invalid move!\n\n");
			return (0);
		}
	}
	else
	{
		board[line - 1][col - 1] = player_color;
		check_directions_and_flip(board, line, col, player_color, pc_color);
		return (1);
	}
}

/****************************************************************
 * flanked - Esta função conta o número de peças viradas, ao
 * jogar numa certa linhas e coluna
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * line - nº da linha em que se pretende colocar a peça, inteiro
 * col - nº da coluna em que se pretende colocar a peça, inteiro
 * color - cor da peça a colocar
 * Retorno:
 * nº de peças viradas ao jogar numa certa linha e coluna
 * **************************************************************/
int		flanked(char board[][8], int line, int col, char color)
{
	int		flips;
	int		delta_line;
	int		delta_col;

	flips = 0;
	delta_line = -1;
	while (delta_line <= 1)
	{
		delta_col = -1;
		while (delta_col <= 1)
		{
			if (delta_line == 0 && delta_col == 0)
				delta_col++;
			flips += count_flips_dir(board, line, col, delta_line, delta_col, color);
			delta_col++;
		}
		delta_line++;
	}
	return (flips);
}

/****************************************************************
 * count_flips_dir - Esta função conta quantas peças são
 * viradas, numa certa linha e coluna, e numa certa numa
 * direção(delta_line e delta_col)
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * line - nº da linha em que se pretende colocar a peça, inteiro
 * col - nº da coluna em que se pretende colocar a peça, inteiro
 * delta_line - direção no eixo das ordenadas, inteiro
 * delta_col - direção no eixo das abcissas, inteiro
 * color - cor da peça a colocar, caractere
 * Retorno:
 * nº de peças viradas ao jogar numa certa linha e coluna
 * **************************************************************/
int		count_flips_dir(char board[][8], int line, int col, int delta_line, int delta_col, char color)
{
	int	flips;

	line += delta_line;
	col += delta_col;
	flips = 0;
	while (line >= 1 && line <= 8 && col >= 1 && col <= 8)
	{
		if (board[line - 1][col - 1] != color && board[line - 1][col - 1] != POINT)
			flips++;
		else if (board[line - 1][col - 1] == color)
			return (flips);
		else
			return (0);
		line += delta_line;
		col += delta_col;
	}
	return (0);
}
/***********************************************************************************************************/

/*****************************************FUNÇÕES SECUNDÁRIAS:**********************************************/

/************************************************************
 * game_over - Esta função verifica se ainda é possível algum
 * dos jogadores jogar(jogador e pc)
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * player_color - cor do jogador, caractere
 * Retorno:
 * 1 se não for possível jogar
 * 0 se for possível continuar a jogar
 * **********************************************************/
int		game_over(char board[][8], char player_color)
{
	int	line;
	int	col;
	int	pc_color;
	int	valid_plays;

	pc_color = opponent_color(player_color);
	valid_plays = 0;
	line = 0;
	while (line < 8)
	{
		col = 0;
		while (col < 8)
		{
			if (board[line][col] == '.'
			&& (flanked(board, line + 1, col + 1, player_color)
			|| flanked(board, line + 1, col + 1, pc_color)))
				valid_plays++;
			col++;
		}
		line++;
	}
	if (!valid_plays)
		return (1);
	return (0);
}

/************************************************************
 * check_winner - Esta função verifica qual dos jogadores
 * ganhou
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * player_color - cor do jogador, caractere
 * Retorno:
 * sem valor, void
 * **********************************************************/
void	check_winner(char board[][8], char player_color)
{
	int	line;
	int	col;
	int	black_pieces;
	int	white_pieces;

	black_pieces = 0;
	white_pieces = 0;
	line = 0;
	while (line < 8)
	{
		col = 0;
		while (col < 8)
		{
			if (board[line][col] == BLACK)
				black_pieces++;
			else if (board[line][col] == WHITE)
				white_pieces++;
			col++;
		}
		line++;
	}
	printf("Game Over!\nBlack: %d discs, White: %d discs\n", black_pieces, white_pieces);
	if (black_pieces == white_pieces)
		printf("It's a draw\n");
	else if (player_color == BLACK)
	{
		if (black_pieces > white_pieces)
			printf("You win!\n");
		else
			printf("You lose!\n");
	}
	else
	{
		if (white_pieces > black_pieces)
			printf("You win!\n");
		else
			printf("You lose!\n");
	}
}

/************************************************************
 * starting_color - Esta função selecciona, aleatoriamente, a
 * cor do jogador
 *
 * Argumentos:
 * sem valor, void
 * Retorno:
 * cor do jogador, caractere
 * **********************************************************/
char	starting_color(void)
{
	int	num;

	srand(time(NULL));
    num = rand() % 2;
    if (num == 1)
	{
        printf("Your discs are White.\n\n\n");
		return ('o');
	}
    else
	{
        printf("Your discs are Black.\n\n\n");
		return ('x');
	}
}

/************************************************************
 * input_is_valid - Esta função verifica se o input dado pelo
 * utilizador está de acordo com as regras
 *
 * Argumentos:
 * line - valor da linha a jogar, ponteiro para inteiro
 * col - valor da coluna a jogar, ponteiro para inteiro
 * Retorno:
 * 1 se o input for válido, inteiro
 * 0 se o input for inválido, inteiro
 * **********************************************************/
int		input_is_valid(int *line, int *col)
{
	char	column;

	printf("Choose your move. For instance: 5F\n");
	fflush(stdin);
	scanf("%d %c", &(*line), &column);
	*col = column + 1 - 'A';
	if (*line >= 0 && *line <= 8 && column >= 'A' && column <= 'H')
		return (1);
	else
	{
		printf("\n!!!INPUT IS NOT VALID!!!\n");
		printf("Insert your move as follows -> 5F\n(A number between 0 and 9 followed by a capital letter between A and H)\n\n");
		return (0);
	}
	printf("\n\n");
}

/************************************************************************
 * check_directions_and_flip - Esta função verifica todas as
 * direções numa certa posição e vira as peças contrárias,
 * caso seja possível
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * line - nº da linha em que se pretende colocar a peça, inteiro
 * col - nº da coluna em que se pretende colocar a peça, inteiro
 * color - cor do jogador(jogador ou pc) cuja peça foi jogada, caractere
 * opp_color - cor do oponente do jogador referido acima, caractere
 * Retorno:
 * sem valor, void
 * **********************************************************************/
void	check_directions_and_flip(char board[][8], int line, int col, char color, char opp_color)
{
	int	delta_line;
	int	delta_col;

	delta_line = -1;
	while (delta_line <= 1)
	{
		delta_col = -1;
		while (delta_col <= 1)
		{
			if (delta_line == 0 && delta_col == 0)
				delta_col++;
			if (count_flips_dir(board, line, col, delta_line, delta_col, color))
				flip_pieces(board, line, col, delta_line, delta_col, color, opp_color);
			delta_col++;
		}
		delta_line++;
	}
}

/*****************************************************************************
 * flip_pieces - Esta função verifica vira as peças numa dada direção,
 * de acordo com as regras do jogo
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * line - nº da linha em que se colocou a peça, inteiro
 * col - nº da coluna em que se colocou a peça, inteiro
 * delta_line - direção na qual vira as peças (componente vertical), inteiro
 * delta_col - direção na qual vira as peças (componente horizontal), inteiro
 * color - cor do jogador(jogador ou pc) cuja peça foi jogada, caractere
 * opp_color - cor do oponente do jogador referido acima, caractere
 * Retorno:
 * sem valor, void
 * ***************************************************************************/
void	flip_pieces(char board[][8], int line, int col, int delta_line, int delta_col, char color, char opp_color)
{
	line += delta_line;
	col += delta_col;
	while (board[line - 1][col - 1] == opp_color)
	{
		board[line - 1][col - 1] = color;
		line += delta_line;
		col += delta_col;
	}
}

/*********************************************************************
 * pc_play -  Esta função coloca uma peça da cor color na posição que
 * vira mais peças do adversário (neste caso o jogador), de acordo com
 * 	as regras do jogo
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * player_color - cor do jogador, caractere
 * Retorno:
 * sem valor, void
 * *******************************************************************/
void	pc_play(char board[][8], char player_color)
{
	int best_play[2];
	int	pc_color;

	pc_color = opponent_color(player_color);
	best_play[0] = -1;
	best_play[1] = -1;
	check_available_plays(board, &best_play[0], &best_play[1], pc_color, 1);
	if (best_play[0] != -1 && best_play[1] != -1)
	{
		board[best_play[0] - 1][best_play[1] - 1] = pc_color;
		check_directions_and_flip(board, best_play[0], best_play[1], pc_color, player_color);
		printf ("My move: %d%c\n\n", best_play[0], best_play[1] - 1 + 'A');
	}
}

/*********************************************************************
 * check_available_plays - Esta função verifica se existe alguma
 * jogada válida para ser efetuada pelo jogador e, caso a vez seja
 * do pc, a melhor jogada é registada e guardada em 2 variáveis
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * line -  linha a testar, ponteiro para inteiro
 * col - coluna a testar, ponteiro para inteiro
 * color - cor do jogador da peça a testar, caractere
 * pc - flag a indicar se é o turno do pc, inteiro
 * Retorno:
 * 1 se existirem jogadas válidas, inteiro
 * 0 se não existirem jogadas válidas, inteiro
 * *******************************************************************/
int		check_available_plays(char board[][8], int *line, int *col, char color, int pc)
{
	int	x;
	int	y;
	int	flips;

	flips = 0;
	x = 0;
	while (x < 8)
	{
		y = 0;
		while (y < 8)
		{
			if (board[x][y] == POINT && flips < flanked(board, x + 1, y + 1, color))
			{
				flips = flanked(board, x + 1, y + 1, color);
				if (pc)
				{
					*line = x + 1;
					*col = y + 1;
				}
			}
			y++;
		}
		x++;
	}
	return (flips);
}

/******************************************************************************
 * read_from_file - Esta função lê as jogadas de um ficheiro *.txt e executa-as
 *
 * Argumentos:
 * board - tabuleiro (matriz), ponteiro para ponteiro de char
 * file_name-  nome do ficheiro do qual se leêm as jogadas, ponteiro para char
 * my_turn - indica se a vez é do jogador ou do pc, ponteiro para inteiro
 * player_color - cor do jogador, caractere
 * Retorno:
 * sem valor, void
 * ****************************************************************************/
void	read_from_file(char board[][8], char *file_name, int *my_turn, char player_color)
{
	FILE	*f;
	char	play[2];
	int		count;
	int		c;
	char	color;

	if ((f = fopen(file_name, "r")) == NULL)
	{
		printf("Error reading from the file\n");
		return ;
	}
	color = BLACK;
	count = 0;
	while ((c = getc(f)) != EOF)
	{
		if (c == '\n')
			continue ;
		play[count++] = c;
		if (count == 2)
		{
			board[play[0] - '0' - 1][play[1] - 'A'] = color;
			check_directions_and_flip(board, play[0] - '0', play[1] - 'A' + 1, color, opponent_color(color));
			color = opponent_color(color);
			count = 0;
		}
		if (color == player_color)
			*my_turn = 1;
		else
			*my_turn = 0;
	}
	fclose(f);
}

/*********************************************************************
 * opponent_color - Esta função devolve a cor do oponente da cor
 * inserida como argumento
 *
 * Argumentos:
 * color - cor do jogador ou pc
 * Retorno:
 * caractere correspondente à cor da peça do oponente, caractere
 * *******************************************************************/
char	opponent_color(char color)
{
	if (color == WHITE)
		return (BLACK);
	else
		return (WHITE);
}

/***********************************************************************************************************/