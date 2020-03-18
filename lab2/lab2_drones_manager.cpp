#include "lab2_drones_manager.hpp"
#include <iostream> // include iostream library for printing to console
#include <vector> // include vector library
#include <algorithm> // include algorithm library

// implement DroneManager empty constructor
DronesManager::DronesManager() : first(NULL), last(NULL), size(0) {}

// implement DroneManager destructor
DronesManager::~DronesManager() {
    // initialize temp pointer
    DroneRecord * searcher = first;

    // iterate through the linked list
    for (int i = 0; i < size; i++) {
        DroneRecord * temp;
        searcher = searcher -> next; // set searcher to next element
        temp = searcher -> prev; // set temp to previous element
        delete temp; // delete pointer at temp 
        temp = NULL; // set temp to NULL
    }

    // delete temp pointer, and set to null
    delete searcher;
    searcher = NULL;
}

// Compare two drone record instances; const objects cannot be modified so can only invoke const member functions
bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    bool is_equal = true;
    is_equal = is_equal && lhs.droneID == rhs.droneID;
    is_equal = is_equal && lhs.range == rhs.range;
    is_equal = is_equal && lhs.yearBought == rhs.yearBought;
    is_equal = is_equal && lhs.droneType == rhs.droneType;
    is_equal = is_equal && lhs.manufacturer == rhs.manufacturer;
    is_equal = is_equal && lhs.description == rhs.description;
    is_equal = is_equal && lhs.batteryType == rhs.batteryType;
    return is_equal;
}

// returns the number of elements in the list
unsigned int DronesManager::get_size() const {
    return size;
}

// checks if the list is empty; returns true if the list is empty, false otherwise
bool DronesManager::empty() const {
    if (!first) return true; // return true if pointer to first node is null
    return false;
}

// returns the value at the given index in the list
// if index is invalid, return last element; if index is empty, return DroneRecord(0);
DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if(!first) return DroneRecord(0); // return DroneRecord(0) if list is empty

    DroneRecord * selector = first; // initialize temporary pointer
    int counter = 0; // initialize counter variable

    // loop through list until specified index
    while (selector -> next && counter < index) { // ensure next index exists as well
        selector = selector -> next;
        counter++;
    }

    if (counter < index) { // if iterated to end of loop and index not reached, return end of list
        std::cout << "Index not found, beyond length of list." << std::endl;
        std::cout << "Returning value at end of list." << std::endl;
        return *selector;
    }

    // otherwise if index reached, return value at specified index
    std::cout << "Record at index was found." << std::endl;
    return *selector;
}

// search for the given value and returns the index of this value if found
unsigned int DronesManager::search(DroneRecord value) const {
    if (!first) return 0; // if list is empty, return 0

    int counter = 0; // initialize counter variable
    DroneRecord * searcher = first; // initialize searcher pointer

    // loop through list
    while (searcher->next) {
        // check if temp is equal to value 
        if (*searcher == value) return counter; // return index if found
        searcher = searcher->next; // set searcher pointer to next element in list
        counter++; // increment counter 
    }

    // else, return size of list
    std::cout << "Value was not found. Returning size of list" << std::endl;
    return size;
}

// prints all the elements in the list to the console
void DronesManager::print() const {
    DroneRecord * temp = first; // initialize temp pointer
    int counter = 1; // initialize counter variable

    // loop through list, print out each drone's attributes
    while (temp -> next) { 
        std::cout << "Drone #" << counter << " Attributes:" << std::endl;
        std::cout << "Drone ID: " << temp -> droneID << std::endl;
        std::cout << "Range: " << temp -> range << std::endl;
        std::cout << "Year Bought: " << temp -> yearBought << std::endl;
        std::cout << "Manufacturer: " << temp -> manufacturer << std::endl;
        std::cout << "Drone Type: " << temp -> droneType << std::endl;
        std::cout << "Battery Type: " << temp -> batteryType << std::endl;
        std::cout << "Description: " << temp -> description << std::endl;

        temp = temp -> next; // set temp pointer to next element in list
        counter++; // increment counter
    }
}

