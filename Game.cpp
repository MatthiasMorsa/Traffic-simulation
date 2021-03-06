#include "pch.h"
#include "Game.h"
#include "vechicle.h"
#include <iostream>
#include <assert.h>
#include <queue>
#include <map>
//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	GridPositions();
	//set all tiles grass
	for (int state : g_CellState) {
		state = 0;
	}
	//load all textures needed
	GetTextures();
	//create vechicleManager
	g_pVechicleManager = new VechicleManager(g_pCarTexture,g_cellPosition, g_GridCells);
	//Point2f pos{ g_cellPosition[0] };
	//g_pVechicleManager->AddVehicle(pos, FindPath(0,99));
}
void GetTextures() {
	assert(TextureFromFile("textures/grass.png", g_pGrass));
	assert(TextureFromFile("textures/RoadHorizontale.png", g_pRoadHorizontal));
	assert(TextureFromFile("textures/RoadVerticale.png", g_pRoadVertical));
	assert(TextureFromFile("textures/RoadEndD.png", g_pRoadEndD));
	assert(TextureFromFile("textures/RoadEndL.png", g_pRoadEndL));
	assert(TextureFromFile("textures/RoadEndR.png", g_pRoadEndR));
	assert(TextureFromFile("textures/RoadEndU.png", g_pRoadEndU));
	assert(TextureFromFile("textures/RoadTurnDtoL.png", g_pRoadDtoL));
	assert(TextureFromFile("textures/RoadTurnDtoR.png", g_pRoadDtoR));
	assert(TextureFromFile("textures/RoadTurnUtoL.png", g_pRoadUtoL));
	assert(TextureFromFile("textures/RoadTurnUtoR.png", g_pRoadUtoR));
	assert(TextureFromFile("textures/RoadPoint.png", g_pRoadPoint));
	assert(TextureFromFile("textures/RoadLDR.png", g_pRoadLDR));
	assert(TextureFromFile("textures/RoadLUD.png", g_pRoadLUD));
	assert(TextureFromFile("textures/RoadLUR.png", g_pRoadLUR));
	assert(TextureFromFile("textures/RoadURD.png", g_pRoadURD));
	assert(TextureFromFile("textures/RoadCross.png", g_pRoadCross));
	assert(TextureFromFile("textures/houseL.png", g_pHouseL));
	assert(TextureFromFile("textures/houseR.png", g_pHouseR));
	assert(TextureFromFile("textures/houseU.png", g_pHouseU));
	assert(TextureFromFile("textures/houseD.png", g_pHouseD));
	assert(TextureFromFile("textures/FactoryU.png", g_pFactoryU));
	assert(TextureFromFile("textures/FactoryD.png", g_pFactoryD));
	assert(TextureFromFile("textures/FactoryL.png", g_pFactoryL));
	assert(TextureFromFile("textures/FactoryR.png", g_pFactoryR));
	assert(TextureFromFile("textures/CarTexture.png", g_pCarTexture));
}
void Draw()
{
	ClearBackground();
	// Put your own draw statements here
	DrawGrid();
	g_pVechicleManager->Draw();
	if (g_Simulating)SetColor(0, 1, 0);
	else SetColor(1, 0, 0);
	FillRect(Rectf{ 0,0,50,50 });
}

