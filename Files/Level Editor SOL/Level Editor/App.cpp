#include "App.h"
#include <Windows.h>
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include "SFML/Audio.hpp"
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;

//constructor
App::App(const char* title, int screenWidth, int screenHeight, int screenBpp)
{
	window.create(VideoMode(screenWidth, screenHeight, screenBpp), title);

	//window.setFramerateLimit(60);
	view = window.getDefaultView();
}

//destructor
App::~App()
{
	//release memory
}

bool App::Init()
{	
	currentBallStartTimer = ballStartTimer;

	/*
	if (!Font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	scoreText.setFont(Font);
	*/
	scoreText.setPosition(Vector2f(100, 100));
	scoreText.setCharacterSize(60);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setString("Score");

	playButton.setSize(Vector2f(350, 100));
	playButton.setPosition(Vector2f(window.getSize().x / 2 - playButton.getSize().x / 2, window.getSize().y / 2));

	logo.setSize(Vector2f(600, 200));
	logo.setPosition(Vector2f(window.getSize().x / 2 - logo.getSize().x / 2, window.getSize().y / 10));

	if (!playButtonPNG.loadFromFile("playButton.png"))
	{
		//error
	}

	playButton.setTexture(&playButtonPNG);
	playButton.setTextureRect(sf::IntRect(1, 1, 350, 100));

	if (!logoPNG.loadFromFile("logo.png"))
	{
		//error
	}

	logo.setTexture(&logoPNG);
	logo.setTextureRect(sf::IntRect(1, 1, 600, 200));

	/*
	//sound buffer
	if (!brickDestroyBuffer.loadFromFile("brickDestroyBuffer.wav"))
	{
		return -1;
	}

	if (!paddleHitBuffer.loadFromFile("paddleHitBuffer.wav"))
	{
		return -1;
	}

	if (!wallHitBuffer.loadFromFile("wallHitBuffer.wav"))
	{
		return -1;
	}

	if (!ballMissBuffer.loadFromFile("ballMissBuffer.wav"))
	{
		return -1;
	}

	if (!levelUpBuffer.loadFromFile("levelUpBuffer.wav"))
	{
		return -1;
	}

	if (!gameOverBuffer.loadFromFile("gameOverBuffer.wav"))
	{
		return -1;
	}
	*/

	/*
	Set and play sound

	sound.setBuffer(wallHitBuffer);
	sound.play();
	*/

	pauseRect.setPosition(Vector2f(30, 30));
	pauseRect.setSize(Vector2f(100, 100));

	if (!pausePNG.loadFromFile("pause.png"))
	{
		//error
	}

	pauseRect.setTexture(&pausePNG);
	pauseRect.setTextureRect(sf::IntRect(1, 1, 100, 100));
	
	srand(time(NULL));;

	int sign;
	sign = 2 * (rand() % 2) - 1;

	/*
	//set ball direction
	xSpeed = sign * (rand() % 100 + 50);
	ySpeed = -100;
	*/

	gameOverRectangle.setSize(Vector2f(708, 271));
	gameOverRectangle.setPosition(window.getSize().x / 2 - gameOverRectangle.getSize().x / 2, window.getSize().y / 3);

	//lives
	livesLeft = 1;

	for (int i = 0; i < L; ++i)
	{
		lives[i].setPosition(window.getSize().x / 20 + 28 * i, window.getSize().y - window.getSize().y / 14);
		lives[i].setFillColor(Color(255, 20, 20, 255));
		lives[i].setRadius(15);
	}

	screenFlasher.setFillColor(Color (255, 255, 255, 0));
	screenFlasher.setPosition(0, 0);
	screenFlasher.setSize(Vector2f(window.getSize().x, window.getSize().y));

	ball.setRadius(20);
	ball.setPosition(window.getSize().x / 2.0f - ball.getRadius(), window.getSize().y * 0.65);
	//ball.setFillColor(Color(150, 150, 150, 255));
	
	// Load Image files

	if (!brick1PNG.loadFromFile("brick1.png"))
	{
		//error
	}

	if (!brick2PNG.loadFromFile("brick2.png"))
	{
		//error
	}

	if (!brick3PNG.loadFromFile("brick3.png"))
	{
		//error
	}

	if (!brick4PNG.loadFromFile("brick4.png"))
	{
		//error
	}

	if (!brick5PNG.loadFromFile("brick5.png"))
	{
		//error
	}

	if (!paddlePNG.loadFromFile("paddle.png"))
	{
		//error
	}

	if (!livesPNG.loadFromFile("lives.png"))
	{
		//error
	}

	if (!ballPNG.loadFromFile("ball.png"))
	{
		//error
	}

	if (!gameOverPNG.loadFromFile("gameover.png"))
	{
		//error
	}


	ball.setTexture(&ballPNG);
	ball.setTextureRect(sf::IntRect(1, 1, 41, 41));

	gameOverRectangle.setTexture(&gameOverPNG);
	gameOverRectangle.setTextureRect(sf::IntRect(0, 0, 708, 271));

	for (int i = 0; i < L; ++i)
	{
		lives[i].setTexture(&livesPNG);
		lives[i].setTextureRect(sf::IntRect(0, 0, 20, 20));
	}
	

	paddle.setSize(Vector2f(200, 20));
	paddle.setPosition(window.getSize().x / 2.0f - paddle.getSize().x / 2.0f, window.getSize().y - 80.0f);
	paddle.setTexture(&paddlePNG);
	paddle.setTextureRect(sf::IntRect(0, 0, 200, 20));
	//paddle.setFillColor(Color(50, 50, 255, 255));

	//set windowBuffer 
	float windowBuffer = (window.getSize().x - N * brickWidth - (N - 1) * brickGapX) / 2;

	//set size of bricks
	//line
	for (int i = 0; i < R; ++i)
	{
		//rows
		for (int j = 0; j < N; ++j)
		{
			bricks[i][j].setSize(sf::Vector2f(1 * brickWidth, 1 * brickHeight));
			bricks[i][j].setPosition(windowBuffer + j * (brickWidth + brickGapX), 80 + i * (brickHeight + brickGapY));

			if (i < level)
			{
				collidable[i][j] = true;
			}
			
			if (i == 0)
			{
				bricks[i][j].setTexture(&brick1PNG);
				bricks[i][j].setTextureRect(sf::IntRect(1, 0, bricks[i][j].getSize().x, bricks[i][j].getSize().y));
			}
			if (i == 1)
			{
				bricks[i][j].setTexture(&brick2PNG);
				bricks[i][j].setTextureRect(sf::IntRect(1, 0, bricks[i][j].getSize().x, bricks[i][j].getSize().y));
			}
			if (i == 2)
			{
				bricks[i][j].setTexture(&brick3PNG);
				bricks[i][j].setTextureRect(sf::IntRect(1, 0, bricks[i][j].getSize().x, bricks[i][j].getSize().y));
			}
			if (i == 3)
			{
				bricks[i][j].setTexture(&brick4PNG);
				bricks[i][j].setTextureRect(sf::IntRect(1, 0, bricks[i][j].getSize().x, bricks[i][j].getSize().y));
			}
			if (i >= 4)
			{
				bricks[i][j].setTexture(&brick5PNG);
				bricks[i][j].setTextureRect(sf::IntRect(1, 0, bricks[i][j].getSize().x, bricks[i][j].getSize().y));
			}
			

		}
	}

	//initalise App date members
	return true;
}


