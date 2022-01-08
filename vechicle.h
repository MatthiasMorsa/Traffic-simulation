#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------


//-----------------------------------------------------
// vechicle Class									
//-----------------------------------------------------
class vechicle final
{
public:
	vechicle();				// Constructor
	~vechicle();				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	vechicle(const vechicle& other) {}
	vechicle(vechicle&& other) noexcept {}
	vechicle& operator=(const vechicle& other) {}
	vechicle& operator=(vechicle&& other)	noexcept {}

	// Member functions						



private:
	// Private member functions								

	// Datamembers								


};


