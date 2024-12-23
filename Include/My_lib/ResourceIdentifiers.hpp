#ifndef MY_LIB_RESOURCEIDENTIFIERS_HPP
#define MY_LIB_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
}

namespace Textures
{
	enum ID
	{
		wPawn,
		bPawn,
		bKing,
		wKing,
		bQueen,
		wQueen,
		bRook,
		wRook,
		bBishop,
		wBishop,
		wKnight,
		bKnight,
		Chess_board, // шахматная доска
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif