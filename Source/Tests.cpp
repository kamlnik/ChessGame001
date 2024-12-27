#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <My_lib/Figure.hpp>
#include <My_lib/Pawn.hpp>
#include <My_lib/King.hpp>
#include <My_lib/Queen.hpp>
#include <My_lib/Rook.hpp>
#include <My_lib/Bishop.hpp>
#include <My_lib/Knight.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <My_lib/Kdtree.hpp>

unsigned chessboard[8][8] = { };

float Screensize = 800;


TEST_CASE(" Primitive Constructor with color and position for Pawn ") {
	Pawn test1_1(Figure::black, sf::Vector2f(0, 0), chessboard);
	REQUIRE(test1_1.getColor() == Figure::black);
	REQUIRE(test1_1.getPosition().x == 0);
	REQUIRE(test1_1.getPosition().x == 0);
	REQUIRE(test1_1.getType() == Figure::Pawn);
	REQUIRE(test1_1.all_move().empty() == true);


	Pawn test1_2(Figure::white, sf::Vector2f(100, 100), chessboard);
	REQUIRE(test1_2.getColor() == Figure::white);
	REQUIRE(test1_2.getPosition().x == 100);
	REQUIRE(test1_2.getPosition().x == 100);
	REQUIRE(test1_2.getType() == Figure::Pawn);
	REQUIRE(test1_2.all_move().empty() == true);
}


TEST_CASE(" Set position metod ") {
	Pawn test2_1(Figure::white, sf::Vector2f(100, 100), chessboard);
	test2_1.setPosition(300, 300);
	REQUIRE(test2_1.getColor() == Figure::white);
	REQUIRE(test2_1.getPosition().x == 300);
	REQUIRE(test2_1.getPosition().x == 300);
	REQUIRE(test2_1.getType() == Figure::Pawn);
	REQUIRE(test2_1.all_move().empty() == true);


	Pawn test2_2(Figure::white, sf::Vector2f(100, 100), chessboard);
	test2_2.setPosition(200, 200);
	REQUIRE(test2_2.getColor() == Figure::white);
	REQUIRE(test2_2.getPosition().x == 200);
	REQUIRE(test2_2.getPosition().x == 200);
	REQUIRE(test2_2.getType() == Figure::Pawn);
	REQUIRE(test2_2.all_move().empty() == true);
}

// other constr have the same structure
TEST_CASE(" Check Moves of Pawn ") {
	unsigned newchessboard[8][8] = {};

	Pawn test3_1(Figure::black, sf::Vector2f(150, 150), newchessboard);
	test3_1.update_move(Screensize);
	auto t = std::find(test3_1.all_move().begin(), test3_1.all_move().end(), sf::Vector2f(150, 250));
	REQUIRE(t != test3_1.all_move().end());
	t = std::find(test3_1.all_move().begin(), test3_1.all_move().end(), sf::Vector2f(150, 350));
	REQUIRE(t != test3_1.all_move().end());
	t = std::find(test3_1.all_move().begin(), test3_1.all_move().end(), sf::Vector2f(150, 450));
	REQUIRE(t == test3_1.all_move().end());

	Pawn test3_2(Figure::white, sf::Vector2f(150, 650), newchessboard);
	test3_2.update_move(Screensize);
	auto t2 = std::find(test3_2.all_move().begin(), test3_2.all_move().end(), sf::Vector2f(150, 550));
	REQUIRE(t2 != test3_2.all_move().end());
	t2 = std::find(test3_2.all_move().begin(), test3_2.all_move().end(), sf::Vector2f(150, 450));
	REQUIRE(t2 != test3_2.all_move().end());
	t2 = std::find(test3_2.all_move().begin(), test3_2.all_move().end(), sf::Vector2f(150, 350));
	REQUIRE(t2 == test3_2.all_move().end());


	Pawn test3_3(Figure::white, sf::Vector2f(50, 50), newchessboard);
	test3_3.update_move(Screensize);
	auto t3 = std::find(test3_3.all_move().begin(), test3_3.all_move().end(), sf::Vector2f(150, 550));
	REQUIRE(t3 == test3_3.all_move().end());
	t3 = std::find(test3_3.all_move().begin(), test3_3.all_move().end(), sf::Vector2f(150, 450));
	REQUIRE(t3 == test3_3.all_move().end());
	t3 = std::find(test3_3.all_move().begin(), test3_3.all_move().end(), sf::Vector2f(150, 350));
	REQUIRE(t3 == test3_3.all_move().end());
}


