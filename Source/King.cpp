#include <My_lib/King.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
Textures::ID KingTextureID(unsigned t)
{
	if (t == 0) { // 0 ��� ������ 
		return Textures::bKing;
	}
	else {
		return Textures::wKing;
	}
}
King::King(Color ncolor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]) :Figure(Type::King, ncolor), king_all_move(), chess_board(new_chess_board), mSprite(textures.get(KingTextureID(ncolor))) {}

void King::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// ����� king
}
King::King(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]) : Figure(Figure::King, nColor), chess_board(new_chess_board), mSprite(), king_all_move() {
	this->setPosition(Position);
}


unsigned mindex_correct_position_for_king(float position, float Screen_size) {
	float returned_val = 0.f;
	int per = position / (Screen_size / 16);
	if (per % 2 == 0) {
		returned_val = (per) / 2;
		return returned_val;
	}
	returned_val = (per - 1) / 2;
	return returned_val;

}


void King::update_move(float Screen_size) {
	unsigned x = mindex_correct_position_for_king(this->getPosition().x, Screen_size);
	unsigned y = mindex_correct_position_for_king(this->getPosition().y, Screen_size);
	unsigned fcolor = this->getColor();
	float xl = (Screen_size / 8);
	king_all_move.clear();
	if (y > 0 && x > 0 ) {
		if (fcolor == 0) {
			if (chess_board[y - 1][x - 1] == 2 || chess_board[y - 1][x - 1] == 4) {
				chess_board[y - 1][x - 1] = 4;
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
			else if (chess_board[y - 1][x - 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
		}
		else {
			if (chess_board[y - 1][x - 1] == 1 || chess_board[y - 1][x - 1] == 3) {
				chess_board[y - 1][x - 1] = 3;
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
			else if (chess_board[y - 1][x - 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
		}
	}
	
	if (y > 0) {
		if (fcolor == 0) {
			if (chess_board[y - 1][x] == 2 || chess_board[y - 1][x] == 4) {
				chess_board[y - 1][x] = 4;
				king_all_move.push_back(sf::Vector2f((x) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
			else if (chess_board[y - 1][x] == 0) {
				king_all_move.push_back(sf::Vector2f((x) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
		}
		else {
			if (chess_board[y - 1][x] == 1 || chess_board[y - 1][x] == 3) {
				chess_board[y - 1][x] = 3;
				king_all_move.push_back(sf::Vector2f((x) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
			else if (chess_board[y - 1][x] == 0) {
				king_all_move.push_back(sf::Vector2f((x) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
		}
	}
	if (y > 0 && x < 7) {
		if (fcolor == 0) {
			if (chess_board[y - 1][x + 1] == 2 || chess_board[y - 1][x + 1] == 4) {
				chess_board[y - 1][x + 1] = 4;
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
			else if (chess_board[y - 1][x + 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
		}
		else {
			if (chess_board[y - 1][x + 1] == 1 || chess_board[y - 1][x + 1] == 3) {
				chess_board[y - 1][x + 1] = 3;
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
			else if (chess_board[y - 1][x + 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
		}
	}
	if ( x < 7 ) {
		if (fcolor == 0) {
			if (chess_board[y][x + 1] == 2 || chess_board[y][x + 1] == 4) {
				chess_board[y][x + 1] = 4;
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y) * xl + (xl / 2)));
			}
			else if (chess_board[y][x + 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y) * xl + (xl / 2)));
			}
		}
		else {
			if (chess_board[y][x + 1] == 1 || chess_board[y][x + 1] == 3) {
				chess_board[y][x + 1] = 3;
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y) * xl + (xl / 2)));
			}
			else if (chess_board[y][x + 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y) * xl + (xl / 2)));
			}
		}
	}
	if (x > 0 ) {
		if (fcolor == 0) {
			if (chess_board[y][x - 1] == 2 || chess_board[y][x - 1] == 4) {
				chess_board[y][x - 1] = 4;
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y) * xl + (xl / 2)));
			}
			else if (chess_board[y][x - 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y) * xl + (xl / 2)));
			}
		}
		else {
			if (chess_board[y][x - 1] == 1 || chess_board[y][x - 1] == 3) {
				chess_board[y][x - 1] = 3;
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y) * xl + (xl / 2)));
			}
			else if (chess_board[y][x - 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y) * xl + (xl / 2)));
			}
		}
	}
	if (y < 7 && x < 7 ) {
		if (fcolor == 0) {
			if (chess_board[y + 1][x + 1] == 2 || chess_board[y + 1][x + 1] == 4) {
				chess_board[y + 1][x + 1] = 4;
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y+1)*xl + (xl / 2)));
			}
			else if (chess_board[y + 1][x + 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y+1)*xl + (xl / 2)));
			}
		}
		else {
			if (chess_board[y + 1][x + 1] == 1 || chess_board[y + 1][x + 1] == 3) {
				chess_board[y + 1][x + 1] = 3;
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y+1)*xl + (xl / 2)));
			}
			else if (chess_board[y + 1][x + 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y+1)*xl + (xl / 2)));
			}
		}
	}
	if (y < 7 ) {
		if (fcolor == 0) {
			if (chess_board[y + 1][x] == 2 || chess_board[y + 1][x] == 4) {
				chess_board[y + 1][x] = 4;
				king_all_move.push_back(sf::Vector2f((x) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
			}
			else if (chess_board[y + 1][x] == 0) {
				king_all_move.push_back(sf::Vector2f((x) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
			}
		}
		else {
			if (chess_board[y + 1][x] == 1 || chess_board[y + 1][x] == 3) {
				chess_board[y + 1][x] = 3;
				king_all_move.push_back(sf::Vector2f((x)*xl + (xl / 2), (y + 1) * xl + (xl / 2)));
			}
			else if (chess_board[y + 1][x] == 0) {
				king_all_move.push_back(sf::Vector2f((x)*xl + (xl / 2), (y + 1) * xl + (xl / 2)));
			}
		}
	}
	if (y < 7 && x > 0) {
		if (fcolor == 0) {
			if (chess_board[y + 1][x - 1] == 2 || chess_board[y + 1][x - 1] == 4) {
				chess_board[y + 1][x - 1] = 4;
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
			}
			else if (chess_board[y + 1][x - 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
			}
		}
		else {
			if (chess_board[y + 1][x - 1] == 1 || chess_board[y + 1][x - 1] == 3) {
				chess_board[y + 1][x - 1] = 3;
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
			}
			else if (chess_board[y + 1][x - 1] == 0) {
				king_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
			}
		}
	}
}