void App::Update()
{
	// compute deltaTime
	// start of consecutive frames
	float deltaTime = clock.restart().asSeconds();

	//update

	if (pauseGame == false)
	{
		

		

		// float paddlePosition = paddle.getPoint;



		// MOVE PADDLE
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (paddle.getPosition().x < window.getSize().x - paddle.getSize().x)
			{
				currentPaddleSpeed = paddleSpeed;
			}
			else
			{
				currentPaddleSpeed = 0;
			}

		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{

			if (paddle.getPosition().x > 0)
			{
				currentPaddleSpeed = paddleSpeed * -1;
			}
			else
			{
				currentPaddleSpeed = 0;
			}
		}
		else
		{
			currentPaddleSpeed = 0;
		}

		paddle.move(currentPaddleSpeed * deltaTime, 0.0f);



		// ball movement
		if (isDead == false)
		{
			ball.move(xSpeed * deltaTime * velocity, ySpeed * deltaTime * velocity);
		}


		// COLLISION


		// Paddle collision
		if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
		{
			// testing collision side

			// ball x position greater
			if (ball.getPosition().x > paddle.getPosition().x)
			{
				// ball y position lower
				if (ball.getPosition().y < paddle.getPosition().y)
				{
					// ball y position lower than brick width
					if (ball.getPosition().y < paddle.getPosition().y + paddle.getSize().y - 2)
					{
						// Bottom side
						// Test for movement
						if (currentPaddleSpeed > 0)
						{
							if (xSpeed < 0)
							{
								ySpeed = -ySpeed;
								xSpeed = -xSpeed;
							}
							else
							{
								ySpeed = -ySpeed;
							}
						}
						else if (currentPaddleSpeed < 0)
						{
							if (xSpeed > 0)
							{
								ySpeed = -ySpeed;
								xSpeed = -xSpeed;
							}
							else
							{
								ySpeed = -ySpeed;
							}
						}
						else
						{
							// change speed and direction of ball
							ySpeed = -ySpeed;
						}

					}
					else
					{
						// Right side
						// Test for movement
						if (currentPaddleSpeed != 0)
						{
							ball.setPosition(ball.getPosition().x + (paddleSpeed * deltaTime * velocity), ball.getPosition().y);
							// change speed and direction of ball
							xSpeed = -xSpeed;
							ySpeed = -ySpeed;
						}
						else
						{
							// change speed and direction of ball
							xSpeed = -xSpeed;
							ySpeed = -ySpeed;
						}


					}
				}
				else
				{
					// Top side
					// Test for movement
					if (currentPaddleSpeed > 0)
					{
						if (xSpeed < 0)
						{
							ySpeed = -ySpeed;
							xSpeed = -xSpeed;
						}
						else
						{
							ySpeed = -ySpeed;
						}
					}
					else if (currentPaddleSpeed < 0)
					{
						if (xSpeed > 0)
						{
							ySpeed = -ySpeed;
							xSpeed = -xSpeed;
						}
						else
						{
							ySpeed = -ySpeed;
						}
					}
					else
					{
						// change speed and direction of ball
						ySpeed = -ySpeed;
					}

				}
			}
			else
			{
				// Left side
				// Test for movement
				if (currentPaddleSpeed != 0)
				{
					ball.setPosition(ball.getPosition().x - (paddleSpeed * deltaTime * velocity), ball.getPosition().y);
					// change speed and direction of ball
					xSpeed = -xSpeed;
					ySpeed = -ySpeed;
				}
				else
				{
					// change speed and direction of ball
					xSpeed = -xSpeed;
					ySpeed = -ySpeed;
				}

			}
			//Setand play sound

			//sound.setBuffer(paddleHitBuffer);
			//sound.play();
		}

		//brick collision
		for (int i = 0; i < R; ++i)
		{
			//rows
			for (int j = 0; j < N; ++j)
			{
				if (ball.getGlobalBounds().intersects(bricks[i][j].getGlobalBounds()) && collidable[i][j] == true)
				{
					// test collision	
					// ball x position greater
					if (ball.getPosition().x > bricks[i][j].getPosition().x)
					{
						// ball y position lower
						if (ball.getPosition().y < bricks[i][j].getPosition().y)
						{
							// ball y position lower than brick width
							if (ball.getPosition().y < bricks[i][j].getPosition().y + bricks[i][j].getSize().y - 2)
							{
								// Bottom side

								// change speed and direction of ball
								ySpeed = -ySpeed;
								// destroy brick
								collidable[i][j] = false;
							}
							else
							{
								// Right side

								// change speed and direction of ball
								xSpeed = -xSpeed;
								// destroy brick
								collidable[i][j] = false;
							}
						}
						else
						{
							// Top side

							// change speed and direction of ball
							ySpeed = -ySpeed;
							// destroy brick
							collidable[i][j] = false;
						}
					}
					else
					{
						// Left side

						// change speed and direction of ball
						xSpeed = -xSpeed;
						// destroy brick
						collidable[i][j] = false;
					}

					/*
					// change speed and direction of ball
					ySpeed = -ySpeed;
					// destroy brick
					collidable[i][j] = false;
					*/

					//Setand play sound

					//sound.setBuffer(brickDestroyBuffer);
					//sound.play();
				}
			}
		}

		// x collision
		// right
		if (ball.getPosition().x > window.getSize().x - ball.getRadius() * 2)
		{
			// rest position
			ball.setPosition(window.getSize().x - ball.getRadius() * 2, ball.getPosition().y);
			// reverse speed
			xSpeed = -xSpeed;
			// increase velocity
			velocity = velocity + 0.05;
		}
		// left
		if (ball.getPosition().x < 0)
		{
			// rest position
			ball.setPosition(0, ball.getPosition().y);
			// reverse speed
			xSpeed = -xSpeed;
			// increase velocity
			velocity = velocity + 0.05;
		}

		// y collision

			// top
		if (ball.getPosition().y < 0)
		{
			// rest position
			ball.setPosition(ball.getPosition().x, 0);
			// reverse speed
			ySpeed = -ySpeed;
			// increase velocity
			velocity = velocity + 0.05;
		}

		// bottom
		if (ball.getPosition().y > window.getSize().y + 40)
		{
			if (isDead == false)
			{
				if (livesLeft > 1)
				{
					isDead = true;
					currentBallStartTimer = ballStartTimer;
					ball.setPosition(window.getSize().x / 2.0f - ball.getRadius(), window.getSize().y * 0.65);
					flash = true;
					currentFlashTimer = 255;
					screenFlasher.setFillColor(Color(255, 10, 10, 0));
					livesLeft -= 1;
				}
				else
				{
					gameOver = true;
					isDead = true;
					currentBallStartTimer = ballStartTimer;
					ball.setPosition(-100, -100);
					flash = true;
					currentFlashTimer = 255;
					screenFlasher.setFillColor(Color(255, 10, 10, 0));
					livesLeft -= 1;
				}
			}
		}

		//screen flasher timer
		if (flash == true)
		{
			flash = false;
		}

		if (currentFlashTimer > 0)
		{
			currentFlashTimer -= deltaTime * 100;
			screenFlasher.setFillColor(Color(screenFlasher.getFillColor().r, screenFlasher.getFillColor().g, screenFlasher.getFillColor().b, 255 * (currentFlashTimer / 255)));
		}

		if (currentFlashTimer < 0)
		{
			screenFlasher.setFillColor(Color(screenFlasher.getFillColor().r, screenFlasher.getFillColor().g, screenFlasher.getFillColor().b, 0));
		}



		// Ball respawn
		if (gameOver == false)
		{
			if (isDead == true)
			{

				if (currentBallStartTimer <= 0)
				{
					int sign;
					sign = 2 * (rand() % 2) - 1;

					//set ball direction
					xSpeed = sign * (rand() % 100 + 50);
					ySpeed = -100;

					velocity = 2;
					ball.setPosition(window.getSize().x / 2.0f - ball.getRadius(), window.getSize().y * 0.65);
					isDead = false;

				}

				currentBallStartTimer -= deltaTime;
			}
		}

		if (gameOver == true)
		{
			xSpeed = 0;
			ySpeed = 0;

			ball.setPosition(-300, -300);

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				gameOver = false;
				livesLeft = 3;
				currentBallStartTimer = ballStartTimer;
				ball.setPosition(window.getSize().x / 2.0f - ball.getRadius(), window.getSize().y * 0.65);
				level = 1;
				

				for (int i = 0; i < R; ++i)
				{
					//rows
					for (int j = 0; j < N; ++j)
					{
						if (i < level)
						{
							collidable[i][j] = true;
						}
						else
						{
							collidable[i][j] = false;
						}
						
					}
				}
			}
		}
		
		blocksActive = 0;

		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (collidable[i][j] == true)
				{
					++blocksActive;
				}
			}
		}

		if (blocksActive == 0)
		{
			if (level >= 5)
			{
				gameOver = true;
			}
			else
			{
				resetLevel == true;
				ball.setPosition(window.getSize().x / 2.0f - ball.getRadius(), window.getSize().y * 0.65);
				++level;
				++livesLeft;
				currentBallStartTimer = ballStartTimer;
				isDead = true;

				for (int i = 0; i < level; ++i)
				{
					//rows
					for (int j = 0; j < N; ++j)
					{
						collidable[i][j] = true;
					}
				}
			}
		}

		/*
		if (resetLevel == true)
		{
			+livesLeft;
			currentBallStartTimer = ballStartTimer;
			ball.setPosition(window.getSize().x / 2.0f - ball.getRadius(), window.getSize().y * 0.65);

			for (int i = 0; i < R; ++i)
			{
				//rows
				for (int j = 0; j < N; ++j)
				{
					collidable[i][j] = true;
				}
			}
		}
		*/
	}
	scoreText.setString(to_string(score));

	if (menu == true)
	{
		gameOver == true;

		//Check mouse
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Vector2i localPosition = Mouse::getPosition(window);

			if (playButton.getGlobalBounds().contains(localPosition.x, localPosition.y))
			{
			menu = false;
			gameOver = false;
			livesLeft = 3;
			currentBallStartTimer = ballStartTimer;
			ball.setPosition(window.getSize().x / 2.0f - ball.getRadius(), window.getSize().y * 0.65);
			level = 1;

			for (int i = 0; i < level; ++i)
			{
				//rows
				for (int j = 0; j < N; ++j)
				{
					collidable[i][j] = true;
				}
			}
			}
				
		}
	}
	else
	{
		pauseTimer -= deltaTime;

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			
			if (pauseTimer <= 0)
			{

				pauseGame = !pauseGame;
				pauseTimer = 0.3;
			}
			
		}
	}
	
	//srand(time(NULL))
	// Write bricks position to file
	if (Keyboard::isKeyPressed(Keyboard::O))
	{
		ofstream myfile;

		// Open file
		myfile.open("saveGame.txt");

		// Write to file

		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (collidable[i][j] == true)
				{
					myfile << bricks[i][j].getPosition().x << "\t" << bricks[i][j].getPosition().y << endl;
				}
			}
		}

		// Close file
		myfile.close();

		cout << "Written to file" << endl;
	}


	// Read/Input from file

	if (Keyboard::isKeyPressed(Keyboard::I))
	{
		int x, y;

		ifstream myfile("example.txt");

		if (myfile.is_open())
		{
			// check for end of file
			while (!myfile.eof())
			{
				myfile >> x >> y;

				cout << x << "\t" << y << endl;
			}

			myfile.close();
		}

		else cout << "Unable to open file";

		cout << "Read from file" << endl;

	}
	
}