TEST_CASE(" Check Moves of Bishop ") {
	unsigned newchessboard[8][8] = {};

	Bishop test4_1(Figure::black, sf::Vector2f(150, 150), newchessboard);
	test4_1.update_move(Screensize);
	auto t = std::find(test4_1.all_move().begin(), test4_1.all_move().end(), sf::Vector2f(50, 250));
	REQUIRE(t != test4_1.all_move().end());
	t = std::find(test4_1.all_move().begin(), test4_1.all_move().end(), sf::Vector2f(650, 650));
	REQUIRE(t != test4_1.all_move().end());
	t = std::find(test4_1.all_move().begin(), test4_1.all_move().end(), sf::Vector2f(450, 650));
	REQUIRE(t == test4_1.all_move().end());

	Bishop test4_2(Figure::white, sf::Vector2f(150, 650), newchessboard);
	test4_2.update_move(Screensize);
	auto t2 = std::find(test4_2.all_move().begin(), test4_2.all_move().end(), sf::Vector2f(50, 750));
	REQUIRE(t2 != test4_2.all_move().end());
	t2 = std::find(test4_2.all_move().begin(), test4_2.all_move().end(), sf::Vector2f(50, 550));
	REQUIRE(t2 != test4_2.all_move().end());
	t2 = std::find(test4_2.all_move().begin(), test4_2.all_move().end(), sf::Vector2f(750, 150));
	REQUIRE(t2 == test4_2.all_move().end());


	Bishop test4_3(Figure::white, sf::Vector2f(50, 50), newchessboard);
	test4_3.update_move(Screensize);
	auto t3 = std::find(test4_3.all_move().begin(), test4_3.all_move().end(), sf::Vector2f(750, 750));
	REQUIRE(t3 != test4_3.all_move().end());
	t3 = std::find(test4_3.all_move().begin(), test4_3.all_move().end(), sf::Vector2f(350, 350));
	REQUIRE(t3 != test4_3.all_move().end());
	t3 = std::find(test4_3.all_move().begin(), test4_3.all_move().end(), sf::Vector2f(150, 350));
	REQUIRE(t3 == test4_3.all_move().end());
}


TEST_CASE(" Check Moves of Rook ") {
	unsigned newchessboard[8][8] = {};

	Rook test5_1(Figure::black, sf::Vector2f(150, 150), newchessboard);
	test5_1.update_move(Screensize);
	auto t = std::find(test5_1.all_move().begin(), test5_1.all_move().end(), sf::Vector2f(350, 150));
	REQUIRE(t != test5_1.all_move().end());
	t = std::find(test5_1.all_move().begin(), test5_1.all_move().end(), sf::Vector2f(150, 450));
	REQUIRE(t != test5_1.all_move().end());
	t = std::find(test5_1.all_move().begin(), test5_1.all_move().end(), sf::Vector2f(450, 650));
	REQUIRE(t == test5_1.all_move().end());

	Rook test5_2(Figure::white, sf::Vector2f(150, 650), newchessboard);
	test5_2.update_move(Screensize);
	auto t2 = std::find(test5_2.all_move().begin(), test5_2.all_move().end(), sf::Vector2f(150, 750));
	REQUIRE(t2 != test5_2.all_move().end());
	t2 = std::find(test5_2.all_move().begin(), test5_2.all_move().end(), sf::Vector2f(650, 650));
	REQUIRE(t2 != test5_2.all_move().end());
	t2 = std::find(test5_2.all_move().begin(), test5_2.all_move().end(), sf::Vector2f(750, 150));
	REQUIRE(t2 == test5_2.all_move().end());


	Rook test5_3(Figure::white, sf::Vector2f(50, 50), newchessboard);
	test5_3.update_move(Screensize);
	auto t3 = std::find(test5_3.all_move().begin(), test5_3.all_move().end(), sf::Vector2f(750, 50));
	REQUIRE(t3 != test5_3.all_move().end());
	t3 = std::find(test5_3.all_move().begin(), test5_3.all_move().end(), sf::Vector2f(50, 350));
	REQUIRE(t3 != test5_3.all_move().end());
	t3 = std::find(test5_3.all_move().begin(), test5_3.all_move().end(), sf::Vector2f(150, 350));
	REQUIRE(t3 == test5_3.all_move().end());
}


