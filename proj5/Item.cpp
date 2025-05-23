/*Title: Item.cpp
  Author: Prof. Dixon
  Date: 4/17/2025
  Description: Implementation of Item class
*/

#include "Item.h"
#include <stdexcept>

// Name: Item(const string& name, const vector<string>& requirements)
// Description: Constructs a new Item with the given name and
//              a list of crafting requirements.
// Preconditions: 'name' must be a valid, non-empty string;
//                'requirements' must contain valid item names.
// Postconditions: m_name is initialized to name;
//                 m_req is initialized to a copy of requirements.
Item::Item(const string& name, const vector<string>& requirements) 
    : m_name(name), m_req(requirements) {
    if (name.empty()) {
        throw invalid_argument("Item name cannot be empty");
    }
}

// Name: GetName()
// Description: Retrieves the name of this item.
// Preconditions: None.
// Postconditions: Returns the value of m_name.
string Item::GetName() const {
    return m_name;
}

// Name: GetReq()
// Description: Retrieves the list of crafting requirements for this item.
// Preconditions: None.
// Postconditions: Returns a const reference to m_req
//                 (the requirements vector).
const vector<string>& Item::GetReq() const {
    return m_req;
}
