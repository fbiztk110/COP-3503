
//Using SDL, SDL Threads, SDL_image, standard IO, and, strings
#include <SDL_thread.h>
#include "Graphics_Car.h"
#include "Graphics_Windows.h"
//#include "RandomGenerator.h"
#include "Build.h"

bool QUIT = false;

//The window we'll be rendering to
LWindow* gWindows[TOTAL_WINDOWS]; 


//RandomGenerator* radMachine = new RandomGenerator();

//Scene textures
LTexture gBackgroundTexture[TOTAL_FLOORS];
LTexture gBackgroundRerender[TOTAL_FLOORS];
LTexture gCarTexture[TOTAL_WINDOWS];


//Mutex
/*
//The protective mutex
SDL_mutex* gBufferLock = NULL;

//The conditions
SDL_cond* gRenderAvailable = NULL;
*/

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		for (int j = 0; j < TOTAL_WINDOWS; j++)
			gWindows[j] = new LWindow();
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		int i = 0;
		//Create windows
		if (!gWindows[i]->init(i))
		{
			printf("Window 0 could not be created!\n");
			success = false;
		}
		if (success)
		{
			//Initialize the rest of the windows
			for (i = 1; i < TOTAL_WINDOWS; ++i)
			{
				gWindows[i]->init(i);
			}
		}
		//discarded code
		/*
		for (int i = 0; i < TOTAL_FLOORS; i++)
		{
			gWindow[i] = SDL_CreateWindow(("Intelligent Parking System - Floor " + (i + 1)), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create renderer for window
				gRenderer[i] = SDL_CreateRenderer(gWindow[i], -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

				if (gRenderer[i] == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer[i], 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! %s\n", IMG_GetError());
						success = false;
					}
				}
			}
		}*/
	}

	return success;
}

bool loadMedia()
{
	//Mutex
	/*
	//Create the mutex
	gBufferLock = SDL_CreateMutex();

	//Create conditions
	gRenderAvailable = SDL_CreateCond();
	*/

	//Loading success flag
	bool success = true;

	//Load splash texture
	if (!gBackgroundTexture[0].loadFromFile("1stFloor_Resources.png", gWindows[0]->getRenderer()))
	{
		printf("Failed to load Floor Plan texture!\n");
		success = false;
	}
	if (!gBackgroundTexture[1].loadFromFile("2ndFloor_Resources.png", gWindows[1]->getRenderer()))
	{
		printf("Failed to load Floor Plan texture!\n");
		success = false;
	}
	if (!gBackgroundTexture[2].loadFromFile("3rdFloor_Resources.png", gWindows[2]->getRenderer()))
	{
		printf("Failed to load Floor Plan texture!\n");
		success = false;
	}
	if (!gBackgroundTexture[3].loadFromFile("4thFloor_Resources.png", gWindows[3]->getRenderer()))
	{
		printf("Failed to load Floor Plan texture!\n");
		success = false;
	}
	else
	{
		gBackgroundRerender[0].loadFromFile("1stFloor_Resources.png", gWindows[0]->getRenderer());
		gBackgroundRerender[1].loadFromFile("2ndFloor_Resources.png", gWindows[1]->getRenderer());
		gBackgroundRerender[2].loadFromFile("3rdFloor_Resources.png", gWindows[2]->getRenderer());
		gBackgroundRerender[3].loadFromFile("4thFloor_Resources.png", gWindows[3]->getRenderer());
	}

	if (!gCarTexture[0].loadFromFile("carTexture.png", gWindows[0]->getRenderer()))
	{
		printf("Failed to load car texture!\n");
		success = false;
	}
	else
	{
		for (int i = 1; i < TOTAL_WINDOWS; i++)
		{
			gCarTexture[i].loadFromFile("carTexture.png", gWindows[i]->getRenderer());
		}

	}
	return success;
}

