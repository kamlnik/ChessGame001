#include <My_lib/Pawn.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>

Textures::ID toTextureID(unsigned t)
{
	if (t == 0) { // 0 это чёрное 
		return Textures::bPawn;
	}
	else {
		return Textures::wPawn;
	}
}

Pawn::Pawn(Color ncolor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]) : Figure(Type::Pawn, ncolor), pawn_all_move(), chess_board(new_chess_board), mSprite(textures.get(toTextureID(ncolor))) { this->set_boundingBox(mSprite.getGlobalBounds()); }


void Pawn::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// вывод пешки 
	}


unsigned mindex_correct_position(float position) {
	float returned_val = 0.f;
	int per = position / 50;
	if (per % 2 == 0) {
		returned_val = (per) / 2;
		return returned_val;
	}
	returned_val = (per - 1) / 2;
	return returned_val;
}

void vertical_move(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& pawn_all_move, bool is_first_move) {
	if (is_first_move == 1) {
		if (fcolor == 0) {
			for (auto i = y + 1; i < y + 3; i++) {
				if (chess_board[i][x] == 0 && i + 1 < 8) {
					float xc = x * 100 + 50;
					float yc = (i ) * 100 + 50;
					std::cout << xc << "\\" << yc << std::endl;
					pawn_all_move.push_back(sf::Vector2f(xc, yc));
				}
				else {
					return;
				}
			} ////////////////////////////////////////////// очень много ошибок тут 
		}
		else {
			for (auto i = y - 1 ; i > y - 3; i--) {
				if (chess_board[i][x] == 0 && i - 1 > 0) {
					float xc = x * 100 + 50;
					float yc = (i) * 100 + 50;
					std::cout << xc << "\\" << yc << std::endl;
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
			for (auto i = y + 1; i < y + 2; i++) {
				if (chess_board[i][x] == 0 && i + 1 < 8) {
					float xc = x * 100 + 50;
					float yc = (i ) * 100 + 50;
					std::cout << xc << "\\" << yc << std::endl;
					pawn_all_move.push_back(sf::Vector2f(xc, yc));
				}
				else {
					return;
				}
			}
		}
		else {
			for (auto i = y - 1; i > y - 2; i--) {
				if (chess_board[i][x] == 0 && i - 1 > 0) {
					float xc = x * 100 + 50;
					float yc = (i) * 100 + 50;
					std::cout << xc << "\\" << yc << std::endl;
					pawn_all_move.push_back(sf::Vector2f(xc, yc));
				}
				else {
					return;
				}
			}
		}
	}
}

void Pawn::update_move() {
	std::cout << "new" << std::endl;
	is_under_attack = 0;
	bool is_first_move = 0;
	unsigned x = mindex_correct_position(this->getPosition().x);
	unsigned y = mindex_correct_position(this->getPosition().y);
	unsigned fcolor = this->getColor();
	//if (chess_board[y][x] == 4) {
	//	is_under_attack = 1;
	//}else if(chess_board[y][x] == 4)
	//chess_board[y][x] = this->getColor() + 1;
	pawn_all_move.clear();
	if (y == 1 && fcolor == 0) {
		is_first_move = 1;
	}
	else if (y == 6 && fcolor == 1) {
		is_first_move = 1;
	}
	vertical_move(chess_board, x, y, fcolor, pawn_all_move, is_first_move);
	if (fcolor == 0) {
		if (y + 1 < 8 && x - 1 < 8 && (chess_board[y + 1][x - 1] == 2 || chess_board[y + 1][x - 1] == 4)) {
			chess_board[y + 1][x - 1] = 4;
			pawn_all_move.push_back(sf::Vector2f((x - 1) * 100 + 50, (y + 1) * 100 + 50));
		}
		if (y + 1 < 8 && x + 1 < 8 && (chess_board[y + 1][x + 1] == 2 || chess_board[y + 1][x + 1] == 4)) {
			chess_board[y + 1][x + 1] = 4;
			pawn_all_move.push_back(sf::Vector2f((x + 1) * 100 + 50, (y + 1) * 100 + 50));
		}
	}
	else {
		if (y - 1 < 8 && x - 1 < 8 && (chess_board[y - 1][x - 1] == 1 || chess_board[y - 1][x - 1] == 3)) {
			chess_board[y - 1][x - 1] = 3;
			pawn_all_move.push_back(sf::Vector2f((x - 1) * 100 + 50, (y - 1) * 100 + 50));
		}
		if (y - 1 < 8 && x + 1 < 8 && (chess_board[y - 1][x + 1] == 1 || chess_board[y - 1][x + 1] == 3)) {
			chess_board[y - 1][x + 1] = 3;
			pawn_all_move.push_back(sf::Vector2f((x + 1) * 100 + 50, (y - 1) * 100 + 50));
		}
	}
	
}