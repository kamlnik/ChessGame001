#include <My_lib/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>


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
	while (mWindow.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);//забираем коорд курсора
		sf::Vector2f pos = mWindow.mapPixelToCoords(pixelPos);
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mWindow.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					pixelPos = sf::Mouse::getPosition(mWindow);
					pos = mWindow.mapPixelToCoords(pixelPos);
					if (Chess_board.getGlobalBounds().contains(pos.x, pos.y)) {
						dX = pos.x - Chess_board.getPosition().x;
						dY = pos.y - Chess_board.getPosition().y;
						isMove = true;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.key.code == sf::Mouse::Left)
					isMove = false;
				//shape.setFillColor(sf::Color::White);
			}

		}
		if (isMove == true) {
			//shape.setFillColor(sf::Color::Green);
			pixelPos = sf::Mouse::getPosition(mWindow);//забираем коорд курсора
			pos = mWindow.mapPixelToCoords(pixelPos);
			Chess_board.setPosition(pos.x - dX, pos.y - dY);
		}
		this->draw();
	}
}