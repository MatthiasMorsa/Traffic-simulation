#pragma once
#include <vector>
#include "VechicleManager.h"
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Traffic simulation - Morsa, Matthias" };

// Change the window dimensions here
float g_WindowWidth{ 900 };
float g_WindowHeight{ 700 };
#pragma endregion gameInformation



#pragma region ownDeclarations
VechicleManager* g_pVechicleManager;
Point2f g_mousePos{};
const float g_GridSizeX = 50 , g_GridSizeY = 50;
const float g_WorldRow{ 800 / g_GridSizeX };
const float g_WorldCol{ 800 / g_GridSizeY };
const int  g_GridCells{ 100 };
const int g_gridsize{ (int)sqrt(g_GridCells) };
std::vector<int> g_path;
std::vector<Point2f> g_cellPosition{ };
Point2f g_startPos{ 50,((int)sqrt(g_GridCells) * g_GridSizeY) + 5};
int g_CellState[g_GridCells]{};
Texture g_pGrass,g_pRoadPoint,g_pRoadUtoL, g_pRoadUtoR, g_pRoadDtoL, g_pRoadDtoR,
		g_pRoadHorizontal, g_pRoadVertical,g_pRoadEndD, g_pRoadEndL, g_pRoadEndU,
		g_pRoadEndR, g_pRoadLDR, g_pRoadLUD, g_pRoadLUR, g_pRoadURD, g_pRoadCross,
		g_pHouseL, g_pHouseR, g_pHouseU, g_pHouseD,g_pFactoryU, g_pFactoryD, g_pFactoryL, g_pFactoryR,
		g_pCarTexture;
// Declare your own functions here
void GetTextures();
void releaseTextures();
void GridPositions();
void DrawGrid();
void Tilecliked();
Texture TileSelector(int& tileIndex);
Texture RoadSelector(int& tileIndex);
Texture HouseSelector(int& tileIndex);
Texture FactorySelector(int& tileIndex);
int CheckConnections(int& tileIndex);
std::vector<int> GetNeighbours(int& tileIndex);
std::vector<int> FindPath(int StartIndex, int EndIndex);
#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
