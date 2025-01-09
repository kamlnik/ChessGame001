#include <My_lib/Rook.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
Textures::ID RookTextureID(unsigned t)
{
	if (t == 0) { // 0 это чёрное 
		return Textures::bRook;
	}
	else {
		return Textures::wRook;
	}
}

Rook::Rook(Color ncolor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]) :Figure(Type::Rook, ncolor), rook_all_move(), chess_board(new_chess_board), mSprite(textures.get(RookTextureID(ncolor))), first_move(1) {}

void Rook::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// вывод king
}
Rook::Rook(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]) :Figure(Figure::Rook, nColor), chess_board(new_chess_board), mSprite(), rook_all_move(), first_move(1) {
	this->setPosition(Position);
}

unsigned mindex_correct_position_for_rook(float position, float Screen_size) {
	float returned_val = 0.f;
	int per = position / (Screen_size / 16);
	if (per % 2 == 0) {
		returned_val = (per) / 2;
		return returned_val;
	}
	returned_val = (per - 1) / 2;
	return returned_val;
}

void vertical_up_move_for_rook(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& rook_all_move, float Screen_size) {
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
				rook_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t][x] == 1 || chess_board[t][x] == 3)) {
				chess_board[t][x] = 3;
				rook_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		rook_all_move.push_back(sf::Vector2f(xc, yc));
		if (t == 0) {
			return;
		}
		t--;
	}
}

void vertical_dawn_move_for_rook(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& rook_all_move, float Screen_size) {
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
				rook_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t][x] == 1 || chess_board[t][x] == 3)) {
				chess_board[t][x] = 3;
				rook_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		rook_all_move.push_back(sf::Vector2f(xc, yc));
		if (t == 7) {
			return;
		}
		t++;
	}
}

void horizontal_left_move_for_rook(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& rook_all_move, float Screen_size) {
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
				rook_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[y][t] == 1 || chess_board[y][t] == 3)) {
				chess_board[y][t] = 3;
				rook_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		rook_all_move.push_back(sf::Vector2f(xc, yc));
		if (t == 0) {
			return;
		}
		t--;
	}
}

void horizontal_right_move_for_rook(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& rook_all_move, float Screen_size) {
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
				rook_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[y][t] == 1 || chess_board[y][t] == 3)) {
				chess_board[y][t] = 3;
				rook_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		rook_all_move.push_back(sf::Vector2f(xc, yc));
		if (t == 7) {
			return;
		}
		t++;
	}
}

void Rook::update_move(float Screensize) {
	unsigned x = mindex_correct_position_for_rook(this->getPosition().x, Screensize);
	unsigned y = mindex_correct_position_for_rook(this->getPosition().y, Screensize);
	unsigned fcolor = this->getColor();
	float xl = (Screensize / 8);
	rook_all_move.clear();
	vertical_up_move_for_rook(chess_board, x, y, fcolor, rook_all_move, Screensize);
	vertical_dawn_move_for_rook(chess_board, x, y, fcolor, rook_all_move, Screensize);
	horizontal_left_move_for_rook(chess_board, x, y, fcolor, rook_all_move, Screensize);
	horizontal_right_move_for_rook(chess_board, x, y, fcolor, rook_all_move, Screensize);
}