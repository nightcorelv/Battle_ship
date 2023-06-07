#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

const enum class ShipType
{
	Normal_Ship,
	Speed_Ship,
	Creators_Ship,
	None
};

const enum class TownMenu
{
	None,
	Market,
	Fight,
};

class Entity:public sf::Drawable
{
private:

	sf::Sprite sprite;
	sf::Texture* texture;
	//animation
	sf::IntRect* intrect;
	
	//ship
	sf::RectangleShape* shape;
	sf::Vertex* line;

	//reusable textures
	static sf::Texture* bulletTexture;
	static sf::Texture* explotionAnimation;
	static sf::Texture* normalShipTextures;
	static sf::Texture* speedShipTextures;
	static sf::Texture* creatorShipTextures;

	//entity type
	bool drawLine;
	bool movable;
	bool isShip;
	bool isAnimation;

protected:

	//load reusable animation
	void loadBulletTexture();
	//load reusable ship texture
	void loadShipTexture(ShipType type);

	//ship functions
	void moveSprite(float xValue, float yValue, float speed);
	void moveShip(ShipType type, float xValue, float yValue, float speed, sf::RenderWindow& window);
	void rotateTo(float angle);
	sf::Vector2f getShipPosition() const;
	void setShipPosition(float x, float y);
	void setPosition(float x, float y);
	void showShipSprite(ShipType type, int index);
	float getShipRotation() const;
	void setShipRotation(float angle);
	//draw line for ship
	void setDrawLine(bool value);

	//for animation
	void setIntRect(int top, int left);
	sf::Vector2u getAnimTextureSize() const;
	int getIntRectTop() const;
	int getIntRectLeft() const;

	//swap texture for Uibuttons
	void changeTexture(sf::Texture* texture);

public:

	void setScale(float x, float y);
	virtual void spawn(int x, int y)=0;
	sf::FloatRect getShipBounds() const;
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;

	//delete static textures
	static void deleteStaticTextures();
	
	Entity(std::string textureLoadPath, bool movable, bool isShip, bool isAnimation);
	virtual ~Entity();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