TEST_CASE(" Check Moves of Knight ") {
	unsigned newchessboard[8][8] = {};

	Knight test6_1(Figure::black, sf::Vector2f(150, 150), newchessboard);
	test6_1.update_move(Screensize);
	auto t = std::find(test6_1.all_move().begin(), test6_1.all_move().end(), sf::Vector2f(50, 350));
	REQUIRE(t != test6_1.all_move().end());
	t = std::find(test6_1.all_move().begin(), test6_1.all_move().end(), sf::Vector2f(250, 350));
	REQUIRE(t != test6_1.all_move().end());
	t = std::find(test6_1.all_move().begin(), test6_1.all_move().end(), sf::Vector2f(450, 650));
	REQUIRE(t == test6_1.all_move().end());

	Knight test6_2(Figure::white, sf::Vector2f(150, 650), newchessboard);
	test6_2.update_move(Screensize);
	auto t2 = std::find(test6_2.all_move().begin(), test6_2.all_move().end(), sf::Vector2f(50, 450));
	REQUIRE(t2 != test6_2.all_move().end());
	t2 = std::find(test6_2.all_move().begin(), test6_2.all_move().end(), sf::Vector2f(350, 550));
	REQUIRE(t2 != test6_2.all_move().end());
	t2 = std::find(test6_2.all_move().begin(), test6_2.all_move().end(), sf::Vector2f(750, 150));
	REQUIRE(t2 == test6_2.all_move().end());


	Knight test6_3(Figure::white, sf::Vector2f(50, 50), newchessboard);
	test6_3.update_move(Screensize);
	auto t3 = std::find(test6_3.all_move().begin(), test6_3.all_move().end(), sf::Vector2f(150, 250));
	REQUIRE(t3 != test6_3.all_move().end());
	t3 = std::find(test6_3.all_move().begin(), test6_3.all_move().end(), sf::Vector2f(250, 150));
	REQUIRE(t3 != test6_3.all_move().end());
	t3 = std::find(test6_3.all_move().begin(), test6_3.all_move().end(), sf::Vector2f(150, 350));
	REQUIRE(t3 == test6_3.all_move().end());
}


TEST_CASE(" Check Moves of King ") {
	unsigned newchessboard[8][8] = {};

	King test7_1(Figure::black, sf::Vector2f(150, 150), newchessboard);
	test7_1.update_move(Screensize);
	auto t = std::find(test7_1.all_move().begin(), test7_1.all_move().end(), sf::Vector2f(50, 150));
	REQUIRE(t != test7_1.all_move().end());
	t = std::find(test7_1.all_move().begin(), test7_1.all_move().end(), sf::Vector2f(250, 150));
	REQUIRE(t != test7_1.all_move().end());
	t = std::find(test7_1.all_move().begin(), test7_1.all_move().end(), sf::Vector2f(450, 650));
	REQUIRE(t == test7_1.all_move().end());

	King test7_2(Figure::white, sf::Vector2f(150, 650), newchessboard);
	test7_2.update_move(Screensize);
	auto t2 = std::find(test7_2.all_move().begin(), test7_2.all_move().end(), sf::Vector2f(50, 650));
	REQUIRE(t2 != test7_2.all_move().end());
	t2 = std::find(test7_2.all_move().begin(), test7_2.all_move().end(), sf::Vector2f(250, 750));
	REQUIRE(t2 != test7_2.all_move().end());
	t2 = std::find(test7_2.all_move().begin(), test7_2.all_move().end(), sf::Vector2f(750, 150));
	REQUIRE(t2 == test7_2.all_move().end());


	King test7_3(Figure::white, sf::Vector2f(50, 50), newchessboard);
	test7_3.update_move(Screensize);
	auto t3 = std::find(test7_3.all_move().begin(), test7_3.all_move().end(), sf::Vector2f(50, 150));
	REQUIRE(t3 != test7_3.all_move().end());
	t3 = std::find(test7_3.all_move().begin(), test7_3.all_move().end(), sf::Vector2f(150, 50));
	REQUIRE(t3 != test7_3.all_move().end());
	t3 = std::find(test7_3.all_move().begin(), test7_3.all_move().end(), sf::Vector2f(0, 0));
	REQUIRE(t3 == test7_3.all_move().end());
}


