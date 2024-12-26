#include <My_lib/Knight.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
Textures::ID KnightTextureID(unsigned t)
{
	if (t == 0) { // 0 это чёрное 
		return Textures::bKnight;
	}
	else {
		return Textures::wKnight;
	}
}
Knight::Knight(Color ncolor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]) :Figure(Type::Knight, ncolor), knight_all_move(), chess_board(new_chess_board), mSprite(textures.get(KnightTextureID(ncolor))) {}

void Knight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// вывод king
}

Knight::Knight(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]):Figure(Figure::Knight, nColor), chess_board(new_chess_board), mSprite(), knight_all_move() {
	this->setPosition(Position);
}

unsigned mindex_correct_position_for_knight(float position, float Screen_size) {
	float returned_val = 0.f;
	int per = position / (Screen_size / 16);
	if (per % 2 == 0) {
		returned_val = (per) / 2;
		return returned_val;
	}
	returned_val = (per - 1) / 2;
	return returned_val;

}


void Knight::update_move(float Screen_size) {
	unsigned x = mindex_correct_position_for_knight(this->getPosition().x, Screen_size);
	unsigned y = mindex_correct_position_for_knight(this->getPosition().y, Screen_size);
	unsigned fcolor = this->getColor();
	float xl = (Screen_size / 8);
	knight_all_move.clear();
	if (x < 6 && y > 0) {
		if (fcolor == 0) {
			if (chess_board[y - 1][x + 2] == 2 || chess_board[y - 1][x + 2] == 4) {
				chess_board[y - 1][x + 2] = 4;
			}
			if (chess_board[y - 1][x + 2] != 1 && chess_board[y - 1][x + 2] != 3) {
				knight_all_move.push_back(sf::Vector2f((x + 2) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
			
		}
		else {
			if (chess_board[y - 1][x + 2] == 1 || chess_board[y - 1][x + 3] == 3) {
				chess_board[y - 1][x + 2] = 3;
			}
			if (chess_board[y - 1][x + 2] != 2 && chess_board[y - 1][x + 2] != 4) {
				knight_all_move.push_back(sf::Vector2f((x + 2) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
			}
		}
	}
	if (x < 7 && y > 1) {
		if (fcolor == 0) {
			if (chess_board[y - 2][x + 1] == 2 || chess_board[y - 2][x + 1] == 4) {
				chess_board[y - 2][x + 1] = 4;
			}
			if (chess_board[y - 2][x + 1] != 1 && chess_board[y - 2][x + 1] != 3) {
				knight_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y - 2) * xl + (xl / 2)));
			}
			
		}
		else {
			if (chess_board[y - 2][x + 1] == 1 || chess_board[y - 2][x + 1] == 3) {
				chess_board[y - 2][x + 1] = 3;
			}
			if ((chess_board[y - 2][x + 1] != 2 && chess_board[y - 2][x + 1] != 4))
				knight_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y - 2) * xl + (xl / 2)));
		}
	}
	if (x < 6 && y < 7) {
		if (fcolor == 0) {
			if (chess_board[y + 1][x + 2] == 2 || chess_board[y + 1][x + 2] == 4) {
				chess_board[y + 1][x + 2] = 4;
			}
			if(chess_board[y + 1][x + 2] != 1 && chess_board[y + 1][x + 2] != 3)
				knight_all_move.push_back(sf::Vector2f((x + 2) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
		}
		else {
			if (chess_board[y + 1][x + 2] == 1 || chess_board[y + 1][x + 2] == 3) {
				chess_board[y + 1][x + 2] = 3;
			}
			if(chess_board[y + 1][x + 2] != 2 && chess_board[y + 1][x + 2] != 4)
				knight_all_move.push_back(sf::Vector2f((x + 2) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
		}
	}
	if (x < 7 && y < 6) {
		if (fcolor == 0) {
			if (chess_board[y + 2][x + 1] == 2 || chess_board[y + 2][x + 1] == 4) {
				chess_board[y + 2][x + 1] = 4;
			}
			if(chess_board[y + 2][x + 1] != 1 && chess_board[y + 2][x + 1] != 3)
				knight_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y + 2) * xl + (xl / 2)));
		}
		else {
			if (chess_board[y + 2][x + 1] == 1 || chess_board[y + 2][x + 1] == 3) {
				chess_board[y + 2][x + 1] = 3;
			}
			if(chess_board[y + 2][x + 1] != 2 && chess_board[y + 2][x + 1] != 4)
				knight_all_move.push_back(sf::Vector2f((x + 1) * xl + (xl / 2), (y + 2) * xl + (xl / 2)));
		}
	} 
	if (x > 0 && y < 6) {
		if (fcolor == 0) {
			if (chess_board[y + 2][x - 1] == 2 || chess_board[y + 2][x - 1] == 4) {
				chess_board[y + 2][x - 1] = 4;
			}
			if(chess_board[y + 2][x - 1] != 1 && chess_board[y + 2][x - 1] != 3)
				knight_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y + 2) * xl + (xl / 2)));
		}
		else {
			if (chess_board[y + 2][x - 1] == 1 || chess_board[y + 2][x + 1] == 3) {
				chess_board[y + 2][x - 1] = 3;
			}
			if(chess_board[y + 2][x - 1] != 2 && chess_board[y + 2][x + 1] != 4)
				knight_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y + 2) * xl + (xl / 2)));
		}
	}
	if (x > 1 && y < 7) {
		if (fcolor == 0) {
			if (chess_board[y + 1][x - 2] == 2 || chess_board[y + 1][x - 2] == 4) {
				chess_board[y + 1][x - 2] = 4;
			}
			if(chess_board[y + 1][x - 2] != 1 && chess_board[y + 1][x - 2] != 3)
				knight_all_move.push_back(sf::Vector2f((x - 2) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
		}
		else {
			if (chess_board[y + 1][x - 2] == 1 || chess_board[y + 1][x - 2] == 3) {
				chess_board[y + 1][x - 2] = 3;
			}
			if(chess_board[y + 1][x - 2] != 2 && chess_board[y + 1][x - 2] != 4)
				knight_all_move.push_back(sf::Vector2f((x - 2) * xl + (xl / 2), (y + 1) * xl + (xl / 2)));
		}
	}
	if (x > 1 && y > 0) {
		if (fcolor == 0) {
			if (chess_board[y - 1][x - 2] == 2 || chess_board[y - 1][x - 2] == 4) {
				chess_board[y - 1][x - 2] = 4;
			}
			if(chess_board[y - 1][x - 2] != 1 && chess_board[y - 1][x - 2] != 3)
				knight_all_move.push_back(sf::Vector2f((x - 2) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
		}
		else {
			if (chess_board[y - 1][x - 2] == 1 || chess_board[y - 1][x - 2] == 3) {
				chess_board[y - 1][x - 2] = 3;
			}
			if(chess_board[y - 1][x - 2] != 2 && chess_board[y - 1][x - 2] != 4)
				knight_all_move.push_back(sf::Vector2f((x - 2) * xl + (xl / 2), (y - 1) * xl + (xl / 2)));
		}
	}
	if (x > 0 && y > 1) {
		if (fcolor == 0) {
			if (chess_board[y - 2][x - 1] == 2 || chess_board[y - 2][x - 1] == 4) {
				chess_board[y - 2][x - 1] = 4;
			}
			if(chess_board[y - 2][x - 1] != 1 && chess_board[y - 2][x - 1] != 3)
				knight_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y - 2) * xl + (xl / 2)));
		}
		else {
			if (chess_board[y - 2][x - 1] == 1 || chess_board[y - 2][x - 1] == 3) {
				chess_board[y - 2][x - 1] = 3;
			}
			if(chess_board[y - 2][x - 1] != 2 && chess_board[y - 2][x - 1] != 4)
				knight_all_move.push_back(sf::Vector2f((x - 1) * xl + (xl / 2), (y - 2) * xl + (xl / 2)));
		}
	}
}