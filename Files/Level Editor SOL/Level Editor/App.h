#pragma once

#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

using namespace sf;

// #  of rows
const int R = 5;
// # of blocks in a row
const int N = 8;

// # of lives
const int L = 10;


class App
{


private:
	Event event;
	View view;
	RenderWindow window;
	CircleShape ball;
	RectangleShape paddle;
	sf::RectangleShape bricks[R][N];
	RectangleShape screenFlasher;
	CircleShape lives[L];
	RectangleShape gameOverRectangle;
	RectangleShape playButton;
	RectangleShape logo;
	RectangleShape pauseRect;

	// other date members here

public:
	//start clock
	Clock clock;

	Texture brick1PNG;
	Texture brick2PNG;
	Texture brick3PNG;
	Texture brick4PNG;
	Texture brick5PNG;
	Texture ballPNG;
	Texture paddlePNG;
	Texture livesPNG;
	Texture gameOverPNG;
	Texture logoPNG;
	Texture playButtonPNG;
	Texture pausePNG;

	Font Font;
	Text scoreText;

	//SoundBuffer wallHitBuffer;
	//SoundBuffer brickDestroyBuffer;
	//SoundBuffer paddleHitBuffer;
	//SoundBuffer ballMissBuffer;
	//SoundBuffer levelUpBuffer;
	//SoundBuffer gameOverBuffer;

	//sf::Sound sound;
	

	//Changing values
	float velocity = 2;
	float xSpeed = 0;
	float ySpeed = 0;
	float currentPaddleSpeed;
	float paddleSpeed = 450;
	float currentFlashTimer;
	float flashTimer = 80;  // 100 = 1 second
	float ballStartTimer = 3;
	float currentBallStartTimer;
	bool isDead = true;
	bool flash;
	int currentFlashValue;
	int livesLeft = 3;
	bool gameOver;
	int level = 1;
	bool resetLevel;
	int blocksActive;
	int score;

	bool menu = true;
	bool pauseGame = false;
	bool levelEditor;
	float pauseTimer = false;

	int xPos;
	int yPos;

	

	//Set Values
	float brickWidth = 140.0f;
	float brickHeight = 20.0f;
	float brickGapX = 15.0f;
	float brickGapY = 10.0f;

	bool collidable[R][N];

	//sf::RectangleShape brick(sf::Vector2f(brickWidth, brickHeight));



	App(const char* title, int screenWidth, int screenHeight, int screenBpp);




	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	
	// Custom
	void Menu();
	void Death();
	void BallMovement();
	void Collision();
	void WriteToFile();
	void ReadFromFile();
	// Custom end

	void Run();
	
};



// end of app class definition