TEST_CASE(" Add to Kdtree ") {
	Kdtree tree8_1;
	unsigned newchessboard[8][8] = {};
	std::shared_ptr<Pawn> Pawn8_1(new Pawn(Figure::black, sf::Vector2f(150, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode8_1(new kdNode(std::move(Pawn8_1)));
	tree8_1.AddNode(kdNode8_1);
	std::shared_ptr<Pawn> Pawn8_2(new Pawn(Figure::black, sf::Vector2f(50, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode8_2(new kdNode(std::move(Pawn8_2)));
	tree8_1.AddNode(kdNode8_2);
	std::shared_ptr<Pawn> Pawn8_3(new Pawn(Figure::black, sf::Vector2f(100, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode8_3(new kdNode(std::move(Pawn8_3)));
	tree8_1.AddNode(kdNode8_3);
	std::shared_ptr<Pawn> Pawn8_4(new Pawn(Figure::black, sf::Vector2f(250, 250), newchessboard));
	std::shared_ptr<kdNode> kdNode8_4(new kdNode(std::move(Pawn8_4)));
	tree8_1.AddNode(kdNode8_4);
	REQUIRE(tree8_1.getroot()->getcoord() == true);
	REQUIRE(tree8_1.getroot()->getthis()->getPosition().x  == 150);
	REQUIRE(tree8_1.getroot()->getthis()->getPosition().y == 150);
	REQUIRE((tree8_1.getroot())->getrightchild()->getcoord() == false);
	REQUIRE(tree8_1.getroot()->getrightchild()->getthis()->getPosition().x == 250);
	REQUIRE(tree8_1.getroot()->getrightchild()->getthis()->getPosition().y == 250);
	REQUIRE((tree8_1.getroot())->getleftchild()->getcoord() == false);
	REQUIRE(tree8_1.getroot()->getleftchild()->getthis()->getPosition().x == 50);
	REQUIRE(tree8_1.getroot()->getleftchild()->getthis()->getPosition().y == 150);
	REQUIRE((tree8_1.getroot())->getleftchild()->getrightchild()->getcoord() == true);
	REQUIRE(tree8_1.getroot()->getleftchild()->getrightchild()->getthis()->getPosition().x == 100);
	REQUIRE(tree8_1.getroot()->getleftchild()->getrightchild()->getthis()->getPosition().y == 150);
}


TEST_CASE(" Delete in Kdtree ") {
	Kdtree tree9_1;
	unsigned newchessboard[8][8] = {};
	std::shared_ptr<Pawn> Pawn9_1(new Pawn(Figure::black, sf::Vector2f(150, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode9_1(new kdNode(std::move(Pawn9_1)));
	tree9_1.AddNode(kdNode9_1);
	std::shared_ptr<Pawn> Pawn9_2(new Pawn(Figure::black, sf::Vector2f(50, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode9_2(new kdNode(std::move(Pawn9_2)));
	tree9_1.AddNode(kdNode9_2);
	std::shared_ptr<Pawn> Pawn9_3(new Pawn(Figure::black, sf::Vector2f(100, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode9_3(new kdNode(std::move(Pawn9_3)));
	tree9_1.AddNode(kdNode9_3);
	std::shared_ptr<Pawn> Pawn9_4(new Pawn(Figure::black, sf::Vector2f(250, 250), newchessboard));
	std::shared_ptr<kdNode> kdNode9_4(new kdNode(std::move(Pawn9_4)));
	tree9_1.AddNode(kdNode9_4);
	tree9_1.DeleteNode(kdNode9_4);
	tree9_1.DeleteNode(kdNode9_3);
	REQUIRE(tree9_1.getroot()->getcoord() == true);
	REQUIRE(tree9_1.getroot()->getthis()->getPosition().x == 150);
	REQUIRE(tree9_1.getroot()->getthis()->getPosition().y == 150);
	REQUIRE((tree9_1.getroot())->getrightchild() == nullptr);
	REQUIRE((tree9_1.getroot())->getleftchild()->getcoord() == false);
	REQUIRE(tree9_1.getroot()->getleftchild()->getthis()->getPosition().x == 50);
	REQUIRE(tree9_1.getroot()->getleftchild()->getthis()->getPosition().y == 150);
	REQUIRE((tree9_1.getroot())->getleftchild()->getrightchild() == nullptr);
}


TEST_CASE(" Find in Kdtree ") {
	Kdtree tree10_1;
	unsigned newchessboard[8][8] = {};
	std::shared_ptr<Pawn> Pawn10_1(new Pawn(Figure::black, sf::Vector2f(150, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode10_1(new kdNode(std::move(Pawn10_1)));
	tree10_1.AddNode(kdNode10_1);
	std::shared_ptr<Pawn> Pawn10_2(new Pawn(Figure::black, sf::Vector2f(50, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode10_2(new kdNode(std::move(Pawn10_2)));
	tree10_1.AddNode(kdNode10_2);
	std::shared_ptr<Pawn> Pawn10_3(new Pawn(Figure::black, sf::Vector2f(100, 150), newchessboard));
	std::shared_ptr<kdNode> kdNode10_3(new kdNode(std::move(Pawn10_3)));
	tree10_1.AddNode(kdNode10_3);
	std::shared_ptr<Pawn> Pawn10_4(new Pawn(Figure::black, sf::Vector2f(250, 250), newchessboard));
	std::shared_ptr<kdNode> kdNode10_4(new kdNode(std::move(Pawn10_4)));
	tree10_1.AddNode(kdNode10_4);
	tree10_1.DeleteNode(kdNode10_3);
	REQUIRE(tree10_1.FindNode(150, 150) != nullptr);
	REQUIRE(tree10_1.FindNode(50, 150) != nullptr);
	REQUIRE(tree10_1.FindNode(100, 150) == nullptr);
	REQUIRE(tree10_1.FindNode(250, 250) != nullptr);
}