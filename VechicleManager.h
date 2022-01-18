#pragma once
#include "vechicle.h"
#include <vector>


class VechicleManager final
{
public:
	VechicleManager(utils::Texture& texture,std::vector<Point2f> gridPositions);
	~VechicleManager( );
	VechicleManager(const VechicleManager&) = delete;
	VechicleManager& operator=(const VechicleManager&) = delete;
	VechicleManager(VechicleManager&&) = delete;
	VechicleManager& operator=(VechicleManager&&) = delete;

	void Update( float elapsedSec);
	void Draw( ) const;
	void DeleteVechicle(int id);
	void DeleteAllVechicle();
	size_t Size( ) const;
	int GetLastid();
	void AddVehicle(Point2f& pos,std::vector<int> path);
	Point2f SeekDirection(Point2f& pos, Point2f& goalPos);
	Point2f NormalizeVector(Point2f& vector);
	void SetGoalPos(Point2f goalPos);
	void GoalUpdate(vechicle* vechicle);
	float distance(Point2f p1, Point2f p2);
private:
	std::vector<vechicle*> m_pVechicles;
	utils::Texture m_pTexture;
	std::vector <std::vector<int>> m_paths;
	float m_VechicleSpeed{ 100 };
	Point2f m_goalPos{};
	std::vector<Point2f> m_gridPositions;
};
