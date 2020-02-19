#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
        ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
	    return true;
	}
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		DronesManager manager3;

		// 4 members in the class
		manager3.insert_front(100);
		manager3.insert(5,1);
		manager3.insert(10,2);
		manager3.insert(14,3);

		// test
		ASSERT_TRUE(manager3.select(0) == 100)
		ASSERT_TRUE(manager3.select(1) == 5)
        ASSERT_TRUE(manager3.select(2) == 10)
		ASSERT_TRUE(manager3.search(14) == 3)
        ASSERT_TRUE(manager3.search(5) == 1)
	    return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
	    DronesManager manager4;
	    // 6 members to begin with
	    manager4.insert_front(50);
	    manager4.insert(20,1);
	    manager4.insert(30,2);
	    manager4.insert(60,3);
	    manager4.insert(90,4);
	    manager4.insert_back(59);

	    // four members remaining
	    manager4.remove_front();
	    manager4.remove_back();

	    // test
	    ASSERT_TRUE(manager4.select(0) == 20)
	    ASSERT_TRUE(manager4.select(1) == 30)
	    ASSERT_TRUE(manager4.select(2) == 60)
	    ASSERT_TRUE(manager4.select(3) == 90)
	    return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
	    DronesManager manager5;

	    // 5 members in the class
	    manager5.insert_front(90);
	    manager5.insert(350,1);
	    manager5.insert(960,2);
	    manager5.insert(310,3);
	    manager5.insert(270,4);

	    // replace members
	    manager5.replace(1,300);
	    manager5.replace(2,500);
	    manager5.replace(3,700);
	    manager5.replace(4,800);

	    // reverse list; now list is in the order of 800,700,500,300,90
	    manager5.reverse_list();

	    // test
	    ASSERT_TRUE(manager5.search(90) == 4)
        ASSERT_TRUE(manager5.search(800) == 0)
        ASSERT_TRUE(manager5.search(300) == 3)
        ASSERT_TRUE(manager5. search(700) == 1)
        ASSERT_FALSE(manager5. search(270) == 0)
        ASSERT_FALSE(manager5. search(90) == 0)
        ASSERT_FALSE(manager5.search(90) == 1)
	    ASSERT_FALSE(manager5.search(300) == 2)
	    return true;
	}


	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
	    DronesManager manager6;

	    // front insertion and output in the order of 40,30,20,10
	    manager6.insert_front(10);
	    manager6.insert_front(20);
	    manager6.insert_front(30);
	    manager6.insert_front(40);

	    ASSERT_TRUE(manager6.search(10) == 3)
	    ASSERT_TRUE(manager6.search(20) == 2)
        ASSERT_TRUE(manager6.search(30) == 1)
        ASSERT_TRUE(manager6.search(40) == 0)

	    return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
	    DronesManager manager7;

	    // the class contains 10,90,60,20,70
	    manager7.insert_front(10);
	    manager7.insert(90,1);
	    manager7.insert(60,2);
	    manager7.insert(20,3);
	    manager7.insert_back(70);

	    // insert at different positions
	    manager7.insert(100,1); //now should be 10,100,90,60,20,70
	    manager7.insert(400,3); //now should be 10,100,90,400,60,20,70
	    manager7.insert(700,5); // now should be 10,100,90,400,60,700,20,70
	    manager7.insert(900,8); // should be inserted at the end

	    // test
	    ASSERT_TRUE(manager7.get_size() == 9)
	    ASSERT_TRUE(manager7.search(900) == 8)
	    ASSERT_TRUE(manager7.search(90) == 2)
	    ASSERT_TRUE(manager7.search(60) == 4)
        ASSERT_FALSE(manager7.search(20) == 3)
        ASSERT_FALSE(manager7.search(70) == 4)
        ASSERT_TRUE(manager7.first->prev == NULL && manager7.last->next == NULL)
        ASSERT_TRUE(manager7.first->prev == NULL && manager7.last->next == NULL)
	    return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
	    DronesManager manager8;

	    // insert elements into the class
	    manager8.insert_front(10);
	    manager8.insert(120,1);
	    manager8.insert(170,2);

	    // remove too many elements
	    manager8.remove(0);
	    manager8.remove(1);
	    manager8.remove(2);
	    manager8.remove(3); //member does not exist

	    // test
	    ASSERT_TRUE(manager8.get_size() == 0)
	    ASSERT_TRUE(manager8.empty() == true)

	    // add more elements
	    manager8.insert(500,0);
	    manager8.insert(300,1);
	    manager8.insert(600,2);
	    manager8.insert_back(1000);

	    // test
	    ASSERT_TRUE(manager8.search(500) == 0)
	    ASSERT_TRUE(manager8.search(600) == 2)
	    ASSERT_TRUE(manager8.search(1000) == 3)
	    ASSERT_TRUE(manager8.get_size() == 4)
	    return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
	    DronesManager manager9;

	    // the class contains 20,30,40,50,60,70
	    manager9.insert_front(20);
	    manager9.insert(30,1);
	    manager9.insert(40, 2);
	    manager9.insert(50,3);
        manager9.insert(60,4);
        manager9.insert(70,5);
        manager9.insert(80,10); // should be invalid
        manager9.insert(700,12); // should be invalid

        manager9.remove(1);// 30 removed
        manager9.remove(2); // 40 removed
        manager9.remove(3); // 50 removed
        manager9.remove(10); // should be invalid

        // the class now contains 20,60,70
        ASSERT_TRUE(manager9.search(20) == 0)
        ASSERT_TRUE(manager9.search(60) == 1)
        ASSERT_TRUE(manager9.search(70) == 2)
        ASSERT_TRUE(manager9.get_size() == 3)
		return true;
	}
	    	
	// PURPOSE: inserts into an unsorted list, then sort the list
	bool test10() {
	    DronesManagerSorted manager10;

	    // make a list first
	    manager10.insert(100,0);
	    manager10.insert(300,1);
	    manager10.insert(200,2);
	    manager10.insert(400,3);

	    // insert into an unsorted list
	    manager10.insert(500,2);
	    manager10.insert(600,1);

	    // sort the list in ascending order
	    manager10.sort_asc();

	    // the list should be sorted as 100,200 ... 700

	    // test
	    ASSERT_TRUE(manager10.search(100) == 0)
	    ASSERT_TRUE(manager10.search(200) == 1)
	    ASSERT_TRUE(manager10.search(500) == 4)
	    ASSERT_TRUE(manager10.search(700) == 6)
	    ASSERT_TRUE(manager10.get_size() == 7)
	    ASSERT_TRUE(manager10.is_sorted_asc() == true)

	    // sort the list in descending order
	    manager10.sort_desc();

	    // test
	    ASSERT_TRUE(manager10.search(700) == 0)
	    ASSERT_TRUE(manager10.search(600) == 1)
	    ASSERT_TRUE(manager10.search(500) == 2)
	    ASSERT_TRUE(manager10.search(100) == 7)
	    ASSERT_TRUE(manager10.is_sorted_desc() == true)

	    return true;
	}  
	
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
	    DronesManagerSorted manager11;

	    // make an ascending list
	    //manager11.insert(10,0);
	    //manager11.insert(40,1);
	    //manager11.insert(70,2);

	    // insert into the ascending list
	    manager11.insert_sorted_asc(20);
	    manager11.insert_sorted_asc(50);
	    manager11.insert_sorted_asc(90);

	    // should be sorted in the order 10,20,40,50,70,90

	    // test
	    ASSERT_TRUE(manager11.is_sorted_asc() == true)
	    ASSERT_TRUE(manager11.search(0) == 10)
	    ASSERT_TRUE(manager11.search(3) == 50)

	    // remove the sorted ascending list elements
	    manager11.remove(6);
	    manager11.remove(5);

	    // test
	    ASSERT_TRUE(manager11.search(50) == 3)
	    ASSERT_TRUE(manager11.search(20) == 1)
	    ASSERT_TRUE(manager11.is_sorted_asc() == true)

	    return true;
	}
	
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
	    DronesManagerSorted manager12;

	    // make a descending list
	    manager12.insert(90,0);
	    manager12.insert(60,1);
	    manager12.insert(30,2);

	    // insert into the descending list
	    manager12.insert_sorted_desc(50);
	    manager12.insert_sorted_desc(40);
	    manager12.insert_sorted_desc(10);

	    // should be sorted as 90,60,50,40,30,10

	    // test
	    ASSERT_TRUE(manager12.search(10) == 5)
	    ASSERT_TRUE(manager12.search(60) == 1)
	    ASSERT_TRUE(manager12.search(50) == 2)
	    ASSERT_TRUE(manager12.is_sorted_desc() == true)

	    // remove elements
	    manager12.remove(1);
	    manager12.remove(3);

	    // the list should now be 90,50,40,10

	    // test
	    ASSERT_TRUE(manager12.search(50) == 1)
	    ASSERT_TRUE(manager12.search(40) == 2)
	    ASSERT_TRUE(manager12.is_sorted_desc() == true)

	    return true;
	}  
};

#endif
