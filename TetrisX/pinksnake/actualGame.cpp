#include "actualGame.h"

float actualGame::time;

//Initialization

//sf::Sprite actualGame::s_Vector;

actualGame::actualGame()
{



	//sf::Sprite* s_frames;
	//sf::Texture* t1;




	//this->spriteList->push_back(*s);

}

actualGame::~actualGame()
{
	//spriteList.clear();
}

bool actualGame::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) //bound Limits
		{
			return 0;
		}
		else if (field[a[i].y][a[i].x]) //figures bounds
		{
			return 0;
		}

	}
	return 1;
}



void actualGame::loadFile()
{
	//startFirstFrame();
	update();
	draw();
}

void actualGame::update()
{

	buttonClass::updateMousePosition();

	buttonClass::retryupdateButton(buttonClass::mousePosView);


	//gameOverBool = false;


	dx = 0; rotate = 0; delay = 0.3;

	sf::Time t;
	sf::Clock c;

	c.getElapsedTime().asSeconds();

	std::cout << c.getElapsedTime().asSeconds() << std::endl;

	if (c.getElapsedTime().asSeconds() != 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			rotate = true;
		}
		c.restart();
		//std::cout << c.getElapsedTime().asSeconds() << std::endl;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		dx = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		dx = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		delay = 0.05;
	}

	//// <- Move -> ///
	for (i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].x += dx;
	}
	if (!check())
	{
		for (i = 0; i < 4; i++)
		{
			a[i] = b[i]; //STOP
		}
	}
	

	//////Rotate//////
	if (rotate)
	{
		Point p = a[1]; //center of rotation
		for (i = 0; i < 4; i++)
		{

			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;



		}
		if (!check()) for (i = 0; i < 4; i++) a[i] = b[i];
	}


	///////Tick//////
	if (timer > delay)
	{
		//int i;
		//i = spriteVector.size();
		for (i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }

		if (!check())
		{
			for (i = 0; i < 4; i++)
			{

				field[b[i].y][b[i].x] = colorNum;
			}

			colorNum = 1 + rand() % 7;
			int n = rand() % 7;
			for (i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}

		timer = 0;
	}



	///////check lines//////////
	int k = M - 1;
	for (i = M - 1; i > 0; i--)
	{
		int count = 0;
		for (j = 0; j < N; j++)
		{
			if (field[i][j])
			{
				count++;


			}
			field[k][j] = field[i][j];
		}
		if (count < N)
		{
			k--;

		}
	}
}

//bool actualGame::startFirstFrame()
//{
//	time = clock.getElapsedTime().asSeconds();
//	clock.restart();
//	timer += time;
//
//
//	if (timer < 3)
//	{
//		pushBackBool = true;
//	}
//	else
//	{
//		pushBackBool = false;
//	}
//	return 1;
//	
//}



void actualGame::draw()
{
	t1.loadFromFile("Images/tiles.png");
	t2.loadFromFile("Images/background.png");
	t3.loadFromFile("Images/frame01.png");

	s.setTexture(t1);
	background.setTexture(t2);
	frame.setTexture(t3);


	frame.setScale(1, 1.1);
	frame.setPosition(-40, -70);


	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);
	s_Vector.push_back(s);

	while (windowManager::getinstance().theWindow->isOpen())
	{
		spriteClear = false;


		//clock.restart();

		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		std::cout << s_Vector.size() << std::endl;

		windowManager::getinstance().update();

		//windowManager::getinstance().draw(windowManager::getinstance().theWindow);

		while (windowManager::getinstance().theWindow->pollEvent(ev))
		{


			if (ev.type == sf::Event::Closed)
			{
				windowManager::getinstance().theWindow->close();
			}



			if (!check()) for (i = 0; i < 4; i++)
			{
				a[i] = b[i];
			}
		}

		//Clear
		windowManager::getinstance().theWindow->clear(sf::Color::Cyan);
		windowManager::getinstance().theWindow->draw(background);


		//i = spriteList.size();
		//j = spriteList.size();


		for (i = 0; i < M; i++) //Bottom draw
			for (j = 0; j < N; j++)
			{
				if (field[i][j] == 0)
				{
					//s_Vector.push_back(s);
					continue;
				}

				
				//s_Vector.push_back(s);
				

				s_Vector[i].setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				s_Vector[i].setPosition(j * 18, i * 18);
				s_Vector[i].move(28, 31); //offset

				s_Vector[j].setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				s_Vector[j].setPosition(j * 18, i * 18);
				s_Vector[j].move(28, 31); //offset

				windowManager::getinstance().theWindow->draw(s_Vector[i]);
				windowManager::getinstance().theWindow->draw(s_Vector[j]);


				


				if (field[i] <= field[0])
				{
					s_Vector.erase(s_Vector.begin() + i);
					s_Vector.erase(s_Vector.begin() + j);
					//s_Vector.clear();
					font.loadFromFile("Fonts/ARCADECLASSIC.TTF");
					myText.setFont(font);
					myText.setString("GAME OVER");
					myText.setFillColor(sf::Color::Red);
					myText.setPosition(40, 200);

					music.openFromFile("Audio/gameOver.wav");
					music.play();

					buttonClass::retry(0, 0, 100, 50, font, "RETRY", sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 50, 100, 255));



					//std::cout << spriteList[] << std::endl;
					if (buttonClass::retryButtonShape.getGlobalBounds().contains(buttonClass::mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{

						//std::cout << "Retry Button has been pressed- now the level should restart" << std::endl;

						//spriteList[1] = spriteList[0];
						spriteClear = true;

					}
					if (spriteClear == true) //START a true boolean
					{
						
						s_Vector.erase(s_Vector.begin() + i);
						s_Vector.erase(s_Vector.begin() + j);

					}

				}
			}

		


		for (i = 0; i < 4; i++) //Normal Draw
		{

			

			
			
			s_Vector[i].setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s_Vector[i].setPosition(a[i].x * 18, a[i].y * 18);
			s_Vector[i].move(28, 31); //offset
			windowManager::getinstance().theWindow->draw(s_Vector[i]);

		}
		//

		//windowManager::getinstance().theWindow->draw(s);
		windowManager::getinstance().theWindow->draw(frame);
		windowManager::getinstance().theWindow->draw(buttonClass::retryButtonShape);
		windowManager::getinstance().theWindow->draw(buttonClass::retryButtonText);
		//windowManager::getinstance().theWindow->draw(myText);
		windowManager::getinstance().theWindow->draw(myText);

		//dispplay Screen
		windowManager::getinstance().theWindow->display();

		//print
		//std::cout << "We are in the ACTUAL_GAME" << std::endl;
	}
}
