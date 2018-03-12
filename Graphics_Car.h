#include "Graphics_Texture.h"

class Car 
{
private:
	static SDL_mutex *gBufferLock;
	SDL_Renderer* CarRenderer;
	LTexture g_CarTexture;
	LTexture g_FloorTexture;
	float m_PosX, m_PosY;
	float m_VelX, m_VelY;
public:
	static std::vector<Car*> carDeck;

	static const int CAR_WIDTH = 20;
	static const int CAR_HEIGHT = 20;

	static const int DOT_VEL = 640;

	Car(SDL_Renderer* gRenderer, LTexture& texture, LTexture& flrTexture, int initX, int initY, int time = 10000);


	~Car();

	void move(float timeStep, int destX, int destY);

	void remove();

	void exit();

	void render();

	void renderOut();
};