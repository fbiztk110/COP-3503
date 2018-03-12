#include "Graphics_Car.h"

SDL_mutex* Car::gBufferLock = SDL_CreateMutex();
std::vector<Car*> Car::carDeck = {};

Car::Car(SDL_Renderer* gRenderer, LTexture& texture, LTexture& flrTexture, int initX, int initY, int time)
{
	//Initialize the position
	m_PosX = initX;
	m_PosY = initY;

	//Initialize the velocity
	m_VelX = 0;
	m_VelY = 0;

	CarRenderer = gRenderer;
	g_CarTexture = texture;
	g_FloorTexture = flrTexture;

	//g_CarTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	//SDL_SetTextureAlphaMod(g_CarTexture.getTexture(), 255);
}

Car::~Car()
{
	remove();
}

void Car::exit()
{
	//Lock
	SDL_LockMutex(gBufferLock);
	int i = 0;
	for (i = 0; i < carDeck.size(); i++)
	if (carDeck.at(i) == (this))
	{
		carDeck.at(i)->remove();
		carDeck.erase(carDeck.begin() + i);
	}

	//Unlock
	SDL_UnlockMutex(gBufferLock);
	
	printf("\nExit successful.");
}

void Car::remove()
{
	renderOut();
	m_PosX = -40;
	m_PosY = -40;
	//SDL_SetTextureAlphaMod(g_CarTexture.getTexture(), 0);
	
	//g_CarTexture = nullptr;
	
}

void Car::move(float timeStep, int destX, int destY)
{
	while ((int)m_PosX != destX && (int)m_PosY != destY)
	{

		//Move the dot left or right
		m_PosX += m_VelX * timeStep;

		//If the dot went too far to the left or right
		if (m_PosX < 0)
		{
			m_PosX = 0;
		}
		else if (m_PosX > SCREEN_WIDTH - CAR_WIDTH)
		{
			m_PosX = SCREEN_WIDTH - CAR_WIDTH;
		}

		//Move the dot up or down
		m_PosY += m_VelY * timeStep;

		//If the dot went too far up or down
		if (m_PosY < 0)
		{
			m_PosY = 0;
		}
		else if (m_PosY > SCREEN_HEIGHT - CAR_HEIGHT)
		{
			m_PosY = SCREEN_HEIGHT - CAR_HEIGHT;
		}
	}
}

 
//Rendered again, does it eliminate original texture?
void Car::render()
{
	//Render Car's new position
	g_CarTexture.render((int)m_PosX, (int)m_PosY, CarRenderer);
	SDL_RenderPresent(CarRenderer);
}

//Create a Alpha mask to render out old car texture;

void Car::renderOut()
{
	//g_CarTexture.render(0, 0, CarRenderer);
	
	SDL_Rect clip = {m_PosX, m_PosY, 40, 40};
	printf("x: %4f y: %4f", m_PosX,  m_PosY);
	//SDL_RenderClear(CarRenderer);
	g_FloorTexture.render((int)m_PosX, (int)m_PosY, CarRenderer, &clip);
	
	SDL_RenderPresent(CarRenderer);
}