void Update(float elapsedSec)
{
	if (g_Simulating) {
		g_pVechicleManager->Update(elapsedSec);
		SpawnVechicles(elapsedSec);
	}
	g_AmountOfCars = g_pVechicleManager->getAmountOfVechicle();
}
void SpawnVechicles(float elapsedSec) {
	if(g_AmountOfCars<g_MaxAmountOfCars){
		if (g_elapsedSecCarSpawn > g_delaySpawnCar) {
			g_delaySpawnCar = ((rand() % 100) / 100.0f) +0.5f;
			g_elapsedSecCarSpawn = 0;
			int houseIndex{ 0 };
			int FactoryIndex{ 0 };
			int wichHouse{ rand() % g_AmountOfHouses };
			int wichFactory{ rand() % g_AmountOfFactories };
			int counter{ 0 };
			for (int indexHouse{ 0 }; indexHouse < g_GridCells - 1; indexHouse++) {
				if (counter == wichHouse)houseIndex = indexHouse;
				if (g_Houses[indexHouse] == 1)counter++;
			}
			counter = 0;
			for (int indexFactory{ 0 }; indexFactory < g_GridCells - 1; indexFactory++) {
				if (counter == wichFactory)FactoryIndex = indexFactory;
				if (g_Factories[indexFactory] == 1)counter++;
			}
			Point2f direction{ FindSpawnDirection(houseIndex) };
			int connections{ CheckConnections(houseIndex) };
			//get index of first road
			int road1{};
			if (connections >= 2 && connections < 4)road1 = houseIndex - 1;
			else if (connections >= 4 && connections < 8)road1 = houseIndex + 10;
			else if (connections >= 8)road1 = houseIndex - 10;
			else road1 = houseIndex + 1;
			//get index of last road
			int road2{};
			connections = CheckConnections(FactoryIndex);
			if (connections >= 2 && connections < 4)road2 = FactoryIndex - 1;
			else if (connections >= 4 && connections < 8)road2 = FactoryIndex + 10;
			else if (connections >= 8)road2 = FactoryIndex - 10;
			else road2 = FactoryIndex + 1;

			g_path = FindPath(road1, road2);
			g_pVechicleManager->AddVehicle(houseIndex, g_path, direction);
		}
		
	}
		g_elapsedSecCarSpawn += elapsedSec;
}
Point2f FindSpawnDirection(int& houseIndex) {
	int selection{ CheckConnections(houseIndex) };
	if (selection >= 2 && selection < 4)return { Point2f{-1,0} };
	else if (selection >= 4 && selection < 8)	return { Point2f{0,-1} };
	else if (selection >= 8)return { Point2f{0,1} };
	return { Point2f{1,0} };
}
void End()
{
	// free game resources here
	//deleting all textures
	releaseTextures();
	delete g_pVechicleManager;
}
void releaseTextures() {
	DeleteTexture(g_pGrass);
	DeleteTexture(g_pRoadHorizontal);
	DeleteTexture(g_pRoadVertical);
	DeleteTexture(g_pRoadEndD);
	DeleteTexture(g_pRoadEndL);
	DeleteTexture(g_pRoadEndR);
	DeleteTexture(g_pRoadEndU);
	DeleteTexture(g_pRoadDtoL);
	DeleteTexture(g_pRoadDtoR);
	DeleteTexture(g_pRoadUtoL);
	DeleteTexture(g_pRoadUtoR);
	DeleteTexture(g_pRoadPoint);
	DeleteTexture(g_pRoadLDR);
	DeleteTexture(g_pRoadLUD);
	DeleteTexture(g_pRoadLUR);
	DeleteTexture(g_pRoadURD);
	DeleteTexture(g_pRoadCross);
	DeleteTexture(g_pHouseL);
	DeleteTexture(g_pHouseR);
	DeleteTexture(g_pHouseU);
	DeleteTexture(g_pHouseD);
	DeleteTexture(g_pFactoryU);
	DeleteTexture(g_pFactoryD);
	DeleteTexture(g_pFactoryL);
	DeleteTexture(g_pFactoryR);
	DeleteTexture(g_pCarTexture);
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	int indexcell{ 0 };
	Point2f direction{ 1,0 };
	switch (key)
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		//test for vechicle spawning/pathfinding
		//g_pVechicleManager->AddVehicle(indexcell, FindPath(0, 99), direction);
		break;
	case SDLK_RIGHT:
		//std::cout << "Right arrow key released\n";
		break;
	case SDLK_1:
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	case SDLK_SPACE:
		if (g_Simulating) {
			g_Simulating = false;
			g_pVechicleManager->DeleteAllVechicle();
		}
		else {
			g_Simulating = true;
		}
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	Point2f mousePos{ float(e.x), float(g_WindowHeight - e.y) };
	//save current mouse position
	g_mousePos.x = mousePos.x;
	g_mousePos.y = mousePos.y;
	switch (e.button)
	{
		case SDL_BUTTON_LEFT:
		{

		if(!g_Simulating)Tilecliked();
		//std::cout << "Left mouse button released\n";
		//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		break;
		}
		case SDL_BUTTON_RIGHT:
		{
			if (!g_Simulating)TileRightcliked();
			//std::cout << "Left mouse button released\n";
			//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
			break;
		}
	}
}
void Tilecliked() {
	int index{};
	for (int counter{ 0 }; counter < g_GridCells; counter++) {
		if ((g_mousePos.x < (g_cellPosition[counter].x + g_GridSizeX)) && (g_mousePos.x > g_cellPosition[counter].x)) {
			if ((g_mousePos.y < (g_cellPosition[counter].y + g_GridSizeY)) && (g_mousePos.y > g_cellPosition[counter].y)) {
				index = counter;
				std::cout << index << "\n";
				if (g_CellState[index] == 0)g_CellState[index] += 1;//road tile
				else if (g_CellState[index] == 1){
					g_CellState[index] += 1;//house tile
					g_Houses[index] = 1;
					g_AmountOfHouses += 1;
				}
				else if (g_CellState[index] == 2) {
					g_CellState[index] += 1;//factory tile
					g_Houses[index] = 0;
					g_AmountOfHouses -= 1;
					g_Factories[index] = 1;
					g_AmountOfFactories += 1;
				}
				else {
					g_CellState[index] = 0;//grass tile
					g_Factories[index] = 0;
					g_AmountOfFactories -= 1;
				}
			}
		}
	}

}
void TileRightcliked() {
	int index{};
	for (int counter{ 0 }; counter < g_GridCells; counter++) {
		if ((g_mousePos.x < (g_cellPosition[counter].x + g_GridSizeX)) && (g_mousePos.x > g_cellPosition[counter].x)) {
			if ((g_mousePos.y < (g_cellPosition[counter].y + g_GridSizeY)) && (g_mousePos.y > g_cellPosition[counter].y)) {
				index = counter;
				std::cout << index << "\n";
				if (g_CellState[index] == 1) {
					g_Houses[index] = 0;
					g_AmountOfHouses -= 1;
				}
				if (g_CellState[index] == 2) {
					g_Factories[index] = 0;
					g_AmountOfFactories -= 1;
				}
				g_CellState[index] = 0;

			
			}
		}
	}

}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here

