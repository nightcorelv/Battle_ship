#include "Entity.h"

void Entity::deleteStaticTextures()
{
	if (bulletTexture != nullptr)
	{
		delete bulletTexture;
	}
	if (explotionAnimation != nullptr)
	{
		delete explotionAnimation;
	}
	if (normalShipTextures != nullptr)
	{
		delete[] normalShipTextures;
	}
	if (speedShipTextures != nullptr)
	{
		delete[] speedShipTextures;
	}
	if (creatorShipTextures != nullptr)
	{
		delete[] creatorShipTextures;
	}
}

void Entity::setScale(float x, float y)
{
    sprite.scale(x, y);
}

void Entity::setDrawLine(bool value)
{
    drawLine = value;
}

sf::Vector2f Entity::getShipPosition() const
{
	return shape->getPosition();
}

void Entity::loadShipTexture(ShipType type)
{

	std::string path;
	//load 32 direction
	for (int i = 0; i < 32; i++)
	{
		switch (i)
		{
		case 0:
			path = "right";
			break;
		case 1:
			path = "32downrightup";
			break;
		case 2:
			path = "downmidright16";
			break;
		case 3:
			path = "32downrightmidup";
			break;
		case 4:
			path = "downright";
			break;
		case 5:
			path = "32downrightmiddown";
			break;
		case 6:
			path = "downright16";
			break;
		case 7:
			path = "32downright";
			break;
		case 8:
			path = "down";
			break;
		case 9:
			path = "32downleft";
			break;
		case 10:
			path = "downleft16";
			break;
		case 11:
			path = "32downleftmiddown";
			break;
		case 12:
			path = "downleft";
			break;
		case 13:
			path = "32downleftmidup";
			break;
		case 14:
			path = "downmidleft16";
			break;
		case 15:
			path = "32downleftup";
			break;
		case 16:
			path = "left";
			break;
		case 17:
			path = "32upleft";
			break;
		case 18:
			path = "upmidleft16";
			break;
		case 19:
			path = "32upleftmiddown";
			break;
		case 20:
			path = "upleft";
			break;
		case 21:
			path = "32upleftmidup";
			break;
		case 22:
			path = "upleft16";
			break;
		case 23:
			path = "32upleftup";
			break;
		case 24:
			path = "up";
			break;
		case 25:
			path = "32uprightup";
			break;
		case 26:
			path = "upright16";
			break;
		case 27:
			path = "32uprightmidup";
			break;
		case 28:
			path = "upright";
			break;
		case 29:
			path = "32uprightmiddown";
			break;
		case 30:
			path = "upmidright16";
			break;
		case 31:
			path = "32upright";
			break;
		}

		if (type == ShipType::Normal_Ship)
		{
			path = "../Images/Normal_Ship/" + path + "/000.png";
			normalShipTextures[i].loadFromFile(path);

		}
		else if (type == ShipType::Speed_Ship)
		{
			path = "../Images/Speed_Ship/" + path + "/000.png";
			speedShipTextures[i].loadFromFile(path);
		}
		else
		{
			path = "../Images/Creators_Ship/" + path + "/000.png";
			creatorShipTextures[i].loadFromFile(path);
		}
	}
}

void Entity::showShipSprite(ShipType type, int index)
{
	if (type == ShipType::Normal_Ship)
	{
		sprite.setTexture(normalShipTextures[index]);
	}
	else if (type == ShipType::Speed_Ship)
	{
		sprite.setTexture(speedShipTextures[index]);
	}
	else
	{
		sprite.setTexture(creatorShipTextures[index]);
	}
	sprite.setScale(0.5, 0.5);
	sf::Vector2f size = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	sprite.setOrigin(size.x * 0.5, size.y * 0.5);
}

sf::FloatRect Entity::getShipBounds() const
{
    return shape->getGlobalBounds();
}

void Entity::moveShip(ShipType type, float xValue, float yValue, float speed, sf::RenderWindow& window)
{
	shape->move(xValue * speed, yValue * speed);

	if (type == ShipType::Normal_Ship)
	{
		sprite.setPosition(shape->getPosition().x - 30, shape->getPosition().y - 30);
	}
	else if (type == ShipType::Speed_Ship)
	{
		sprite.setPosition(shape->getPosition().x - 30, shape->getPosition().y - 30);
	}
	else
	{
		sprite.setPosition(shape->getPosition().x - 40, shape->getPosition().y - 50);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && drawLine)
	{
		if (line == nullptr)
		{
			line = new sf::Vertex[2]{ sf::Vertex(sf::Vector2f(0, 0)),sf::Vertex(sf::Vector2f(0, 0)) };
		}
		line[0].position = sf::Vector2f(shape->getPosition().x, shape->getPosition().y);
		line[1].position = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	}
}

