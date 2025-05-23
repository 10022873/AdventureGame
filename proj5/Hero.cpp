#include "Hero.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>

// Name: Hero(const string& name)
// Description: Constructs a new Hero with the specified name.
// Preconditions: name must be a valid, non-empty string.
// Postconditions: m_name is initialized; inventory map is empty.
Hero::Hero(const string& name) : m_name(name) {
    if (name.empty()) {
        throw invalid_argument("Hero name cannot be empty");
    }
}

// Name: ~Hero()
// Description: Destructor for Hero.
// Preconditions: None.
// Postconditions: Releases any dynamically allocated items in Hero.
//                 None in this case.
Hero::~Hero() {}

// Name: GetName()
// Description: Retrieves the hero's name.
// Preconditions: None.
// Postconditions: Returns the value of m_name.
string Hero::GetName() const {
    return m_name;
}

// Name: SetName(const string& name)
// Description: Updates the hero's name.
// Preconditions: name must be a valid string.
// Postconditions: m_name is set to the new value.
void Hero::SetName(const string& name) {
    if (name.empty()) {
        throw invalid_argument("Hero name cannot be empty");
    }
    m_name = name;
}

// Name: DisplayInventory()
// Description: Prints the hero's current inventory using overloaded << operator
// Preconditions: Inventory map has been initialized.
// Postconditions: Inventory contents are displayed.
void Hero::DisplayInventory() const {
    cout << m_name << "'s Inventory:" << endl;
    cout << m_inventory;
}

// Name: CollectItem(const string& item)
// Description: If the item exists, in m_inventory, uses Update to increment quantity
//              If the item does not exist in m_inventory, inserts it.
// Preconditions: item must be a valid item name.
// Postconditions: Inventory count for item is incremented by 1.
// Note: Uses try and catch (const out_of_range&) and inserts if caught.
void Hero::CollectItem(const string& item) {
    try {
        int current = m_inventory.ValueAt(item);
        m_inventory.Insert(item, current + 1);
    } catch (const out_of_range&) {
        m_inventory.Insert(item, 1);
    }
}

// Name: CanCraft(const vector<string>& requirements)
// Description: Iterators through the requirements to see if they have quantity in m_inventory
// Preconditions: Requirements vector populated with item names.
// Postconditions: Returns true if every required item has count ≥1.
// Note: Uses try and catch (const out_of_range&) and returns false if caught.
bool Hero::CanCraft(const vector<string>& requirements) const {
    for (const string& item : requirements) {
        try {
            if (m_inventory.ValueAt(item) < 1) {
                return false;
            }
        } catch (const out_of_range&) {
            return false;
        }
    }
    return true;
}


// Name: Craft(const string& result, const vector<string>& requirements)
// Description: Consumes the listed requirements and adds the
//              crafted "result" (iterates through requirements and Updates)
// Preconditions: Call to CanCraft(requirements) must return true.
// Postconditions: Each requirement's count is decremented by 1;
//                 Result of crafting is added.
void Hero::Craft(const string& result, const vector<string>& requirements) {
    if (!CanCraft(requirements)) {
        throw runtime_error("Cannot craft " + result + " - missing requirements");
    }

    for (const string& item : requirements) {
        int current = m_inventory.ValueAt(item);
        m_inventory.Insert(item, current - 1);
    }

    CollectItem(result);
    cout << "Successfully crafted " << result << "!" << endl;
}

// Name: Raw()
// Description: Simulates mining for raw materials. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random raw material
//                 to inventory or reports none found.
void Hero::Raw() {
    Gather(RawProducts, "You mined but found nothing.",
           "You mined and found ");
}

// Name: Natural()
// Description: Simulates foraging for natural resources. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random natural resource
//                 or reports none found.
void Hero::Natural() {
    Gather(NaturalProducts, "You foraged but found nothing.",
           "You foraged and found ");
}

// Name: Food()
// Description: Simulates gathering food items. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random food item or reports none found.
void Hero::Food() {
    Gather(FoodProducts, "You gathered but found no food.",
           "You gathered ");
}

// Name: Hunt()
// Description: Simulates hunting for creature drops. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random creature drop
//                 or reports none found.
void Hero::Hunt() {
    Gather(HuntProducts, "You hunted but found nothing.",
           "You hunted and got ");
}

// Name: Gather
// Description: Randomly selects an item from vector products passed.
//              If selection equals list size, prints 'noItemMsg';
//              otherwise prints foundMsg + item and adds it
//              to the hero's inventory.
// Preconditions: 'products' must contain valid item names.
// Postconditions: Inventory is incremented for the selected
//               item if found; message printed.
void Hero::Gather(const vector<string>& products, const string& noItemMsg,
                 const string& foundMsg) {
    size_t index = rand() % (products.size() + 1);

    if (index == products.size()) {
        cout << noItemMsg << endl;
    } else {
        string item = products[index];
        cout << foundMsg << item << "." << endl;
        CollectItem(item);
    }
}
