#include <iostream>
#include "priority_queue.h"

class c_elem 
{
public:	
	c_elem(int data)
		: m_data(data)
	{
		
	}

	int get_data() const
	{
		return m_data;
	}

private:
	int m_data; 
};

class c_compare_functor
{
public:
	int operator () (const c_elem& e1, const c_elem& e2)
	{
		return (e1.get_data() < e2.get_data()) ? -1 : 1;
	}
};


//////////////////////////////////////////////////////////////////////////
// TEST
////////////////////////////////////////////////////////////////////////// 

int main(int argc, char **argv)
{
	c_priority_queue<c_elem, c_compare_functor> pq;

	std::vector<c_elem> elems; 
	elems.push_back(c_elem(9));
	elems.push_back(c_elem(10));
	elems.push_back(c_elem(8));
	elems.push_back(c_elem(12));
	elems.push_back(c_elem(1));
	elems.push_back(c_elem(20));

	// Push elements to the queue
	for (unsigned int i = 0; i < elems.size(); ++i)
	{
		std::cout << "Push : " << elems[i].get_data() << std::endl; 
		pq.push(elems[i]);		
	}
	std::cout << std::endl; 
	
	// Test pop()
	while (pq.size() > 0)
	{
		std::cout << "Pop : " << pq.pop()->get_data() << std::endl; 
	}

	std::cout << std::endl; 
	
	// Add elements back for testing find() and remove()
	for (unsigned int i = 0; i < elems.size(); ++i)
	{
		std::cout << "Push : " << elems[i].get_data() << std::endl; 
		pq.push(elems[i]);		
	}

	std::cout << "Remove 1" << std::endl;

	// Remove 1
	pq.remove(elems[4]);

	while (pq.size() > 0)
	{
		std::cout << "Pop : " << pq.pop()->get_data() << std::endl; 
	}


	for (unsigned int i = 0; i < elems.size(); ++i)
	{
		std::cout << "Push : " << elems[i].get_data() << std::endl; 
		pq.push(elems[i]);		
	}

	
	std::cout << "Remove 12" << std::endl;

	// Remove 12
	pq.remove(elems[3]);


	while (pq.size() > 0)
	{
		std::cout << "Pop : " << pq.pop()->get_data() << std::endl; 
	}

	return 0;
}