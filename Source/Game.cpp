#include <My_lib/Game.hpp>
#include <SFML/Window/Event.hpp>


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(800, 800), "ChessAPP", sf::Style::Close), mWorld(mWindow)
	//, mPlayer()
	//, mFont()
	//, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	//, shape(100.f)
	//,test()
{
	//shape.setFillColor(sf::Color::Blue);
//	shape.setOrigin(50.f, 50.f);
	//shape.setPosition(100.f, 100.f);
	/*sf::Texture texture;
	texture.loadFromFile("C:/Users/Kamlo/source/repos/ChessGame001/Media/Textures/wK.png");
	test.setTexture(texture);
	test.setOrigin(40.f, 40.f);
	test.setPosition(100.f, 100.f);*/
	//mFont.loadFromFile("Media/Sansation.ttf");
	//mStatisticsText.setFont(mFont);
	//mStatisticsText.setPosition(5.f, 5.f);
	//mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	//mWorld.World_processEvent();
	while (mWindow.isOpen())
	{
		mWorld.World_processEvents();
	//	render();
	}
	//mWorld.World_processEvent();
//	while (mWindow.isOpen())
//	{
		//sf::Time elapsedTime = clock.restart();
		//timeSinceLastUpdate += elapsedTime;
		//while (timeSinceLastUpdate > TimePerFrame)
	//	{
		//	timeSinceLastUpdate -= TimePerFrame;

		//	processEvents();
		//	std::cout << "daun" << std::endl;
		//	std::cout << "bro, update " << std::endl;
		//	update(TimePerFrame);
			
	//	}
		//render();
		//updateStatistics(elapsedTime);
		//render();
	//}
}

/*void Game::processEvents()
{
	bool isMove = false;//���������� ��� ������ ���� �� �������
	float dX = 0;
	float dY = 0;
	while (mWindow.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);//�������� ����� �������
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
					if (mWorld.Chess_board.getGlobalBounds().contains(pos.x, pos.y)) {
						dX = pos.x - mWorld.Chess_board.getPosition().x;
						dY = pos.y - mWorld.Chess_board.getPosition().y;
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
			pixelPos = sf::Mouse::getPosition(mWindow);//�������� ����� �������
			pos = mWindow.mapPixelToCoords(pixelPos);
			mWorld.Chess_board.setPosition(pos.x - dX, pos.y - dY);
		}
		render();
			while (mWindow.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyPressed:
					handlePlayerInput(event.key.code, true);
					break;

				case sf::Event::KeyReleased:
					handlePlayerInput(event.key.code, false);
					break;

				case sf::Event::Closed:
					mWindow.close();
					break;
				}
			}
		}
	}
}*/
/*void Game::update(sf::Time elapsedTime)
{
	mWorld.update(elapsedTime);
	//sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	mPlayer.move(movement * elapsedTime.asSeconds());
}*/

/*void Game::render()
{
	mWindow.clear();
	
	mWorld.draw();
	//mWindow.draw(shape);
	mWindow.setView(mWindow.getDefaultView());
	//mWindow.draw(mStatisticsText);
	mWindow.display();
}*/

/*void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}*/

/*void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}*/
