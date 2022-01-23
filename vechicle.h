#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "utils.h"
//-----------------------------------------------------
// vechicle Class									
//-----------------------------------------------------
class vechicle final
{
public:
	vechicle(Point2f& pos,utils::Texture& Texture);		// Constructor
	~vechicle();				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	vechicle(const vechicle& other)  = delete;
	vechicle(vechicle&& other) noexcept  = delete;
	vechicle& operator=(const vechicle& other)  = delete;
	vechicle& operator=(vechicle&& other)	noexcept  = delete;

	// Member functions						
	void Update(float& dt);
	void SetDirection(Point2f& direction);
	void SetGoalTileIndex(int& tileIndex);
	void SetSpeed(float& speed);
	int GetTileIndex();
	void SetTileIndex(int tileIndex);
	int GetLastTileIndex();
	Point2f GetPosition();
	void SetGoalPosition(Point2f goalPos);
	Point2f GetGoalPosition();
	void Draw();
	int GetCounterPath();
	int GetGoalTileIndex();
	void SetCounterPath(int counter);
	Point2f GetDirection();
	
private:
	// Private member functions								
	void CalculateAngle();
	// Datamembers								
	int m_tileIndex{};
	int m_lastTileIndex{};
	int m_GoalTileIndex{};
	float m_speed{};
	Point2f m_direction{};
	Point2f m_defaultDirection{0,-1};
	Point2f m_Position;
	Point2f m_goalPosistion{};
	utils::Texture m_pTexture;
	Rectf m_SrcRect{};
	int m_chooseTexture{};
	int m_PathCounter{ 0 };
	float m_angle{ 0 };
};


