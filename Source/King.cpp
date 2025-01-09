#include <My_lib/King.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
Textures::ID KingTextureID(unsigned t)
{
	if (t == 0) { // 0 это чёрное 
		return Textures::bKing;
	}
	else {
		return Textures::wKing;
	}
}
King::King(Color ncolor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]) :Figure(Type::King, ncolor), king_all_move(), chess_board(new_chess_board), mSprite(textures.get(KingTextureID(ncolor))), first_move(1) {}

void King::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// вывод king
}
King::King(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]) : Figure(Figure::King, nColor), chess_board(new_chess_board), mSprite(), king_all_move(), first_move(1) {
	this->setPosition(Position);
}
bool King::is_first_move() {
	return first_move;
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

bool left_white_castling(unsigned(&chess_board)[8][8], unsigned x, unsigned y) {
	if (x != 4 || y != 7) {
		return 0;
	}
	for (int xl = x - 1; xl > 0; xl--) {
		if (chess_board[y][xl] != 0) {
			return 0;
		}
	}
	return 1;
}

bool right_white_castling(unsigned(&chess_board)[8][8], unsigned x, unsigned y) {
	if (x != 4 || y != 7) {
		return 0;
	}
	for (int xl = x + 1; xl < 7; xl++) {
		if (chess_board[y][xl] != 0) {
			return 0;
		}
	}
	return 1;
}

bool left_black_castling(unsigned(&chess_board)[8][8], unsigned x, unsigned y) {
	if (x != 3 || y != 0) {
		return 0;
	}
	for (int xl = x - 1; xl > 0; xl--) {
		if (chess_board[y][xl] != 0) {
			return 0;
		}
	}
	return 1;
}

bool right_black_castling(unsigned(&chess_board)[8][8], unsigned x, unsigned y) {
	if (x != 3 || y != 0) {
		return 0;
	}
	for (int xl = x + 1; xl < 7; xl++) {
		if (chess_board[y][xl] != 0) {
			return 0;
		}
	}
	return 1;
}

void castling(unsigned fcolor, unsigned(&chess_board)[8][8], std::vector<sf::Vector2f>& king_all_move, float Screen_size, unsigned x, unsigned y) {
	float xl = (Screen_size / 8);
	if (fcolor == 1) {
		if (left_white_castling(chess_board, x, y) == 1) {
			king_all_move.push_back(sf::Vector2f((x - 2) * xl + (xl / 2), (y) * xl + (xl / 2)));
		}
		if (right_white_castling(chess_board, x, y) == 1) {
			king_all_move.push_back(sf::Vector2f((x + 2) * xl + (xl / 2), (y) * xl + (xl / 2)));
		}
	}
	else {
		if (left_black_castling(chess_board, x, y) == 1) {
			king_all_move.push_back(sf::Vector2f((x - 2) * xl + (xl / 2), (y)*xl + (xl / 2)));
		}
		if (right_black_castling(chess_board, x, y) == 1) {
			king_all_move.push_back(sf::Vector2f((x + 2) * xl + (xl / 2), (y)*xl + (xl / 2)));
		}
	}
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
	if (first_move == 1 && (chess_board[y][x] == 2 || chess_board[y][x] == 1)) {
		//std::cout << "daun" << std::endl;
		castling(fcolor, chess_board, king_all_move, Screen_size, x, y);
	}
}