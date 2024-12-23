#include <My_lib/Queen.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
Textures::ID QueenTextureID(unsigned t)
{
	if (t == 0) { // 0 это чёрное 
		return Textures::bQueen;
	}
	else {
		return Textures::wQueen;
	}
}
Queen::Queen(Color ncolor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]) :Figure(Type::Queen, ncolor), queen_all_move(), chess_board(new_chess_board), mSprite(textures.get(QueenTextureID(ncolor))) {}

void Queen::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// вывод king
}
unsigned mindex_correct_position_for_queen(float position, float Screen_size) {
	float returned_val = 0.f;
	int per = position / (Screen_size / 16);
	if (per % 2 == 0) {
		returned_val = (per) / 2;
		return returned_val;
	}
	returned_val = (per - 1) / 2;
	return returned_val;

}
void vertical_up_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& queen_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (y == 0) {
		return;
	}
	unsigned t = y - 1;
	while (t >= 0) {
		float xc = x * l + l / 2;
		float yc = (t)*l + l / 2;
		if (chess_board[t][x] != 0) {
			if (fcolor == 0 && (chess_board[t][x] == 2 || chess_board[t][x] == 4)) {
				chess_board[t][x] = 4;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if(fcolor == 1 && (chess_board[t][x] == 1 || chess_board[t][x] == 3)) {
				chess_board[t][x] = 3;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		queen_all_move.push_back(sf::Vector2f(xc, yc));
		if (t == 0) {
			return;
		}
		t--;
	}
}
void vertical_dawn_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& queen_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (y == 7) {
		return;
	}
	unsigned t = y + 1;
	while (t < 8) {
		float xc = x * l + l / 2;
		float yc = (t)*l + l / 2;
		if (chess_board[t][x] != 0) {
			if (fcolor == 0 && (chess_board[t][x] == 2 || chess_board[t][x] == 4)) {
				chess_board[t][x] = 4;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t][x] == 1 || chess_board[t][x] == 3)) {
				chess_board[t][x] = 3;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		queen_all_move.push_back(sf::Vector2f(xc, yc));
		if (t == 7) {
			return;
		}
		t++;
	}
}

void diagonal_right_up_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& queen_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (y == 0 || x == 7) {
		return;
	}
	unsigned t1 = y - 1 ;
	unsigned t2 = x + 1;
	while (t1 >= 0 && t2 < 8) {
		float xc = t2 * l + l / 2;
		float yc = (t1)*l + l / 2;
		if (chess_board[t1][t2] != 0) {
			if (fcolor == 0 && (chess_board[t1][t2] == 2 || chess_board[t1][t2] == 4)) {
				chess_board[t1][t2] = 4;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t1][t2] == 1 || chess_board[t1][t2] == 3)) {
				chess_board[t1][t2] = 3;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		queen_all_move.push_back(sf::Vector2f(xc, yc));
		if (t1 == 0 || t2 == 7) {
			return;
		}
		t1--;
		t2++;
	}
}
void diagonal_left_dawn_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& queen_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (y == 7 || x == 0) {
		return;
	}
	unsigned t1 = y + 1;
	unsigned t2 = x - 1;
	while (t1 < 8 && t2 >= 0) {
		float xc = t2 * l + l / 2;
		float yc = (t1)*l + l / 2;
		if (chess_board[t1][t2] != 0) {
			if (fcolor == 0 && (chess_board[t1][t2] == 2 || chess_board[t1][t2] == 4)) {
				chess_board[t1][t2] = 4;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t1][t2] == 1 || chess_board[t1][t2] == 3)) {
				chess_board[t1][t2] = 3;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		queen_all_move.push_back(sf::Vector2f(xc, yc));
		if (t1 == 7 || t2 == 0) {
			return;
		}
		t1++;
		t2--;
	}
}
void diagonal_right_dawn_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& queen_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (x == 7 || y == 7) {
		return;
	}
	unsigned t1 = y + 1;
	unsigned t2 = x + 1;
	while (t1 < 8 && t2 < 8) {
		float xc = t2 * l + l / 2;
		float yc = (t1)*l + l / 2;
		if (chess_board[t1][t2] != 0) {
			if (fcolor == 0 && (chess_board[t1][t2] == 2 || chess_board[t1][t2] == 4)) {
					chess_board[t1][t2] = 4;
					queen_all_move.push_back(sf::Vector2f(xc, yc));	
			}
			else if (fcolor == 1 && (chess_board[t1][t2] == 1 || chess_board[t1][t2] == 3)) {
				chess_board[t1][t2] = 3;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		queen_all_move.push_back(sf::Vector2f(xc, yc));
		if (t1 == 7 || t2 == 7) {
			return;
		}
		t1++;
		t2++;
	}
}
void diagonal_left_up_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& queen_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (x == 0 || y == 0) {
		return;
	}
	unsigned t1 = y - 1;
	unsigned t2 = x - 1;
	while (t1 >= 0 && t2 >= 0) {
		float xc = t2 * l + l / 2;
		float yc = (t1)*l + l / 2;
		if (chess_board[t1][t2] != 0) {
			if (fcolor == 0 && (chess_board[t1][t2] == 2 || chess_board[t1][t2] == 4)) {
				chess_board[t1][t2] = 4;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t1][t2] == 1 || chess_board[t1][t2] == 3)) {
				chess_board[t1][t2] = 3;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		queen_all_move.push_back(sf::Vector2f(xc, yc));
		if (t1 == 0 || t2 == 0) {
			return;
		}
		t1--;
		t2--;
	}
}
void horizontal_left_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& queen_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (x == 0) {
		return;
	}
	unsigned t = x - 1;
	while (t >= 0) {
		float xc = t * l + l / 2;
		float yc = (y)*l + l / 2;
		if (chess_board[y][t] != 0) {
			if (fcolor == 0 && (chess_board[y][t] == 2 || chess_board[y][t] == 4)) {
				chess_board[y][t] = 4;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[y][t] == 1 || chess_board[y][t] == 3)) {
				chess_board[y][t] = 3;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		queen_all_move.push_back(sf::Vector2f(xc, yc));
		if (t == 0) {
			return;
		}
		t--;
	}
}
void horizontal_right_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& queen_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (x == 7) {
		return;
	}
	unsigned t = x + 1;
	while (t < 8) {
		float xc = t * l + l / 2;
		float yc = (y)*l + l / 2;
		if (chess_board[y][t] != 0) {
			if (fcolor == 0 && (chess_board[y][t] == 2 || chess_board[y][t] == 4)) {
				chess_board[y][t] = 4;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[y][t] == 1 || chess_board[y][t] == 3)) {
				chess_board[y][t] = 3;
				queen_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		queen_all_move.push_back(sf::Vector2f(xc, yc));
		if (t == 7) {
			return;
		}
		t++;
	}
}


void Queen::update_move(float Screensize) {
	unsigned x = mindex_correct_position_for_queen(this->getPosition().x, Screensize);
	unsigned y = mindex_correct_position_for_queen(this->getPosition().y, Screensize);
	unsigned fcolor = this->getColor();
	float xl = (Screensize / 8);
	queen_all_move.clear();
	vertical_up_move(chess_board, x, y, fcolor, queen_all_move, Screensize);
	vertical_dawn_move(chess_board, x, y, fcolor, queen_all_move, Screensize);
	horizontal_left_move(chess_board, x, y, fcolor, queen_all_move, Screensize);
	horizontal_right_move(chess_board, x, y, fcolor, queen_all_move, Screensize);
	diagonal_left_dawn_move(chess_board, x, y, fcolor, queen_all_move, Screensize);
	diagonal_left_up_move(chess_board, x, y, fcolor, queen_all_move, Screensize);
	diagonal_right_dawn_move(chess_board, x, y, fcolor, queen_all_move, Screensize);
	diagonal_right_up_move(chess_board, x, y, fcolor, queen_all_move, Screensize);
}