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
void tree_bypass(std::shared_ptr<kdNode> fptr, float xc, float yc, std::vector<std::shared_ptr<kdNode>>& Needed_elements) {
	//std::cout << 1 << std::endl;
	if (fptr != nullptr) {
		
		tree_bypass(fptr->getrightchild(), xc, yc, Needed_elements);
		//if ...
		sf::FloatRect rect(sf::Vector2f(fptr->getthis()->getPosition().x - 40, fptr->getthis()->getPosition().y - 40), sf::Vector2f(80.f,80.f));
		if (Needed_elements.empty() == true && rect.contains(xc,yc)) {
		//	std::cout << fptr->getthis()->boundingBox.left << std::endl;
			Needed_elements.push_back(fptr);
		}
		tree_bypass(fptr->getleftchild(), xc, yc, Needed_elements);

	}
	//else {
	//	std::cout << 2 << std::endl;
	//}
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
	if (Chesstree.getroot() == nullptr) {
		throw std::runtime_error("wefqw");
	}
	std::shared_ptr<kdNode> testptr = Chesstree.getroot();
	if ((Chesstree.getroot())->getrightchild() == nullptr) {
		
		throw std::runtime_error("????");
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
void World::World_processEvents() {
	bool isMove = false;//переменная для щелчка мыши по спрайту
	float dX = 0;
	float dY = 0;
	std::vector<std::shared_ptr<kdNode>> moved_element;
	while (mWindow.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);//забираем коорд курсора
		sf::Vector2f pos = mWindow.mapPixelToCoords(pixelPos);
		sf::Event event;
		//std::cout << pos.x << pos.y << std::endl;
		//std::cout << "the end " << std::endl;
		while (mWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mWindow.close();
			}
			//tree_bypass(Chesstree.getroot(), pos.x, pos.y, moved_element);
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					//pixelPos = sf::Mouse::getPosition(mWindow);
					//pos = mWindow.mapPixelToCoords(pixelPos);
					//tree_bypass(Chesstree.getroot(), pos.x, pos.y, moved_element); //  не работает
					//std::cout << pos.x << pos.y << std::endl;
					tree_bypass(Chesstree.getroot(), pos.x, pos.y, moved_element);
					if (moved_element.empty() == false) {
						dX = pos.x - (moved_element.front())->getthis()->getPosition().x;
						dY = pos.y - (moved_element.front())->getthis()->getPosition().y;
						isMove = true;
					}else {
						std::cout << "daun\n";
					}
					//if (Chess_board.getGlobalBounds().contains(pos.x, pos.y)) {
					//	dX = pos.x - Chess_board.getPosition().x;
					//	dY = pos.y - Chess_board.getPosition().y;
					//	isMove = true;
					//} 
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.key.code == sf::Mouse::Left)
					isMove = false;
				moved_element.clear();
				//shape.setFillColor(sf::Color::White);
			}

		}
		if (isMove == true) {
			//shape.setFillColor(sf::Color::Green);
			//pixelPos = sf::Mouse::getPosition(mWindow);//забираем коорд курсора
			//pos = mWindow.mapPixelToCoords(pixelPos);
			(moved_element.front())->getthis()->setPosition(pos.x - dX, pos.y - dY);
		}
		this->draw();
	}
}

