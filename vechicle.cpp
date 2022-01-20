
//---------------------------
// Includes
//---------------------------
#include "pch.h"
#include "vechicle.h"

//---------------------------
// Static datamembers
//---------------------------
// initialize static datamembers here 

//---------------------------
// Constructor(s) & Destructor
//---------------------------
vechicle::vechicle(Point2f& pos,utils::Texture& texture):
	m_Position{pos},
	m_pTexture{texture}
{
	m_chooseTexture = rand() % 2;
	if (m_chooseTexture == 0) {//red car
		m_SrcRect.left = 0;
		m_SrcRect.bottom = texture.height;
		m_SrcRect.width = texture.width/2;
		m_SrcRect.height = texture.height;
	}
	else {//blue car
		m_SrcRect.left = texture.width / 2;
		m_SrcRect.bottom = texture.height;
		m_SrcRect.width = texture.width / 2;
		m_SrcRect.height = texture.height;
	}
}

vechicle::~vechicle()
{
	// nothing to destroy
}

//---------------------------
// Member functions
//---------------------------

// write member functions here
void vechicle::Update(float& dt) {
	m_Position.x += m_direction.x * m_speed * dt;
	m_Position.y += m_direction.y * m_speed * dt;

	CalculateAngle();
}
void vechicle::Draw() {
	Rectf DstRect{0,0,m_pTexture.width / 2,m_pTexture.height };
	glPushMatrix();
	
	glTranslatef(m_Position.x, m_Position.y, 0);//go to vechicle
	//glScalef(1, 1, 1);//invers vechicle sprite
	glRotatef(-m_angle, 0, 0, 1);//rotate projectile 
	glTranslated(-(m_pTexture.width/4),-m_pTexture.height/2, 0);//translate to middle vechicle

	utils::DrawTexture(m_pTexture, DstRect, m_SrcRect);//draw on vechicle pos
	glPopMatrix();//return to world pos

}
void vechicle::SetDirection(Point2f& direction) {
	m_direction = direction;
}
void vechicle::SetGoalTileIndex(int& tileIndex) {
	m_GoalTileIndex = tileIndex;
}
void vechicle::SetSpeed(float& speed) {
	m_speed = speed;
}
int vechicle::GetTileIndex() {
	return m_tileIndex;
}
Point2f vechicle::GetPosition() {
	return m_Position;
}
int vechicle::GetCounterPath() {
	return m_PathCounter;
	
}
void vechicle::CalculateAngle() {
	float dot = m_direction.x * m_defaultDirection.x + m_direction.y * m_defaultDirection.y;     // dot product between[x1, y1] and [x2, y2]
	float det = m_direction.x * m_defaultDirection.y - m_direction.y * m_defaultDirection.x;     // determinant
	m_angle = (float)atan2(det, dot);
	m_angle *= ( 180/ 3.14f);
}
int vechicle::GetGoalTileIndex() {
	return m_GoalTileIndex;
}
void vechicle::SetCounterPath(int counter) {
	m_PathCounter = counter;
}

void vechicle::SetGoalPosition(Point2f goalPos) {
	m_goalPosistion = goalPos;
}
Point2f vechicle::GetGoalPosition() {
	return m_goalPosistion;
}
void vechicle::SetTileIndex(int tileIndex) {
	m_tileIndex = tileIndex;
}


