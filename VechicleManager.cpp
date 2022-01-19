#include "pch.h"
#include "VechicleManager.h"


VechicleManager::VechicleManager(utils::Texture& texture,std::vector<Point2f> gridPositions, const int& gridsize) :
	m_pTexture{ texture },
	m_gridSize{gridsize}
{
	m_gridPositions = gridPositions;
}
VechicleManager::~VechicleManager() {

	DeleteAllVechicle();
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
		if (distance(position, goalPosition) < 1) {
			//inc counter path
			vechicle->SetCounterPath(vechicle->GetCounterPath()+1);
			//inc goaltile trough path
			if (index < (int)m_paths.size()) {
				if (vechicle->GetCounterPath() <= int(m_paths[index].size() - 1)) {
					int nextTileIndex{ m_paths[index][vechicle->GetCounterPath()] };
					int currentTile{ vechicle->GetGoalTileIndex() };
					vechicle->SetGoalTileIndex(nextTileIndex);
					//update goal pos
					if (vechicle->GetCounterPath() + 1 < (int)m_paths[index].size() - 1) {
						int secondNextTileIndex{ m_paths[index][vechicle->GetCounterPath() + 1] };
						GoalUpdate(vechicle,currentTile,nextTileIndex,secondNextTileIndex);
						
					}
					else {
						int secondNextTileIndex{ MAXINT };
						GoalUpdate(vechicle, currentTile,nextTileIndex, secondNextTileIndex);
					}
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
void VechicleManager::GoalUpdate(vechicle* vechicle,int& currentTileIndex, int& nextTileIndex, int& SecondnextTileIndex) {
	if (nextTileIndex != MAXINT)m_goalPos = FindGoalPos( currentTileIndex,nextTileIndex,SecondnextTileIndex );
	else m_goalPos = vechicle->GetGoalPosition();//might need to change
	goalPoses.push_back(m_goalPos);
	vechicle->SetGoalPosition(m_goalPos);
}
Point2f  VechicleManager::FindGoalPos(int& currentTileIndex, int& nextTileIndex, int& SecondnextTileIndex) {
	//conection wil return 1:up 2:down 3:right 4:left for second next tile *10 for the next tile
	switch (CheckConnections(currentTileIndex,nextTileIndex,SecondnextTileIndex))
	{
		case 10:
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 1.33f),m_gridPositions[nextTileIndex].y + (50 / 4) };
			break;							
		case 20:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50/4),m_gridPositions[nextTileIndex].y + (50 / 1.33f) };
			break;							
		case 30:							
			return Point2f{ m_gridPositions[nextTileIndex].x + 50 / 4,m_gridPositions[nextTileIndex].y + 50 / 4 };
			break;							
		case 40:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 1.33f),m_gridPositions[nextTileIndex].y + (50 / 1.33f) };
			break;							
		case 11:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 1.33f),m_gridPositions[nextTileIndex].y + (50 / 4) };
			break;							
		case 13:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 1.33f),m_gridPositions[nextTileIndex].y + 50 / 4 };
			break;							
		case 14:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 1.33f),m_gridPositions[nextTileIndex].y + (50 / 1.33f) };
			break;							
		case 22:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50/4),m_gridPositions[nextTileIndex].y + (50 / (4 / 3)) };
			break;							
		case 23:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 4),m_gridPositions[nextTileIndex].y + (50 / 4) };
			break;							
		case 24:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 4),m_gridPositions[nextTileIndex].y + (50 / 1.33f) };
			break;							
		case 31:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 1.33f),m_gridPositions[nextTileIndex].y + (50 / 4) };
			break;							
		case 32:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 4),m_gridPositions[nextTileIndex].y + (50 / 4) };
			break;							
		case 33:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 4),m_gridPositions[nextTileIndex].y + (50 / 4) };
			break;							
		case 41:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 1.33f),m_gridPositions[nextTileIndex].y + (50 / 1.33f) };
			break;							
		case 42:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 4),m_gridPositions[nextTileIndex].y + (50 / 1.33f) };
			break;							
		case 44:							
			return Point2f{ m_gridPositions[nextTileIndex].x + (50 / 1.33f),m_gridPositions[nextTileIndex].y + (50 / 1.33f) };
			break;
	default:
		break;
	}
	return Point2f{ 0,0 };
}
void VechicleManager::Draw() const {
	//update all vechicles
	for (vechicle* vechicle : m_pVechicles) {
		vechicle->Draw();
	}
	for (Point2f pos : goalPoses) {
		utils::SetColor(1, 0, 1);
		utils::DrawEllipse(pos, 5, 5, 2);
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
	vechicleToAdd->SetGoalTileIndex(path[0]);//first tile of path
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

int VechicleManager::CheckConnections(int& currentTileIndex, int& nextTileIndex, int& SecondnextTileIndex) {
	int upcomingPathID{ 0 };
	//next tile check
	upcomingPathID+= 10 * checkConnection(currentTileIndex, nextTileIndex);
	//second next tile check
	if (SecondnextTileIndex != MAXINT) {
		upcomingPathID += checkConnection(nextTileIndex, SecondnextTileIndex);
	}
	return upcomingPathID;
}
int VechicleManager::checkConnection(int& currentTileIndex, int& nextTileIndex) {
	if (currentTileIndex - 10 >= 0) {
		if (currentTileIndex - 10 == nextTileIndex)return 1;
	}
	//down check
	if (currentTileIndex + 10 <= m_gridSize - 1) {
		if (currentTileIndex + 10 == nextTileIndex)return 2;
	}
	//if at most right col
	if (currentTileIndex % 10 != 9) {
		//Right check
		if (currentTileIndex + 1 == nextTileIndex)return 3;
	}
	//check if at most left col
	if (currentTileIndex % 10 != 0) {
		//Left check
		if (currentTileIndex - 1 == nextTileIndex)return 4;
	}
	return 0;
}