void App::Menu()
{
	cout << "This is working" << endl;
}

void App::Death()
{
}

void App::BallMovement()
{
}

void App::Collision()
{
	cout << "Collision running" << endl;
}

void App::WriteToFile()
{
	//ofstream myfile;

	// Open file
	//myfile.open("example.txt");

	// Write to file
	//myfile << "Writing this to a file.\n";

	// Close file
	//myfile.close();
}

void App::ReadFromFile()
{
	/*
	int x, y;

	ifstream myfile("example.txt");

	if (myfile.is_open())
	{
		// check for end of file
		while (!myfile.eof())
		{
			myfile >> x >> y;

			cout << x << "\t" << y << endl;
		}

		myfile.close();
	}

	else cout << "Unable to open file";
	*/
	}



void App::Draw()
{
	window.clear();
	window.setView(view);

	// draw
	if (menu == true)
	{
		window.draw(playButton);
		window.draw(logo);
	}
	else
	{
		if (gameOver == false)
		{
			window.draw(ball);
			window.draw(paddle);
		}

		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (collidable[i][j] == true)
				{
					window.draw(bricks[i][j]);
				}
			}
		}

		for (int i = 0; i < livesLeft; ++i)
		{
			window.draw(lives[i]);
		}

		if (gameOver == true)
		{
			window.draw(gameOverRectangle);
		}

		if (pauseGame == true)
		{
			window.draw(pauseRect);
		}

		window.draw(scoreText);

		window.draw(screenFlasher);
	}

	// last to display
	window.display();
}



void App::HandleEvents()
{
	if (event.type == Event::Closed)
		window.close();


	//Check mouse position
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Vector2i localPosition = Mouse::getPosition(window);


		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (bricks[i][j].getGlobalBounds().contains(localPosition.x, localPosition.y))
				{
					collidable[i][j] = !collidable[i][j];

					/*
					if (collidable[i][j] == true)
					{
						collidable[i][j] = false;
					}
					else
					{
						collidable[i][j] = true;
					}
					*/
				}
			}
		}


	}

	//other keyboard, mouse evenets
}

void App::Run()
{
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			HandleEvents();
		}
		Update();
		Draw();
	}
}

//end of App method definitons