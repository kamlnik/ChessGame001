#include <My_lib/Pawn.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>

Textures::ID PawnTextureID(unsigned t)
{
	if (t == 0) { // 0 это чёрное 
		return Textures::bPawn;
	}
	else {
		return Textures::wPawn;
	}
}

Pawn::Pawn(Color ncolor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]) : Figure(Type::Pawn, ncolor), pawn_all_move(), chess_board(new_chess_board), mSprite(textures.get(PawnTextureID(ncolor))) { }

Pawn::Pawn(Color nColor, const sf::Vector2f Position, unsigned(&new_chess_board)[8][8]): Figure(Figure::Pawn, nColor), chess_board(new_chess_board), mSprite(), pawn_all_move() {
	this->setPosition(Position);
}
void Pawn::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// вывод пешки 
	}


unsigned mindex_correct_position(float position, float Screen_size) {
	float returned_val = 0.f;
	int per = position / (Screen_size/16);
	if (per % 2 == 0) {
		returned_val = (per) / 2;
		return returned_val;
	}
	returned_val = (per - 1) / 2;
	return returned_val;
	
}

void vertical_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& pawn_all_move, bool is_first_move, float Screen_size) {
	float l = Screen_size / 8;
	if (is_first_move == 1) {
		if (fcolor == 0) {
			for (unsigned i = y + 1; i < y + 3; i++) {
				if (chess_board[i][x] == 0 && i < 8) {
					float xc = x * l + l/2;
					float yc = (i) * l + l/2;
					pawn_all_move.push_back(sf::Vector2f(xc, yc));
				}
				else {
					return;
				}
			} 
		}
		else {
			for (unsigned i = y - 1 ; i > y - 3; i--) {
				if (chess_board[i][x] == 0 && i >= 0) {
					float xc = x * l + l/2;
					float yc = (i) * l + l/2;
					pawn_all_move.push_back(sf::Vector2f(xc, yc));
				}
				else {
					return;
				}
			}
		}
	}
	else {
		if (fcolor == 0) {
			if (x < 8) {
				unsigned i = y + 1;
				if (chess_board[i][x] == 0 && i >= 0) {
					float xc = x * l + l / 2;
					float yc = (i)*l + l / 2;
					pawn_all_move.push_back(sf::Vector2f(xc, yc));
				}
			}
		}
		else {
			if (y > 0) {
				unsigned i = y - 1;
				if (chess_board[i][x] == 0 && i >= 0) {
					float xc = x * l + l/2;
					float yc = (i) * l + l/2;
					pawn_all_move.push_back(sf::Vector2f(xc, yc));
				}
			}
		}
	}
}

void Pawn::update_move( float Screen_size) {
	bool is_first_move = 0;
	unsigned x = mindex_correct_position(this->getPosition().x, Screen_size);
	unsigned y = mindex_correct_position(this->getPosition().y, Screen_size);
	unsigned fcolor = this->getColor();
	pawn_all_move.clear();
	if (y == 1 && fcolor == 0) {
		is_first_move = 1;
	}
	else if (y == 6 && fcolor == 1) {
		is_first_move = 1;
	}
	vertical_move(chess_board, x, y, fcolor, pawn_all_move, is_first_move, Screen_size);
	float xl = (Screen_size / 8);
	if (fcolor == 0) {
		if (x > 0 && y + 1 < 8 && x - 1 >= 0 && (chess_board[y + 1][x - 1] == 2 || chess_board[y + 1][x - 1] == 4)) {
			chess_board[y + 1][x - 1] = 4;
			pawn_all_move.push_back(sf::Vector2f( (x - 1) * xl + (xl / 2), (y + 1) * xl + (xl/2) ) );
		}
		if (y + 1 < 8 && x + 1 < 8 && (chess_board[y + 1][x + 1] == 2 || chess_board[y + 1][x + 1] == 4)) {
			chess_board[y + 1][x + 1] = 4;
			pawn_all_move.push_back(sf::Vector2f((x + 1) * xl + xl/2, (y + 1) * xl + xl/2));
		}
	}
	else {
		if (y > 0 && x > 0 && (chess_board[y - 1][x - 1] == 1 || chess_board[y - 1][x - 1] == 3)) {
			chess_board[y - 1][x - 1] = 3;
			pawn_all_move.push_back(sf::Vector2f((x - 1) * xl + xl/2, (y - 1) * xl + xl/2));
		}
		if (y > 0 && x + 1 < 8 && (chess_board[y - 1][x + 1] == 1 || chess_board[y - 1][x + 1] == 3)) {
			chess_board[y - 1][x + 1] = 3;
			pawn_all_move.push_back(sf::Vector2f((x + 1) * xl + xl/2, (y - 1) * xl + xl/2));
		}
	}
}