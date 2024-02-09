#pragma once
#include "Players.h"
class PlayerCowboy : public  Players
{
private:
    float CurrentFrame = 0;
    Clock clock;
    float time;
    float speed = 0.2;
public:
    PlayerCowboy()
    {
        texture.loadFromFile("Textures/cowboy.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(10, 0, 60, 90));
    	sprite.setOrigin(sprite.getPosition().x+sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
        float time;
    }
    
    void move() override
    {
    	time = clock.getElapsedTime().asMicroseconds();
    	clock.restart();
    	time = time / 800;
    	
        if (direction==LEFT)
		{
			CurrentFrame += 0.02 * time;
			if (CurrentFrame > 16) CurrentFrame -= 16;
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame)+10, 0, 60, 90));
			sprite.move(-speed * time, 0);
		}

		if (direction==RIGHT)
		{
			CurrentFrame += 0.02 * time;
			if (CurrentFrame > 16) CurrentFrame -= 16;
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame)+20, 85, 60, 90));
			sprite.move(speed * time, 0);
		}

		if (direction==UP) 
		{
			CurrentFrame += 0.02 * time;
			if (CurrentFrame > 16) CurrentFrame -= 16;
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame)+10, 265, 60, 90));
			sprite.move(0, -speed * time);
		}

		if (direction==DOWN)
		{
			CurrentFrame += 0.02 * time;
			if (CurrentFrame > 16) CurrentFrame -= 16;
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame)+10, 175, 60, 90));
			sprite.move(0, speed * time);
		}

		if (direction==DOWN_LEFT)
		{
			CurrentFrame += 0.02 * time;
			if (CurrentFrame > 16) CurrentFrame -= 16;
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 355, 60, 90));
			sprite.move(-speed*time, speed * time);
		}

		if (direction==DOWN_RIGHT)
		{
			CurrentFrame += 0.02 * time;
			if (CurrentFrame > 16) CurrentFrame -= 16;
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 445, 65, 90));
			sprite.move(speed * time, speed * time);
		}
    }

    void draw(RenderWindow& window)
    {
    	window.draw(sprite);
    }
    void Direction(Event& event)
    {
	    if (Keyboard::isKeyPressed(sf::Keyboard::W) || Keyboard::isKeyPressed(sf::Keyboard::Up))
	    {
	    	pressed=true;
	    	direction = UP;
	    }
    	if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left)
    		&& !(Keyboard::isKeyPressed(sf::Keyboard::S)))
    	{
    		pressed=true;
    		direction = LEFT;
    	}
    	if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Right)
			&& !(Keyboard::isKeyPressed(sf::Keyboard::S)))
    	{
    		pressed=true;
    		direction = RIGHT;
    	}
    	if (Keyboard::isKeyPressed(sf::Keyboard::S) || Keyboard::isKeyPressed(sf::Keyboard::Down)
			&& !(Keyboard::isKeyPressed(sf::Keyboard::D))
			&& !(Keyboard::isKeyPressed(sf::Keyboard::Right))
			&& !(Keyboard::isKeyPressed(sf::Keyboard::A))
			&& !(Keyboard::isKeyPressed(sf::Keyboard::Left)))
    	{
    		pressed=true;
    		direction = DOWN;
    	}
    	if((Keyboard::isKeyPressed(Keyboard::Down) && (Keyboard::isKeyPressed(Keyboard::Left)))
			|| (Keyboard::isKeyPressed(Keyboard::S) && (Keyboard::isKeyPressed(Keyboard::A))))
    	{
    		pressed=true;
    		direction = DOWN_LEFT;
    	}
    	if((Keyboard::isKeyPressed(Keyboard::Down) && (Keyboard::isKeyPressed(Keyboard::Right)))
			|| (Keyboard::isKeyPressed(Keyboard::S) && (Keyboard::isKeyPressed(Keyboard::D))))
    	{
    		pressed=true;
    		direction = DOWN_RIGHT;
    	}
    	
    }
	void checkBounds() override
    {
    	if(sprite.getPosition().x <0 ||sprite.getPosition().x+sprite.getTextureRect().getSize().x>1920)
    	{
    		direction=STOP;
    	}
    	if(sprite.getPosition().y <0 ||sprite.getPosition().y + sprite.getTextureRect().getSize().y>1080)
    	{
    		direction=STOP;
    	}
    }
	
};
