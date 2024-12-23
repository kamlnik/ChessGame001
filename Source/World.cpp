#include <My_lib/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <vector>


World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, Chess_board()
	, Chesstree()
{
	Screen_width = mWindow.getSize().y;
	Scale_value = Screen_width / 800;
	loadTextures();
	buildScene();

}


void World::draw() // нужна отрисовка дерева фигур 
{
	mWindow.clear();
	mWindow.setView(mWorldView);
	mWindow.draw(Chess_board);
	Chesstree.drawtree(mWindow);
	mWindow.display();
}


void World::loadTextures()
{
	mTextures.load(Textures::Chess_board, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/Chess_board2.png");
	mTextures.load(Textures::wPawn, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wP.png");
	mTextures.load(Textures::bPawn, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/bP.png");
	mTextures.load(Textures::bKing, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/bK.png");
	mTextures.load(Textures::wKing, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wK.png");
	mTextures.load(Textures::wQueen, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wQ.png");
	mTextures.load(Textures::bQueen, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/bQ.png");
	mTextures.load(Textures::wRook, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wR.png");
	mTextures.load(Textures::bRook, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/bR.png");
	mTextures.load(Textures::wBishop, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wB.png");
	mTextures.load(Textures::bBishop, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/bB.png");
	mTextures.load(Textures::wKnight, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wN.png");
	mTextures.load(Textures::bKnight, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/bN.png");
}

unsigned new_index_correct_position(float position, float Screen_size) {
	float returned_val = 0.f;
	int per = position / (Screen_size/16);
	if (per % 2 == 0) {
		returned_val = (per) / 2 ;
		return returned_val;
	}
	returned_val = (per - 1) / 2;
	return returned_val;
}

void func_print_desk(const unsigned(&chess_borad)[8][8]) {
	for (int t = 0; t < 8; t++) {
		for (int r = 0; r < 8; r++) {
			std::cout << chess_borad[t][r];
		}
		std::cout << std::endl;
	}
}

void World::buildScene() {
	sf::Texture& texture = mTextures.get(Textures::Chess_board);
	sf::IntRect textureRect(mWorldBounds);
	Chess_board.setTexture(texture, true); // не знаю зачем true или false 
	Chess_board.scale(Scale_value , Scale_value);

	for (int i = 0; i < 8; i++) {
		std::unique_ptr<Pawn> wPawn(new Pawn(Figure::white, mTextures, Chess_board_for_figures));
		wPawn.get()->setOrigin(40.f, 40.f);
		wPawn.get()->scale(Scale_value, Scale_value);
		wPawn.get()->getTransform();
		wPawn->setPosition(Screen_width / 16 + ( i * Screen_width / 8), 13 * Screen_width / 16);
		Chess_board_for_figures[6][i] = 2; // 0 - ничего 1 - чёрное 2 - белое 3 - чёрное под ударом 4 - белое под ударом 
		std::shared_ptr <kdNode> node(new kdNode(std::move(wPawn)));
		Chesstree.AddNode(node);
	}

	for (int i = 0; i < 8; i++) {
		std::unique_ptr<Pawn> bPawn(new Pawn(Figure::black, mTextures, Chess_board_for_figures));
		bPawn.get()->setOrigin(40.f, 40.f);
		bPawn.get()->scale(Scale_value, Scale_value);
		bPawn.get()->getTransform();
		bPawn->setPosition(Screen_width / 16 + (i * Screen_width) / 8, 3 * Screen_width / 16);
		Chess_board_for_figures[1][i] = 1;
		std::shared_ptr <kdNode> node(new kdNode(std::move(bPawn)));
		Chesstree.AddNode(node);
	}

	std::unique_ptr<King> wKing(new King(Figure::white, mTextures, Chess_board_for_figures));
	wKing.get()->setOrigin(40.f, 40.f);
	wKing.get()->scale(Scale_value, Scale_value);
	wKing.get()->getTransform();
	wKing->setPosition(Screen_width / 16 + (4 * Screen_width / 8), 15 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_wking(new kdNode(std::move(wKing)));
	WKing = node_for_wking->getthis();
	Chesstree.AddNode(node_for_wking);

	std::unique_ptr<King> bKing(new King(Figure::black, mTextures, Chess_board_for_figures));
	bKing.get()->setOrigin(40.f, 40.f);
	bKing.get()->scale(Scale_value, Scale_value);
	bKing.get()->getTransform();
	bKing->setPosition(Screen_width / 16 + (3 * Screen_width / 8), 1 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_bking(new kdNode(std::move(bKing)));
	BKing = node_for_bking->getthis();
	Chesstree.AddNode(node_for_bking);

	std::unique_ptr<Queen> wQueen(new Queen(Figure::white, mTextures, Chess_board_for_figures));
	wQueen.get()->setOrigin(40.f, 40.f);
	wQueen.get()->scale(Scale_value, Scale_value);
	wQueen.get()->getTransform();
	wQueen->setPosition(Screen_width / 16 + (3 * Screen_width / 8), 15 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_wQueen(new kdNode(std::move(wQueen)));
	Chesstree.AddNode(node_for_wQueen);
	
	std::unique_ptr<Queen> bQueen(new Queen(Figure::black, mTextures, Chess_board_for_figures));
	bQueen.get()->setOrigin(40.f, 40.f);
	bQueen.get()->scale(Scale_value, Scale_value);
	bQueen.get()->getTransform();
	bQueen->setPosition(Screen_width / 16 + (4 * Screen_width / 8), 1 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_bQueen(new kdNode(std::move(bQueen)));
	Chesstree.AddNode(node_for_bQueen);

	std::unique_ptr<Rook> wRook1(new Rook(Figure::white, mTextures, Chess_board_for_figures));
	wRook1.get()->setOrigin(40.f, 40.f);
	wRook1.get()->scale(Scale_value, Scale_value);
	wRook1.get()->getTransform();
	wRook1->setPosition(Screen_width / 16 + (0 * Screen_width / 8), 15 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_wRook1(new kdNode(std::move(wRook1)));
	Chesstree.AddNode(node_for_wRook1);

	std::unique_ptr<Rook> wRook2(new Rook(Figure::white, mTextures, Chess_board_for_figures));
	wRook2.get()->setOrigin(40.f, 40.f);
	wRook2.get()->scale(Scale_value, Scale_value);
	wRook2.get()->getTransform();
	wRook2->setPosition(Screen_width / 16 + (7 * Screen_width / 8), 15 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_wRook2(new kdNode(std::move(wRook2)));
	Chesstree.AddNode(node_for_wRook2);

	std::unique_ptr<Rook> bRook1(new Rook(Figure::black, mTextures, Chess_board_for_figures));
	bRook1.get()->setOrigin(40.f, 40.f);
	bRook1.get()->scale(Scale_value, Scale_value);
	bRook1.get()->getTransform();
	bRook1->setPosition(Screen_width / 16 + (0 * Screen_width / 8), 1 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_bRook1(new kdNode(std::move(bRook1)));
	Chesstree.AddNode(node_for_bRook1);

	std::unique_ptr<Rook> bRook2(new Rook(Figure::black, mTextures, Chess_board_for_figures));
	bRook2.get()->setOrigin(40.f, 40.f);
	bRook2.get()->scale(Scale_value, Scale_value);
	bRook2.get()->getTransform();
	bRook2->setPosition(Screen_width / 16 + (7 * Screen_width / 8), 1 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_bRook2(new kdNode(std::move(bRook2)));
	Chesstree.AddNode(node_for_bRook2);

	std::unique_ptr<Bishop> wBishop1(new Bishop(Figure::white, mTextures, Chess_board_for_figures));
	wBishop1.get()->setOrigin(40.f, 40.f);
	wBishop1.get()->scale(Scale_value, Scale_value);
	wBishop1.get()->getTransform();
	wBishop1->setPosition(Screen_width / 16 + (2 * Screen_width / 8), 15 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_wBishop1(new kdNode(std::move(wBishop1)));
	Chesstree.AddNode(node_for_wBishop1);

	std::unique_ptr<Bishop> wBishop2(new Bishop(Figure::white, mTextures, Chess_board_for_figures));
	wBishop2.get()->setOrigin(40.f, 40.f);
	wBishop2.get()->scale(Scale_value, Scale_value);
	wBishop2.get()->getTransform();
	wBishop2->setPosition(Screen_width / 16 + (5 * Screen_width / 8), 15 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_wBishop2(new kdNode(std::move(wBishop2)));
	Chesstree.AddNode(node_for_wBishop2);

	std::unique_ptr<Bishop> bBishop1(new Bishop(Figure::black, mTextures, Chess_board_for_figures));
	bBishop1.get()->setOrigin(40.f, 40.f);
	bBishop1.get()->scale(Scale_value, Scale_value);
	bBishop1.get()->getTransform();
	bBishop1->setPosition(Screen_width / 16 + (2 * Screen_width / 8), 1 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_bBishop1(new kdNode(std::move(bBishop1)));
	Chesstree.AddNode(node_for_bBishop1);

	std::unique_ptr<Bishop> bBishop2(new Bishop(Figure::black, mTextures, Chess_board_for_figures));
	bBishop2.get()->setOrigin(40.f, 40.f);
	bBishop2.get()->scale(Scale_value, Scale_value);
	bBishop2.get()->getTransform();
	bBishop2->setPosition(Screen_width / 16 + (5 * Screen_width / 8), 1 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_bBishop2(new kdNode(std::move(bBishop2)));
	Chesstree.AddNode(node_for_bBishop2);

	std::unique_ptr<Knight> wKnight1(new Knight(Figure::white, mTextures, Chess_board_for_figures));
	wKnight1.get()->setOrigin(40.f, 40.f);
	wKnight1.get()->scale(Scale_value, Scale_value);
	wKnight1.get()->getTransform();
	wKnight1->setPosition(Screen_width / 16 + (1 * Screen_width / 8), 15 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_wKnight1(new kdNode(std::move(wKnight1)));
	Chesstree.AddNode(node_for_wKnight1);

	std::unique_ptr<Knight> wKnight2(new Knight(Figure::white, mTextures, Chess_board_for_figures));
	wKnight2.get()->setOrigin(40.f, 40.f);
	wKnight2.get()->scale(Scale_value, Scale_value);
	wKnight2.get()->getTransform();
	wKnight2->setPosition(Screen_width / 16 + (6 * Screen_width / 8), 15 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_wKnight2(new kdNode(std::move(wKnight2)));
	Chesstree.AddNode(node_for_wKnight2);

	std::unique_ptr<Knight> bKnight1(new Knight(Figure::black, mTextures, Chess_board_for_figures));
	bKnight1.get()->setOrigin(40.f, 40.f);
	bKnight1.get()->scale(Scale_value, Scale_value);
	bKnight1.get()->getTransform();
	bKnight1->setPosition(Screen_width / 16 + (1 * Screen_width / 8), 1 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_bKnight1(new kdNode(std::move(bKnight1)));
	Chesstree.AddNode(node_for_bKnight1);

	std::unique_ptr<Knight> bKnight2(new Knight(Figure::black, mTextures, Chess_board_for_figures));
	bKnight2.get()->setOrigin(40.f, 40.f);
	bKnight2.get()->scale(Scale_value, Scale_value);
	bKnight2.get()->getTransform();
	bKnight2->setPosition(Screen_width / 16 + (6 * Screen_width / 8), 1 * Screen_width / 16);
	std::shared_ptr <kdNode> node_for_bKnight2(new kdNode(std::move(bKnight2)));
	Chesstree.AddNode(node_for_bKnight2);
	Chesstree.update( Screen_width, Chess_board_for_figures);
}
float correct_position(float position , float screen_size) {
	float returned_val = 0.f;
	int per = position / (screen_size / 16);
	if (per % 2 == 0) {
		returned_val = (per + 1) * (screen_size / 16);
		return returned_val;
	}
	returned_val = (per) * (screen_size / 16);
	return returned_val;
}
void tree_bypass(std::shared_ptr<kdNode> fptr, float xc, float yc, std::vector<std::shared_ptr<kdNode>>& Needed_elements, bool whoose_move, float Scale_value) {
	if (fptr != nullptr) {

		tree_bypass(fptr->getrightchild(), xc, yc, Needed_elements, whoose_move, Scale_value);
		//if ...
		sf::FloatRect rect(sf::Vector2f(fptr->getthis()->getPosition().x - 40* Scale_value, fptr->getthis()->getPosition().y - 40* Scale_value), sf::Vector2f(80.f * Scale_value, 80.f * Scale_value));
		unsigned val = fptr->getthis()->getColor();
		if (Needed_elements.empty() == true && val == whoose_move && rect.contains(xc, yc)) {
			Needed_elements.push_back(fptr);
		}
		tree_bypass(fptr->getleftchild(), xc, yc, Needed_elements, whoose_move, Scale_value);

	}
}
void putTree(std::shared_ptr <kdNode> ptr, int level)
{
	int i = level;
	if (ptr != nullptr) {

		putTree(ptr->getrightchild(), level + 1);
		while (i-- > 0) {
			std::cout << "      ";
		}
		std::cout << ptr.get()->getthis()->getPosition().x << " , " << ptr.get()->getthis()->getPosition().y <<ptr->getthis()->get_is_under_attack() <<std::endl;
		putTree(ptr->getleftchild(), level + 1);

	}
}
void World::World_processEvents() {
	bool isMove = false;//переменная для щелчка мыши по спрайту
	float dX = 0;
	float dY = 0;
	std::vector<std::shared_ptr<kdNode>> moved_element;
	sf::Vector2f Previos_Position;
	while (mWindow.isOpen())
	{
		this->draw();
		if (moved_element.empty() == false) {
			mWindow.draw(*(moved_element.front())->getthis());
		}
		sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);//забираем коорд курсора
		sf::Vector2f pos = mWindow.mapPixelToCoords(pixelPos);
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mWindow.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {

				if (event.key.code == sf::Mouse::Left) {
					tree_bypass(Chesstree.getroot(), pos.x, pos.y, moved_element, Whoose_move, Scale_value);
					if (moved_element.empty() == false) {
						Previos_Position = (moved_element.front())->getthis()->getPosition();
						dX = pos.x - (moved_element.front())->getthis()->getPosition().x;
						dY = pos.y - (moved_element.front())->getthis()->getPosition().y;
						isMove = true;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased ) {
				if (event.key.code == sf::Mouse::Left) {
					if (moved_element.empty() == false) {
						isMove = false;
						moved_element.front()->getthis()->setPosition(correct_position(moved_element.front()->getthis()->getPosition().x , Screen_width), correct_position(moved_element.front()->getthis()->getPosition().y , Screen_width));
						sf::Vector2f New_position = moved_element.front()->getthis()->getPosition();
						std::vector<sf::Vector2f> possible_moves = moved_element.front()->getthis()->all_move(); // тут проблема (как ожидалось )
						auto t = std::find(possible_moves.begin(), possible_moves.end(), New_position);
						if (t != possible_moves.end()) {
							
							unsigned Nx = new_index_correct_position(New_position.x, Screen_width);
							unsigned Ny = new_index_correct_position(New_position.y, Screen_width);
							unsigned Px = new_index_correct_position(Previos_Position.x, Screen_width);
							unsigned Py = new_index_correct_position(Previos_Position.y, Screen_width);
							unsigned t = 0;
							if ((Chess_board_for_figures[Ny][Nx] == 3 && moved_element.front()->getthis()->getColor() == 1) || (Chess_board_for_figures[Ny][Nx] == 4 && moved_element.front()->getthis()->getColor() == 0)) {
								t = Chesstree.can_make_this_move(WKing, BKing, moved_element.front(), Previos_Position, New_position, 1, Screen_width, Chess_board_for_figures);
							}
							else {
								t = Chesstree.can_make_this_move(WKing, BKing, moved_element.front(), Previos_Position, New_position, 0, Screen_width, Chess_board_for_figures);
							}
							/*if (Chesstree.IS_MATE(WKing, BKing, Screen_width, Chess_board_for_figures) == 1) {
								if (moved_element.front()->getthis()->getColor() == 1) {
									std::cout << "______ Mate to white ______" << std::endl;
								}
								else {
									std::cout << "______ Mate to black ______" << std::endl;
								}
							}*/
							if(WKing->get_is_under_attack() == 1){
								std::cout << "______ Check to white ______" << std::endl;
							}
							else if (BKing->get_is_under_attack() == 1) {
								std::cout << "______ Check to black ______" << std::endl;
							}
							else {
								std::cout << "____________________________" << std::endl;
							}
							/*if (WKing->get_is_under_attack() == 1) {
								std::cout << "______ Check to white ______" << std::endl;
							}else if (BKing->get_is_under_attack() == 1) {
								std::cout << "______ Check to black ______" << std::endl;
							}
							else {
								std::cout << "____________________________" << std::endl;
							}*/
							/*Chess_board_for_figures[Py][Px] = 0;
							Chess_board_for_figures[Ny][Nx] = (moved_element.front()->getthis()->getColor()) + 1;
							Chesstree.update(Screen_width ,Chess_board_for_figures);*/
							if (t == 0) {
								if (Whoose_move) {
									Whoose_move = 0;
								}
								else {
									Whoose_move = 1;
								}
							}
							func_print_desk(Chess_board_for_figures);
						}
						else {
							moved_element.front()->getthis()->setPosition(Previos_Position);
						}
						Previos_Position = sf::Vector2f(0.f, 0.f);
						moved_element.clear();
					}
				}
			}

		}
		if (isMove == true) {
			(moved_element.front())->getthis()->setPosition(pos.x - dX, pos.y - dY);
		}
	}
}