void GridPositions() {
	
	int cell{ 0 };
	Point2f pos{};
	pos.x = g_startPos.x;
	pos.y = g_startPos.y;
	Point2f cellPosition[g_GridCells]{};
	for (int irow{ 0 }; irow < g_gridsize; irow++) {
		for (int icol{ 0 }; icol < g_gridsize; icol++) {//put positions from cells 
			cellPosition[irow * g_gridsize + icol].x = pos.x;
			cellPosition[irow * g_gridsize + icol].y = pos.y;
			pos.x += g_GridSizeX;
		}

		pos.y -= g_GridSizeY;
		pos.x = g_startPos.x;
	}
	for (Point2f pos : cellPosition) {
		g_cellPosition.push_back(pos);
	}
}
void DrawGrid() {
	int irow{ 0 };
	int icol{ 0 };
	int index{ 0 };
	//draw cells
	while (irow < g_gridsize) {
		if (icol < g_gridsize) {

			//drawtile
			if (g_CellState[index] == 0)SetColor(1, 1, 1);
			else SetColor(0, 0, 0);
			FillRect(g_cellPosition[index].x, g_cellPosition[index].y, g_GridSizeX, g_GridSizeY);
			DrawTexture(TileSelector(index), g_cellPosition[index]);
			icol++;
			index++;//next cell index
		}
		else {
			irow++; icol = 0;
		}
	}
	irow = 0;
	////pathfinding test
	//for (int index : g_path)
	//{
	//	SetColor(1, 1, 0,0.5f);
	//	FillRect(g_cellPosition[index].x, g_cellPosition[index].y, g_GridSizeX, g_GridSizeY);
	//}
}
Texture TileSelector(int& tileIndex) {

	switch (g_CellState[tileIndex])
	{
	case 0://grass type
		return g_pGrass;
		break;
	case 1://road type
		return RoadSelector(tileIndex);
		break;
	case 2://house type
		return HouseSelector(tileIndex);;
		break;
	case 3://factory type
		return FactorySelector(tileIndex);;
		break;
	default:
		break;
	}


	return g_pGrass;
}
Texture RoadSelector(int& tileIndex) {
	//trough the bits we know what other tiles are connected to the tile
	int selection{ 0 };//up  left
	//                 0 0 0 0<right
	//               down^
	selection = CheckConnections(tileIndex);
	switch (selection)
	{
	case 0:
		return g_pRoadPoint;
		break;
	case 1:
		return g_pRoadEndL;
		break;
	case 2:
		return g_pRoadEndR;
		break;
	case 3:
		return g_pRoadHorizontal;
		break;
	case 4:
		return g_pRoadEndU;
		break;
	case 5:
		return g_pRoadUtoR;
		break;
	case 6:
		return g_pRoadUtoL;
		break;
	case 7:
		return g_pRoadLDR;
		break;
	case 8:
		return g_pRoadEndD;
		break;
	case 9:
		return g_pRoadDtoR;
		break;
	case 10:
		return g_pRoadDtoL;
		break;
	case 11:
		return g_pRoadLUR;
		break;
	case 12:
		return g_pRoadVertical;
		break;
	case 13:
		return g_pRoadURD;
		break;
	case 14:
		return g_pRoadLUD;
		break;
	case 15:
		return g_pRoadCross;
		break;
	default:
		return g_pGrass;
		break;
	}
}
Texture HouseSelector(int& tileIndex) {
	//trough the bits we know what other tiles are connected to the tile
	int selection{ 0 };  //up  left
		//                 0 0 0 0<right
		//               down^
	selection = CheckConnections(tileIndex);
	//return texture
	if (selection >= 2 && selection < 4)return g_pHouseL;
	else if (selection >= 4 && selection < 8)return g_pHouseD;
	else if (selection >= 8)return g_pHouseU;
	return g_pHouseR;
}
Texture FactorySelector(int& tileIndex) {
	//trough the bits we know what other tiles are connected to the tile
	int selection{ 0 };  //up  left
		//                 0 0 0 0<right
		//               down^
	selection = CheckConnections(tileIndex);
	//return texture
	if (selection >= 2 && selection < 4)return g_pFactoryL;
	else if (selection >= 4 && selection < 8)return g_pFactoryD;
	else if (selection >= 8)return g_pFactoryU;
	return g_pFactoryR;
}

