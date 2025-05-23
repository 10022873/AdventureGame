/*Title: Area.cpp
  Author: Prof. Dixon
  Date: 4/17/2025
  Description: Implementation of Area class methods
*/

#include "Area.h"
#include <iostream>

// Name: Area (Constructor)
// Description: Creates a new Area object with specified parameters
// Preconditions: All parameters must be valid
// Postconditions: New Area object is created with specified properties
Area::Area(int id, string name, string desc, int north, int east, int south, int west)
    : m_ID(id), m_name(name), m_desc(desc) {
    m_direction[N] = north;
    m_direction[E] = east;
    m_direction[S] = south;
    m_direction[W] = west;
}

// Name: GetName
// Description: Returns the area's name
// Preconditions: Area must be properly initialized
// Postconditions: Returns m_name as string
string Area::GetName() {
    return m_name;
}

// Name: GetID
// Description: Returns the area's unique identifier
// Preconditions: Area must be properly initialized
// Postconditions: Returns m_ID as int
int Area::GetID() {
    return m_ID;
}

// Name: GetDesc
// Description: Returns the area's description
// Preconditions: Area must be properly initialized
// Postconditions: Returns m_desc as string
string Area::GetDesc() {
    return m_desc;
}

// Name: CheckDirection
// Description: Checks if there's an exit in specified direction
// Preconditions: Area must be properly initialized
// Parameters: char direction (case insensitive N/E/S/W)
// Postconditions: Returns adjacent area ID or -1 if no exit
int Area::CheckDirection(char myDirection) {
    switch(toupper(myDirection)) {
        case 'N': return m_direction[N];
        case 'E': return m_direction[E];
        case 'S': return m_direction[S];
        case 'W': return m_direction[W];
        default: return -1;
    }
}

// Name: PrintArea
// Description: Displays area information to console
// Preconditions: Area must be complete
// Postconditions: Outputs name, description, and available exits
void Area::PrintArea() {
    cout << m_name << endl << m_desc << endl << "Possible Exits: ";
    
    if(m_direction[N] != -1) cout << "N ";
    if(m_direction[E] != -1) cout << "E ";
    if(m_direction[S] != -1) cout << "S ";
    if(m_direction[W] != -1) cout << "W ";
    
    cout << endl;
}