void Entity::moveSprite(float xValue, float yValue, float speed)
{
    sprite.move(xValue * speed, yValue * speed);
}

void Entity::loadBulletTexture()
{
	sprite.setTexture(*bulletTexture);
}

void Entity::rotateTo(float angle)
{
    shape->rotate(angle);
}

sf::FloatRect Entity::getBounds() const
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Entity::getPosition() const
{
    return sprite.getPosition();
}

void Entity::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Entity::changeTexture(sf::Texture* texture)
{
	sprite.setTexture(*texture);
}

void Entity::setShipPosition(float x, float y)
{
	shape->setPosition(x, y);
}

float Entity::getShipRotation() const
{
    return shape->getRotation();
}

void Entity::setShipRotation(float angle)
{
    shape->setRotation(angle);
}

sf::Vector2u Entity::getAnimTextureSize() const
{
	return explotionAnimation->getSize();
}

void Entity::setIntRect(int top, int left)
{
	intrect->top = top;
	intrect->left = left;
	sprite.setTextureRect(*intrect);
}

int Entity::getIntRectTop() const
{
	return intrect->top;
}

int Entity::getIntRectLeft() const
{
	return intrect->left;
}

sf::Texture* Entity::bulletTexture;
sf::Texture* Entity::explotionAnimation;
sf::Texture* Entity::normalShipTextures;
sf::Texture* Entity::speedShipTextures;
sf::Texture* Entity::creatorShipTextures;

Entity::Entity(std::string textureLoadPath, bool movable, bool isShip, bool isAnimation)
	:movable(movable),
	isShip(isShip),
	drawLine(false),
	isAnimation(isAnimation),
	shape(nullptr),
	texture(nullptr),
	intrect(nullptr),
	line(nullptr)
{
    if (isShip)
    {
		if (shape == nullptr)
		{
			shape = new sf::RectangleShape;
		}
        shape->setFillColor(sf::Color::Cyan);
        sf::Vector2f size = sf::Vector2f(70, 20);
        shape->setSize(size);
        shape->setOrigin(size.x * 0.5, size.y * 0.5);
		if (normalShipTextures == nullptr)
		{
			normalShipTextures = new sf::Texture[32];
			loadShipTexture(ShipType::Normal_Ship);
		}
		if (speedShipTextures == nullptr)
		{
			speedShipTextures = new sf::Texture[32];
			loadShipTexture(ShipType::Speed_Ship);
		}
		if (creatorShipTextures == nullptr)
		{
			creatorShipTextures = new sf::Texture[32];
			loadShipTexture(ShipType::Creators_Ship);
		}
		if (bulletTexture == nullptr)
		{
			bulletTexture = new sf::Texture;
			bulletTexture->loadFromFile("../Images/Bullet/000.png");
		}
		if (explotionAnimation == nullptr)
		{
			explotionAnimation = new sf::Texture;
			explotionAnimation->loadFromFile("../Images/Boom/000.png");
		}
    }
	else if (isAnimation)
	{
		if (explotionAnimation == nullptr)
		{
			explotionAnimation = new sf::Texture;
			explotionAnimation->loadFromFile("../Images/Boom/000.png");
		}
		sprite.setTexture(*explotionAnimation);
		if (intrect == nullptr)
		{
			intrect = new sf::IntRect(0, 0, explotionAnimation->getSize().x / 5, explotionAnimation->getSize().y / 7);
		}
		sprite.setTextureRect(*intrect);
		sprite.setOrigin(sprite.getGlobalBounds().width * 0.5, sprite.getGlobalBounds().height * 0.5);
	}
    else if (textureLoadPath != "")
    {
		if (texture == nullptr)
		{
			texture = new sf::Texture;
		}
		texture->loadFromFile(textureLoadPath);
        sprite.setTexture(*texture);
        if (movable)
        {
            sprite.setOrigin(sprite.getGlobalBounds().width * 0.5, sprite.getGlobalBounds().height * 0.5);
        }
    }

}

Entity::~Entity()
{
	if (texture != nullptr)
	{
		delete texture;
	}
	if (shape != nullptr)
	{
		delete shape;
	}
	if (line != nullptr)
	{
		delete[] line;
	}
	if (intrect != nullptr)
	{
		delete intrect;
	}
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isShip)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && drawLine)
        {
            target.draw(line, 2, sf::Lines);
        }
    }
    target.draw(sprite);

}
