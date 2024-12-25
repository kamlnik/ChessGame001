#include <My_lib/Bishop.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
Textures::ID BishopTextureID(unsigned t)
{
	if (t == 0) { // 0 это чёрное 
		return Textures::bBishop;
	}
	else {
		return Textures::wBishop;
	}
}
Bishop::Bishop(Color ncolor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]) :Figure(Type::Bishop, ncolor), bishop_all_move(), chess_board(new_chess_board), mSprite(textures.get(BishopTextureID(ncolor))) {}

void Bishop::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// вывод 
}
unsigned mindex_correct_position_for_bishop(float position, float Screen_size) {
	float returned_val = 0.f;
	int per = position / (Screen_size / 16);
	if (per % 2 == 0) {
		returned_val = (per) / 2;
		return returned_val;
	}
	returned_val = (per - 1) / 2;
	return returned_val;

}
void diagonal_right_up_move_for_bishop(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& bishop_all_move, float Screen_size) {
	float l = Screen_size / 8;
	if (y == 0 || x == 7) {
		return;
	}
	unsigned t1 = y - 1;
	unsigned t2 = x + 1;
	while (t1 >= 0 && t2 < 8) {
		float xc = t2 * l + l / 2;
		float yc = (t1)*l + l / 2;
		if (chess_board[t1][t2] != 0) {
			if (fcolor == 0 && (chess_board[t1][t2] == 2 || chess_board[t1][t2] == 4)) {
				chess_board[t1][t2] = 4;
				bishop_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t1][t2] == 1 || chess_board[t1][t2] == 3)) {
				chess_board[t1][t2] = 3;
				bishop_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		bishop_all_move.push_back(sf::Vector2f(xc, yc));
		if (t1 == 0 || t2 == 7) {
			return;
		}
		t1--;
		t2++;
	}
}

void diagonal_left_dawn_move_for_bishop(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& bishop_all_move, float Screen_size) {
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
				bishop_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t1][t2] == 1 || chess_board[t1][t2] == 3)) {
				chess_board[t1][t2] = 3;
				bishop_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		bishop_all_move.push_back(sf::Vector2f(xc, yc));
		if (t1 == 7 || t2 == 0) {
			return;
		}
		t1++;
		t2--;
	}
}

void diagonal_right_dawn_move_for_bishop(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& bishop_all_move, float Screen_size) {
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
				bishop_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t1][t2] == 1 || chess_board[t1][t2] == 3)) {
				chess_board[t1][t2] = 3;
				bishop_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		bishop_all_move.push_back(sf::Vector2f(xc, yc));
		if (t1 == 7 || t2 == 7) {
			return;
		}
		t1++;
		t2++;
	}
}

void diagonal_left_up_move_for_bishop(unsigned(&chess_board)[8][8], unsigned x, unsigned y, unsigned fcolor, std::vector<sf::Vector2f>& bishop_all_move, float Screen_size) {
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
				bishop_all_move.push_back(sf::Vector2f(xc, yc));
			}
			else if (fcolor == 1 && (chess_board[t1][t2] == 1 || chess_board[t1][t2] == 3)) {
				chess_board[t1][t2] = 3;
				bishop_all_move.push_back(sf::Vector2f(xc, yc));
			}
			return;
		}
		bishop_all_move.push_back(sf::Vector2f(xc, yc));
		if (t1 == 0 || t2 == 0) {
			return;
		}
		t1--;
		t2--;
	}
}


void Bishop::update_move(float Screensize) {
	unsigned x = mindex_correct_position_for_bishop(this->getPosition().x, Screensize);
	unsigned y = mindex_correct_position_for_bishop(this->getPosition().y, Screensize);
	unsigned fcolor = this->getColor();
	float xl = (Screensize / 8);
	bishop_all_move.clear();
	diagonal_left_dawn_move_for_bishop(chess_board, x, y, fcolor, bishop_all_move, Screensize);
	diagonal_left_up_move_for_bishop(chess_board, x, y, fcolor, bishop_all_move, Screensize);
	diagonal_right_dawn_move_for_bishop(chess_board, x, y, fcolor, bishop_all_move, Screensize);
	diagonal_right_up_move_for_bishop(chess_board, x, y, fcolor, bishop_all_move, Screensize);
}

/*bool Kdtree::can_make_this_move(std::shared_ptr<Figure> Wking, std::shared_ptr<Figure> Bking, std::shared_ptr<kdNode> fptr, sf::Vector2f Previos_position, sf::Vector2f New_position, unsigned is_delete, float Screensize, unsigned(&chessboard)[8][8]) {
	if (fptr == nullptr) {
		throw std::runtime_error("ChangeNode Error: pointer = nullptr");
	}
	if (fptr->getthis() == nullptr) {
		throw std::runtime_error("ChangeNode Error: pointer to figure = nullptr");
	}
	fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
	DeleteNode(fptr);
	std::shared_ptr<kdNode> deleted_element = nullptr;
	if (is_delete == 1) {
		deleted_element = FindNode(New_position.x, New_position.y);
		DeleteNode(New_position.x, New_position.y);
	}
	fptr->getthis()->setPosition(New_position.x, New_position.y);
	AddNode(fptr);
	unsigned Nx = index_correct_position(New_position.x, Screensize);
	unsigned Ny = index_correct_position(New_position.y, Screensize);
	unsigned Px = index_correct_position(Previos_position.x, Screensize);
	unsigned Py = index_correct_position(Previos_position.y, Screensize);
	chessboard[Py][Px] = 0;
	chessboard[Ny][Nx] = (fptr->getthis()->getColor()) + 1;
	unsigned t = fptr->getthis()->getColor();
	update(Screensize, chessboard);
	if ((t == 1 && Wking->get_is_under_attack() == 1) || (t == 0 && Bking->get_is_under_attack() == 1)) {
		DeleteNode(fptr);
		fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
		AddNode(fptr);
		chessboard[Ny][Nx] = 0;
		chessboard[Py][Px] = fptr->getthis()->getColor() + 1;
		if (deleted_element != nullptr) {
			AddNode(deleted_element);
			chessboard[Ny][Nx] = deleted_element->getthis()->getColor() + 1;
		}
		update(Screensize, chessboard);
		return 1;
	}

	return 0;
}*/
