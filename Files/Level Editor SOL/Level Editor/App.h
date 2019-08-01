#pragma once

#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

using namespace sf;

// Constant ints
// #  of rows
const int R = 5;

// # of blocks in a row
const int N = 8;

// # of lives
const int L = 10;


class App{

private:
	// Default
	Event event;
	View view;
	RenderWindow window;

	// Load Shapes

	// Gameplay
	CircleShape ball;
	RectangleShape paddle;
	sf::RectangleShape bricks[R][N];
	
	// UI
	RectangleShape screenFlasher;
	CircleShape lives[L];
	RectangleShape gameOverRectangle;

	// Menu
	RectangleShape playButton;
	RectangleShape logo;
	RectangleShape pauseRect;

	// other date members here

public:
	// Start clock
	Clock clock;

	// Textures
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

	// Fonts
	Font Font;

	// Texts
	Text scoreText;

	//Changing values

	// Floats
	float velocity = 2;
	float xSpeed = 0;
	float ySpeed = 0;
	float currentPaddleSpeed;
	float paddleSpeed = 450;
	float currentFlashTimer;
	float flashTimer = 80;  // 100 = 1 second
	float ballStartTimer = 3;
	float currentBallStartTimer;
	float deltaTime;
	float pauseTimer;

	// Ints
	int currentFlashValue;
	int livesLeft = 3;
	int level = 1;
	int blocksActive;
	int score;

	// Bools
	bool isDead = true;
	bool flash = false;
	bool gameOver = false;
	bool resetLevel = false;
	bool pauseGame = false;

	// Strings
	string currentGame = "Menu";

	//Set Values

	//Floats
	float brickWidth = 140.0f;
	float brickHeight = 20.0f;
	float brickGapX = 15.0f;
	float brickGapY = 10.0f;

	//Bools
	bool collidable[R][N];


	App(const char* title, int screenWidth, int screenHeight, int screenBpp);

	// App methods

	~App();

	// Crimsion zombie
	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	
	// Custom methods
	void Menu();
	void MainGame();
	void Death();
	void BallMovement();
	void Collision();
	void WriteToFile();
	void ReadFromFile();
	void SaveMainGameplayProgress();
	// Custom end

	// Crimsion zombie
	void Run();
	
};

// end of app class definition