void close()
{
	//Free loaded images
	for (LTexture t : gCarTexture)
		t.free();

	//Mutex
	/*
	//Destroy the mutex
	SDL_DestroyMutex(gBufferLock);
	gBufferLock = NULL;

	//Destroy conditions
	SDL_DestroyCond(gRenderAvailable);
	//SDL_DestroyCond(gCanConsume);
	gRenderAvailable = NULL;
	*/

		
	for (int i = 0; i < TOTAL_FLOORS; i++)
	{
		//Free loaded images
		gBackgroundTexture[i].free();
	
		//Destroy window
		gWindows[i]->free();
	}

	/*
	for (int i = 0; i < carDeck.size(); i++)
		carDeck.at(i)->remove();
	*/

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//Thread One: To initialize cars on the floor
int threadOne( void* g)
{
	/*Here i is tracking the floor number, j is tracking the 
	*/
	int i, j, x = -40, y = -40, time, random;
	SDL_Renderer* render = 0;
	
	for (i = 0; i < TOTAL_FLOORS; i++)
	{
		for (j = 1; j <= TOTAL_LOTS_PER_FLOOR; j += random)
		{
			time = randomTime();
			random = randomNum(2 * (1 + i));
			
			render = gWindows[i]->getRenderer();

			//Garage::getPosition(x, y);

			//To Be Replaced: process the x, y positions to pixel positions
			x = randomNum(16) * 40;
			y = randomNum(12) * 40;

			Car* temp = new Car(render, gCarTexture[i], gBackgroundRerender[i], x, y);
			temp->render();
			Car::carDeck.push_back(temp);
			
			//Set callback
			SDL_TimerID timerID = SDL_AddTimer(time * 1000, callback, temp);
		}
	}

	printf("Thread 1 ran.");
	return 0;
}

//Randomly generate Cars. Simulate the car flow of the Garage
int threadTwo(void* g)
{
	int x = -40, y = -40, time = 0, fl = 0;
	SDL_Renderer* render = 0;
	while (!QUIT)
	{
		//here x is set as floor number and y is set as parking lot number
		//Garage->findFirstParking(x, y); 
		fl = x;
		render = gWindows[fl - 1]->getRenderer();
		//Now get the position for rendering
		//Garage::getPosition(x, y);

		Car* temp = new Car(render, gCarTexture[fl - 1], gBackgroundTexture[fl - 1],x, y);
		Car::carDeck.push_back(temp);
		temp->render();
		//Set callback
		//SDL_AddTimer(time * 1000, temp->CarCallBack, nullptr);
	}

	printf("Thread 2 ran.");
	return 0;
}

/*
int threadThree(void* g)
{
	while (!QUIT)
	{
		Garage garage;

		int choice;
		bool menu = true;
		int UFID;

		do
		{
			std::cout << " \n Please select one of the following options:  \n";

			std::cout << "1 - Entering \n2 - Leaving" << std::endl;

			std::cout << "Enter your selection: " << std::endl;
			std::cin >> choice;



			switch (choice)
			{
			case 1:

				std::cout << "You are now entering the garage";

				std::cout << "\n Please enter your UF ID: ";
				std::cin >> UFID;
				if (UFID < 10000000 || UFID > 99999999) {
					std::cout << "This UFID does not exist. Please enter a valid 8-digit UFID." << std::endl;

				}
				else if (UFID >= 10000000 || UFID <= 99999999) {
					int floorNum = garage.matchDecalType(UFID);
					// call function that assigns decal to matching floor

					// call function that assigns the next available slot for the user

					//confirm user selection of slot
				}
				break;
			case 2:
				std::cout << "You are now leaving the garage";

				std::cout << "\n Please enter your UF ID: ";
				std::cin >> UFID;
				if (UFID < 10000000 || UFID > 99999999) {
					std::cout << "This UFID does not exist. Please enter a valid 8-digit UFID." << std::endl;
				}
				else {
					//call function to check if UF ID is entered to a corresponding slot

					//if UF ID exists call free parking space function
				}


				break;
			case 3:
				return 0;
				std::cout << "You have exited the program.";
				break;
			default:
				std::cout << "Invalid Selection. Please enter valid input.";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;


			}

		} while ((choice != 1) || (choice != 2));
	}


	printf("Thread 3 ran.");
	return 0;
}
*/

Uint32 callback(Uint32 interval, void* param)
{
	static_cast<Car*>(param)->exit();

	return 0;
}

int randomID()  // random parking (generate ufid)
{
	int min = 10000000;
	int max = 99999999;
	int id = (rand() % (max - min + 1) + min);
	return id;

}

int randomTime()   //parking time for random parking
{
	int mintime = 10;  //minutes, but actually used as seconds
	int maxtime = 120;  // minutes, but actually used as seconds
	int time = (rand() % (maxtime - mintime + 1) + mintime);
	return time;
}

int randomNum(int gap)
{
	return (rand() % (gap + 1));
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			//Event handler
			SDL_Event e;

			
			//Render all windows with background texture
			for (int i = 0; i < TOTAL_FLOORS; i ++)
				gWindows[i]->render(gBackgroundTexture[i]);
			

			//declare and initialize data resources that will be shared to many threads
			//Garage* garage = new Garage();

			//Thread One: To initialize cars on the floor
			SDL_Thread* ThreadOne = SDL_CreateThread(threadOne, "ThreadOne", nullptr);
			SDL_WaitThread(ThreadOne, NULL);

			//Thread Two: Randomly produce Cars into the Graphics
			//SDL_Thread* ThreadTwo = SDL_CreateThread(threadTwo, "ThreadTwo", nullptr);

			//Thread Three: Obtain user's input for Cars into Garage
			//SDL_Thread* ThreadThree = SDL_CreateThread(threadThree, "ThreadThree", nullptr);
			//SDL_Thread* consumerThread = SDL_CreateThread(consumer, "Consumer", NULL);

			//Purely checking whether the program is still running 
			while (!QUIT)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						QUIT = true;
					}

					for (int i = 0; i < TOTAL_WINDOWS; ++i)
					{
						gWindows[i]->handleEvent(e);
					}
				}


				//Check all windows
				bool allWindowsClosed = true;
				for (int i = 0; i < TOTAL_WINDOWS; ++i)
				{
					if (gWindows[i]->isShown())
					{
						allWindowsClosed = false;
						break;
					}
				}

				if (allWindowsClosed)
					QUIT = true;

				//Car* car = new Car( gRenderer, gCarTexture,360, 40);

				//Update screen
				//SDL_RenderPresent(gRenderer);
				//SDL_RenderPresent(gCarRenderer);
			}

			//Wait for producer and consumer to finish
			
			//SDL_WaitThread(producerThread, NULL);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}