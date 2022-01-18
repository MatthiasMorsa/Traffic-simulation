#include "pch.h"
#include "VechicleManager.h"


VechicleManager::VechicleManager(utils::Texture& texture,std::vector<Point2f> gridPositions) :
	m_pTexture{ texture }
{
	m_gridPositions = gridPositions;
}
VechicleManager::~VechicleManager() {

	for (vechicle* vechicle : m_pVechicles) {

		
		delete vechicle;

	}
	m_pVechicles.clear();
}

void VechicleManager::DeleteAllVechicle()
{
	for (vechicle* vechicle : m_pVechicles) {


		delete vechicle;

	}
	m_pVechicles.clear();
}

void VechicleManager::Update(float elapsedSec) {
	//update all vechicles
	int index{ -1 };
	for (vechicle* vechicle : m_pVechicles) {
		index++;
		bool deleteVechicle{ false };
		Point2f position{ vechicle->GetPosition() };
		Point2f goalPosition{ vechicle->GetGoalPosition() };
		m_goalPos = vechicle->GetGoalPosition();

		vechicle->Update(elapsedSec);
		//check if near goal
		if (distance(position, goalPosition) < 5) {
			//inc counter path
			vechicle->SetCounterPath(vechicle->GetCounterPath()+1);
			//inc goaltile trough path
			if (index < (int)m_paths.size()) {
				if (vechicle->GetCounterPath() <= int(m_paths[index].size() - 1)) {
					int goalTileIndex{ m_paths[index][vechicle->GetCounterPath()] };
					vechicle->SetGoalTileIndex(goalTileIndex);
					//update goal pos
					GoalUpdate(vechicle);
					//
					m_goalPos = vechicle->GetGoalPosition();
					Point2f direction{ SeekDirection(position,m_goalPos) };
					vechicle->SetDirection(direction);
				}
				else {
					//delete vechcile he got to the goal
					deleteVechicle = true;
				}
			}
		}


		if (deleteVechicle)DeleteVechicle(index);
		else {
			Point2f direction{ SeekDirection(position,m_goalPos) };
			vechicle->SetDirection(direction);
		}
	}
}
void VechicleManager::GoalUpdate(vechicle* vechicle) {
	int tileindex{ vechicle->GetGoalTileIndex() };
	m_goalPos = m_gridPositions[tileindex];
	vechicle->SetGoalPosition(m_goalPos);
}
void VechicleManager::Draw() const {
	//update all vechicles
	for (vechicle* vechicle : m_pVechicles) {
		vechicle->Draw();
	}
}

size_t VechicleManager::Size() const {
	return m_pVechicles.size();
}


void VechicleManager::DeleteVechicle(int id)
{
	vechicle* backup{ m_pVechicles[m_pVechicles.size() - 1] };
	delete m_pVechicles[id];
	
	m_pVechicles[id] = backup;
	m_pVechicles.pop_back();
	//wel also need to delete the path 

	//std::vector<int> backup{ m_paths[m_paths.size() - 1] };
	//delete m_pVechicles[id];

	m_paths.at(id) = m_paths[m_paths.size() - 1];
	m_paths.pop_back();
}

int VechicleManager::GetLastid()
{
	return int(m_pVechicles.size() - 1);
}

void VechicleManager::AddVehicle(Point2f& pos, std::vector<int> path) {
	//ad car and path to memory
	m_pVechicles.push_back(new vechicle(pos, m_pTexture));
	vechicle* vechicleToAdd{ m_pVechicles[m_pVechicles.size() - 1] };
	//save path
	m_paths.push_back(path);
	//set car start configuration
	vechicleToAdd->SetSpeed(m_VechicleSpeed);
	vechicleToAdd->SetCounterPath(0);
	vechicleToAdd->SetGoalTileIndex(path[1]);//first tile of path
	vechicleToAdd->SetGoalPosition(m_gridPositions[vechicleToAdd->GetGoalTileIndex()]);
	Point2f position{ vechicleToAdd->GetPosition() };
	Point2f goalPosition{ vechicleToAdd->GetGoalPosition() };
	Point2f direction{ SeekDirection(position,goalPosition) };
	vechicleToAdd->SetDirection(direction);
}
Point2f VechicleManager::SeekDirection(Point2f& pos, Point2f& goalPos) {
	Point2f steering{ goalPos.x - pos.x ,goalPos.y - pos.y };
	if(steering.x == 0 && steering.y ==0)return steering;
	steering = NormalizeVector(steering);
	return steering;
}
Point2f VechicleManager::NormalizeVector(Point2f& vector) {
	float lenght{(float)sqrtf((vector.x * vector.x) + (vector.y * vector.y) )};
	Point2f normalizedVec{ vector.x / lenght,vector.y / lenght };
	return normalizedVec;
}
void VechicleManager::SetGoalPos(Point2f goalPos) {
	m_goalPos = goalPos;
}
float VechicleManager::distance(Point2f Point1, Point2f Point2)
{
	float X{};
	float Y{};
	double result{};
	if (Point1.x > Point2.x) X = Point1.x - Point2.x;
	else X = Point2.x - Point1.x;
	if (Point1.y > Point2.y) Y = Point1.y - Point2.y;
	else Y = Point2.y - Point1.y;
	result = sqrt(pow(X, 2) + pow(Y, 2));
	return float(result);
}