// inserts a value into the list at a given index; the list is not sorted
// if the index is invalid, insertion is rejected
bool DronesManager::insert(DroneRecord value, unsigned int index) {
    // initialize pointer variables
    DroneRecord* temp1 = new DroneRecord();
    DroneRecord* temp2 = new DroneRecord();
    *temp1 = value; // set temp1 pointer to value input
    temp2 = first; // set temp2 pointer to first

    // if index is 0 use insert_front function
    if (index == 0) {
        return this -> insert_front(value);
    } else if (index > size) { // if index is greater than size, return false
        return false;
    }

    // loop through list to correct index
    for (int i = 0; i < index - 2; i++) {
        // temp2 will point to index - 1 node when the loop finishes
        temp2 = temp2 -> next;
    }
    
    // insert value into list
    temp1 -> next = temp2 -> next; // set value next pointer equal to list index next
    temp1 -> prev = temp2; // set value prev pointer to temp2
    temp2 -> next = temp1; // set temp2 next pointer to temp1

    // check if element after temp1 insetion exists
    if (temp2 -> next -> next) {
        temp2 = temp2 -> next -> next; // set temp2 to the element after temp1
        temp2 -> prev = temp1; // set the prev pointer of that element to temp1
    }

    // increment size, return true
    size++;
    return true;
}

// insert value at the front of the list
bool DronesManager::insert_front(DroneRecord value) {
    // initialize temp pointer
    DroneRecord* temp = new DroneRecord();
    *temp = value; // set temp to value

    // point temp to first
    temp -> next = first;
    first = temp; // set first to temp

    // if last not set, set last to temp
    if (!last) last = temp;

    // increment size, and return true
    size++;
    return true;
}

// insert value at the back of the list
bool DronesManager::insert_back(DroneRecord value) {
    //initialize the temp pointer
    DroneRecord * temp = new DroneRecord();
    *temp = value;

    // set temp next pointer to null
    temp -> next = NULL;

    // set temp prev pointer to last node
    temp -> prev = last;
    last = temp; // set last node to temp

    // if first is not set, set first to temp
    if (!first) first = temp;

    // increment size and return true
    size++;
	return true;
}

// remove list element at specified index
bool DronesManager::remove(unsigned int index) {
    // initialize temp pointers
    DroneRecord * temp = first;
    DroneRecord * temp_prev;
    int counter = 0; // initialize counter variable

    // return false if list is empty
    if (!first) return false;

    // return false if index is beyond list
    if (index > size) return false;

    // loop through list
    while (temp -> next && counter < index) {
        temp = temp -> next;
        counter++;
    }
    
    temp_prev = temp -> prev; // set temp_prev to temp prev pointer
    temp_prev -> next = temp -> next; // set temp_prev next to temp next pointer
    temp -> next -> prev = temp -> prev; // set next prev pointer to temp prev

    temp -> next = NULL; // set temp pointer attributes to null
    temp -> prev = NULL;
    delete temp; // deallocate memory from temp
    temp = NULL; // set temp to null

    // return true
	return true;
}

// remove first element of list
bool DronesManager::remove_front() {
    // if list is empty return false
    if (!first) return false;

    // initialize temp pointer
    DroneRecord * temp = new DroneRecord();
    DroneRecord * temp1 = new DroneRecord();

    // set temp to the second pointer in the list
    temp = first -> next;
    temp -> prev = NULL; // set the second prev pointer to null

    // set temp1 to first
    temp1 = first;

    // set the first next node to null
    first -> next = NULL;
    
    first = temp; // set first pointer to temp pointer

    // delete pointer that was originally pointing to the first pointer
    delete temp1;
    temp1 = NULL;

    // return true
	return true;
}

