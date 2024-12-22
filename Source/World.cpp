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

	//, mSceneGraph()
	//, mSceneLayers()
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
	//mWindow.draw(mStatisticsText);
	mWindow.display();
}


void World::loadTextures()
{
	mTextures.load(Textures::Chess_board, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/Chess_board2.png");
	mTextures.load(Textures::wPawn, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wP.png");
	mTextures.load(Textures::bPawn, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/bP.png");
	mTextures.load(Textures::bKing, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/bK.png");
	mTextures.load(Textures::wKing, "C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wK.png");
}

unsigned index_correct_position(float position, float Screen_size) {
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
/*	std::unique_ptr<Pawn> wPawn1(new Pawn(Figure::white, mTextures));
	wPawn1.get()->setOrigin(40.f, 40.f);
	wPawn1->setPosition(450.f, 650.f);
	std::shared_ptr <kdNode> node1(new kdNode(std::move(wPawn1)));
	Chesstree.AddNode(node1);
	std::unique_ptr<Pawn> wPawn2(new Pawn(Figure::white, mTextures));
	wPawn2.get()->setOrigin(40.f, 40.f);
	wPawn2->setPosition(250.f, 650.f);
	std::shared_ptr <kdNode> node2(new kdNode(std::move(wPawn2)));
	Chesstree.AddNode(node2);
	Chesstree.DeleteNode(450.f, 650.f);*/

	for (int i = 0; i < 8; i++) {
		std::unique_ptr<Pawn> wPawn(new Pawn(Figure::white, mTextures, Chess_board_for_figures));
		//wPawn->mSprite.scale(1.5, 1.5);
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
		//bPawn.get()->scale(Scale_value, Scale_value);
		//bPawn.get()->setOrigin(40.f * Scale_value, 40.f * Scale_value);
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



	Chesstree.update( Screen_width, Chess_board_for_figures);
	//Chesstree.update_all_status(Chess_board_for_figures);

	//func_print_desk(Chess_board_for_figures);
//	std::shared_ptr<kdNode>* Needed_element = nullptr;
	//tree_bypass(Chesstree.getroot(), 0.f, 0.f, Needed_element);//std::cout << Chesstree.getroot()->getleftchild()->getthis()->getPosition().x << Chesstree.getroot()->getleftchild()->getthis()->getPosition().y;
	//Chesstree.tree_bypass(0.f, 0.f);
	//std::cout << Chesstree.getroot()->getrightchild()->getrightchild()->getthis()->getPosition().x << Chesstree.getroot()->getrightchild()->getrightchild()->getthis()->getPosition().y;
	//if ((Chesstree.getroot())->getleftchild() == nullptr) {
	//	throw std::runtime_error("4444");
	//}
	//std::cout << Chesstree.getroot()->getthis()->getPosition().x << Chesstree.getroot()->getthis()->getPosition().y;
	//if (Chesstree.getroot()->getleftchild() == nullptr) {
	////	throw std::runtime_error("leftchild");
	//}
	//std::shared_ptr<kdNode>* Needed_element = nullptr;
	//Chesstree.tree_bypass(Chesstree.getroot(), 1110.f, 1111.f, Needed_element);
	//Chesstree.DeleteNode(450.f, 650.f);
	//std::unique_ptr<Figure> testptr = wPawn1;
	//mFigure = std::move(wPawn1);
	//Figure* test = Pawn(Figure::white, mTextures);
	//std::cout << mFigure->getPosition().x;;
	//std::cout << (*mFigure).getPosition().x;
	//(*mFigure).getPosition().x
	/*for (std::size_t i = 0; i < LayerCount; ++i) // инициализация слоёв 
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}*/
	/*SceneNode::Ptr layer(new SceneNode());
	mSceneLayers.push_back(layer.get());
	mSceneGraph.attachChild(std::move(layer));
	sf::Texture& texture = mTextures.get(Textures::Chess_board);
	sf::IntRect textureRect(mWorldBounds);
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(0, 0);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Figure> wPawn1(new Figure(Figure::wPawn, mTextures));  //
	wPawn1.get()->setOrigin(40.f, 40.f);
	wPawn1->setPosition(450.f, 650.f);
	std::cout << wPawn1.get()->getPosition().x;
	mSceneLayers[Background]->attachChild(std::move(wPawn1));// Инициализация фигур

	//mSceneLayers[Background]->attachChild(std::move(wPawn1)); // ничего не понимаю 
	std::unique_ptr<Figure> bPawn1(new Figure(Figure::bPawn, mTextures));  // 
	bPawn1.get()->setOrigin(40.f, 40.f);
	bPawn1->sf::Transformable::setPosition(50.f, 150.f); //
	mSceneGraph.attachChild(std::move(bPawn1));
	//mSceneLayers[Background]->attachChild(std::move(bPawn1));
	*/
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
	//std::shared_ptr<kdNode> changed_element;
	std::vector<std::shared_ptr<kdNode>> moved_element;
	sf::Vector2f Previos_Position;
	while (mWindow.isOpen())
	{
		this->draw();
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
							unsigned Nx = index_correct_position(New_position.x, Screen_width);
							unsigned Ny = index_correct_position(New_position.y, Screen_width);
							unsigned Px = index_correct_position(Previos_Position.x, Screen_width);
							unsigned Py = index_correct_position(Previos_Position.y, Screen_width);
							if ((Chess_board_for_figures[Ny][Nx] == 3 && moved_element.front()->getthis()->getColor() == 1) || (Chess_board_for_figures[Ny][Nx] == 4 && moved_element.front()->getthis()->getColor() == 0)) {
								Chesstree.ChangeNode(moved_element.front(), Previos_Position, New_position, 1);
							}
							else {
								Chesstree.ChangeNode(moved_element.front(), Previos_Position, New_position, 0);
							}
							Chess_board_for_figures[Py][Px] = 0;
							Chess_board_for_figures[Ny][Nx] = (moved_element.front()->getthis()->getColor()) + 1;
							Chesstree.update(Screen_width ,Chess_board_for_figures);
							if (Whoose_move) {
								Whoose_move = 0;
							}
							else {
								Whoose_move = 1;
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

