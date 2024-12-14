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
}


void World::buildScene() {
	
	sf::Texture& texture = mTextures.get(Textures::Chess_board);
	sf::IntRect textureRect(mWorldBounds);
	Chess_board.setTexture(texture, true); // не знаю зачем true или false 
//	*mFigure(Figure::Pawn, Figure::black);
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
		std::unique_ptr<Pawn> wPawn(new Pawn(Figure::white, mTextures));
		wPawn.get()->setOrigin(40.f, 40.f);
		wPawn->setPosition(50.f + i * 100.f, 650.f);
		std::shared_ptr <kdNode> node(new kdNode(std::move(wPawn)));
		Chesstree.AddNode(node);
	}
	for (int i = 0; i < 8; i++) {
		std::unique_ptr<Pawn> bPawn(new Pawn(Figure::black, mTextures));
		bPawn.get()->setOrigin(40.f, 40.f);
		bPawn->setPosition(50.f + i * 100.f, 150.f);
		std::shared_ptr <kdNode> node(new kdNode(std::move(bPawn)));
		Chesstree.AddNode(node);
	}

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

//	mFigure->setPosition(450.f, 650.f);
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
float correct_position(float position) {
	float returned_val = 0.f;
	int per = position / 50;
	if (per % 2 == 0) {
		returned_val = (per + 1) * 50;
		return returned_val;
	}
	returned_val = (per) * 50;
	return returned_val;
}
void tree_bypass(std::shared_ptr<kdNode> fptr, float xc, float yc, std::vector<std::shared_ptr<kdNode>>& Needed_elements, bool whoose_move) {
	if (fptr != nullptr) {

		tree_bypass(fptr->getrightchild(), xc, yc, Needed_elements, whoose_move);
		//if ...
		sf::FloatRect rect(sf::Vector2f(fptr->getthis()->getPosition().x - 40, fptr->getthis()->getPosition().y - 40), sf::Vector2f(80.f, 80.f));
		unsigned val = fptr->getthis()->getColor();
		if (Needed_elements.empty() == true && val == whoose_move &&rect.contains(xc, yc)) {
			Needed_elements.push_back(fptr);
		}
		tree_bypass(fptr->getleftchild(), xc, yc, Needed_elements, whoose_move);

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
		std::cout << ptr.get()->getthis()->getPosition().x << " , " << ptr.get()->getthis()->getPosition().y << "\n";
		//target.draw(*(ptr->getthis())); // интересно будет ли работать 
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
			mWindow.draw(*(moved_element.front()->getthis()));
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
					tree_bypass(Chesstree.getroot(), pos.x, pos.y, moved_element, Whoose_move);
					if (moved_element.empty() == false) {
						std::cout << 1 <<std::endl;
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
						moved_element.front()->getthis()->setPosition(correct_position(moved_element.front()->getthis()->getPosition().x), correct_position(moved_element.front()->getthis()->getPosition().y));
						sf::Vector2f New_position = moved_element.front()->getthis()->getPosition();
						Chesstree.ChangeNode(moved_element.front(), Previos_Position, New_position); // работает 
						//putTree(Chesstree.getroot(), 0);
						isMove = false;
						//putTree(Chesstree.getroot(), 0);
						if (moved_element.front()->getthis()->getPosition() != Previos_Position) {
							if (Whoose_move) {
								Whoose_move = 0;
							}
							else {
								Whoose_move = 1;
							}
						}
						Previos_Position = sf::Vector2f(0.f, 0.f);
						moved_element.clear();
					}
				}
			}

		}
		if (isMove == true) {
			//shape.setFillColor(sf::Color::Green);
			//pixelPos = sf::Mouse::getPosition(mWindow);//забираем коорд курсора
			//pos = mWindow.mapPixelToCoords(pixelPos);
			(moved_element.front())->getthis()->setPosition(pos.x - dX, pos.y - dY);
		}
		//this->draw();
	}
}