// remove last element of list
bool DronesManager::remove_back() {
    // if list is empty return false
	if (!first) return false;

    // initialize temp pointer
    DroneRecord * temp = new DroneRecord();
    DroneRecord * temp1 = new DroneRecord();

    // set temp to the second pointer in the list
    temp = last -> prev;
    temp -> next = NULL; // set the second prev pointer to null

    // set temp1 to last
    temp1 = last;

    // set the last prev pointer to null
    last -> prev = NULL;
    
    last = temp; // set last pointer to temp pointer

    // delete pointer that was originally pointing to the first pointer
    delete temp1;
    temp1 = NULL;

    // return true
	return true;
}

// replaces the value at the given index with the given value; the list is not sorted
// if the index is invalid, the replacement is rejected
bool DronesManager::replace(unsigned int index, DroneRecord value) {
    // initialize temp pointer
    DroneRecord * temp = new DroneRecord();

    //initialize the temp pointer
    *temp = value;
    temp -> next = NULL;

    // if index is greater than size, return false
    if (index > size){
        return false;
    }

    // loop through list until index
    for (int i = 0; i < index; i++){
        temp = temp -> next;
    }

    // set value at temp to inputted value
    *temp = value;
	return true;
}

//reverses the linked list
bool DronesManager::reverse_list() {
    if (!first) return false;

    // initialize temp pointers
    DroneRecord * temp1 = last;
    DroneRecord * temp2 = first; 

    // loop through list
    while (temp1 -> prev) {
        *temp2 = *temp1; // set value of temp1 to value of temp
        temp1 = temp1 -> prev; // set temp to prev
        temp2 = temp2 -> next; // set temp1 to next
    }

    // return true
    return true;
}

// returns true if the list is sorted in ascending order
bool DronesManagerSorted::is_sorted_asc() const {
    // initialize temp pointer
    DroneRecord * temp = first;

    // loop through list
    while (temp -> next){
        // check if two consecutive elements are correctly sorted
        // if they are not, return false
        if (temp -> droneID < temp -> prev -> droneID) {
            return false;
        }
    }

    // else return true
    return true;
}

// returns true if the list is sorted in descending order
bool DronesManagerSorted::is_sorted_desc() const {
    // initialize temp pointer
    DroneRecord * temp = first;

    while (temp -> next){
        // check if two consecutive elements are correctly sorted
        // if they are not, return false
        if (temp -> droneID > temp -> prev -> droneID) {
            return false;
        }
    }

    // else return true
    return true;
}

// inserts a value so that the list remains sorted in ascending order
bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    if (!(this->is_sorted_asc())) return false;

    DroneRecord * temp = first;
    bool check = false;
    int counter = 0;

    while(counter < size && !check) {
        if (val.droneID >= temp -> droneID) check = true;
        counter++;
    }

    this -> insert(val, counter);
    
	return true;
}

// inserts a value so that the list remains sorted in descending order
bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    if (!(this->is_sorted_desc())) return false;

    DroneRecord * temp = first;
    bool check = false;
    int counter = 0;

    while(counter < size && !check) {
        if (val.droneID <= temp -> droneID) check = true;
        else counter++;
    }

    this -> insert(val, counter);
    
	return true;
}

void DronesManagerSorted::sort_asc() {
    std::vector<unsigned int> drone_ids;
    DroneRecord * temp = first;

    while (temp -> next) {
        drone_ids.push_back(temp -> droneID);
        temp -> next;
    }

    std::sort(drone_ids.begin(), drone_ids.end());

    temp = first;

    for (int i = 0; temp -> next; i++) {
        *temp = drone_ids[i];
        temp = temp -> next;
    }
}
    
void DronesManagerSorted::sort_desc() {
    std::vector<unsigned int> drone_ids;
    DroneRecord * temp = first;

    while (temp -> next) {
        drone_ids.push_back(temp -> droneID);
        temp -> next;
    }

    std::sort(drone_ids.begin(), drone_ids.end(), greater<int>());

    temp = first;

    for (int i = 0; temp -> next; i++) {
        *temp = drone_ids[i];
        temp = temp -> next;
    }
}
