#include "actualGame.h"

float actualGame::time;

actualGame::actualGame()
{

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
	update();
	draw();
}

void actualGame::update()
{

	gameOverBool = false;

	buttonClass::updateMousePosition();

	buttonClass::retryupdateButton(buttonClass::mousePosView);

	dx = 0; rotate = 0; delay = 0.3;


	//times = clocks.getElapsedTime();

	t = c.getElapsedTime();



	//std::cout << times.asSeconds() << std::endl;

	if (c.getElapsedTime().asSeconds() != 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			rotate = true;
		}
		c.restart();
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


	//

	if (gameOverBool == false)
	{
		for (int i = 0; i < 24; i++)
		{
			s_Vector.push_back(s);
		}



		while (windowManager::getinstance().theWindow->isOpen())
		{

			std::cout << gameOverBool << std::endl;

			//clock.restart();

			time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			std::cout << s_Vector.size() << std::endl;

			windowManager::getinstance().update();

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


			//std::cout << gameOverBool << std::endl;

			for (i = 0; i < 4; i++) //Normal Draw
			{
				s_Vector[i].setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
				s_Vector[i].setPosition(a[i].x * 18, a[i].y * 18);
				s_Vector[i].move(28, 31); //offset
				windowManager::getinstance().theWindow->draw(s_Vector[i]);
			}


			for (i = 0; i < M; i++) //Bottom draw
				for (j = 0; j < N; j++)
				{
					if (field[i][j] == 0)
					{
						continue;
					}

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
						//std::cout << "RRRRR" << std::endl;
						gameOverBool = true;
						//std::cout << gameOverBool << std::endl;
					}
				}




			//renders
			windowManager::getinstance().theWindow->draw(frame);
			windowManager::getinstance().theWindow->draw(buttonClass::retryButtonShape);
			windowManager::getinstance().theWindow->draw(buttonClass::retryButtonText);
			windowManager::getinstance().theWindow->draw(myText);

			//dispplay Screen
			windowManager::getinstance().theWindow->display();
		}
	}

	if (gameOverBool == true)
	{
		/*for (int i = 0; i < 24; i++)
		{
			s_Vector.pop_back();
		}*/

		s_Vector.erase(s_Vector.begin() + 1);

		font.loadFromFile("Fonts/ARCADECLASSIC.TTF");
		myText.setFont(font);
		myText.setString("GAME OVER");
		myText.setFillColor(sf::Color::Red);
		myText.setPosition(40, 200);

		if (s_Vector.size() <= 0)
		{
			/*std::cout << "eeeee" << std::endl;*/

			s_Vector.resize(1);

			//clocks.restart();


			buttonClass::retry(0, 0, 100, 50, font, "RETRY", sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 50, 100, 255));


			music.openFromFile("Audio/gameOver.wav");
			if (!music.Playing)
			{
				std::cout << "error at playing music" << std::endl;
			}
			else
			{
				music.play();
			}

			if (buttonClass::retryButtonShape.getGlobalBounds().contains(buttonClass::mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameOverBool = false;

				//windowManager::getinstance().addscreen(new actualGame);
			}
		}
	}
}