int CheckConnections(int& tileIndex) {
	int upIndex{ MAXINT }, downIndex{ MAXINT }, leftIndex{ MAXINT }, rightIndex{ MAXINT }, selector{0};
	//up check
	if (tileIndex - 10 >= 0) {
		if (g_CellState[tileIndex - 10] == 1)upIndex =  1;
	}
	//down check
	if (tileIndex + 10 <= g_GridCells-1) {
		if (g_CellState[tileIndex + 10] == 1)downIndex =  1;
	}
	//if at most right col
	if (tileIndex % 10 != 9){
		//Right check
		if (g_CellState[tileIndex + 1] == 1)rightIndex = 1;
	}
	//check if at most left col
	if (tileIndex % 10 != 0){
		//Left check
		if (g_CellState[tileIndex - 1] == 1)leftIndex = 1;
	}
	            //up  left
//                 0 0 0 0<right
//               down^
	//get selector
	if (rightIndex != MAXINT)selector += 1;
	if (leftIndex != MAXINT)selector += 2;
	if (downIndex != MAXINT)selector += 4;
	if (upIndex != MAXINT)selector += 8;

	return selector;
}

std::vector<int> GetNeighbours(int& tileIndex){
	//up check
	std::vector<int> neighbourIndexes{};
	if (tileIndex - 10 >= 0) {
		if (g_CellState[tileIndex - 10] == 1)neighbourIndexes.push_back(tileIndex-10);
	}
	//down check
	if (tileIndex + 10 <= g_GridCells - 1) {
		if (g_CellState[tileIndex + 10] == 1)neighbourIndexes.push_back(tileIndex + 10);
	}
	//if at most right col
	if (tileIndex % 10 != 9) {
		//Right check
		if (g_CellState[tileIndex + 1] == 1)neighbourIndexes.push_back(tileIndex + 1);
	}
	//check if at most left col
	if (tileIndex % 10 != 0) {
		//Left check
		if (g_CellState[tileIndex - 1] == 1)neighbourIndexes.push_back(tileIndex - 1);
	}
	return neighbourIndexes;
}

std::vector<int>  FindPath(int StartIndex, int EndIndex){

	std::queue<int> openlist; //Nodes that still need a check
	std::map<int, int> closedList; // already checked nodes

	openlist.push(StartIndex);

	while (!openlist.empty())
	{
		int currentIndex = openlist.front();    //taking a node from the openlist
		openlist.pop(); //removing that node

		if (currentIndex == EndIndex)//stop searching we found end
		{
			//closedList[currentIndex] = closedList[currentIndex-1]
			break;
		}
		for (int index : GetNeighbours(currentIndex))
		{
			if (closedList.find(index) == closedList.end())
			{
				//we did not find this node in de closedlist
				openlist.push(index);
				closedList[index] = currentIndex;
			}
		}
	}

	//Start tracking the path
	std::vector<int> path;
	int currentIndex = EndIndex;

	while (currentIndex != StartIndex)
	{
		path.push_back(currentIndex);
		currentIndex = closedList[currentIndex];
	}
	path.push_back(StartIndex);
	std::reverse(path.begin(), path.end());//reversing path so the beginning is at the green dot

	return path;
}
#pragma endregion ownDefinitions