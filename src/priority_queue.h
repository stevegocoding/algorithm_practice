#include <vector>
using namespace std;


template <class T, class Compare = less<typename vector<T>::value_type> >
class c_priority_queue
{
	typedef T elem_type;
	typedef T* elem_ptr;
	typedef typename vector<elem_ptr>::iterator pq_iterator;

public:
	explicit c_priority_queue()
		: m_end(0)
		, m_comp_functor(Compare())
	{	
	}

	~c_priority_queue()
	{
		// Release the vector's memory
		vector<elem_ptr>().swap(m_heap);
	}

	void push(T& value)
	{
		if (m_end >= (int)m_heap.size())
			m_heap.push_back(&value);
		else 
			m_heap[m_end] = &value;
		
		++m_end;
		
		heapify();
	}

	T* pop()
	{
		if (size() == 0)
			return NULL;
		
		std::swap(m_heap[0], m_heap[m_end-1]); 
		T *ret = m_heap[m_end-1]; 
		--m_end; 

		shift_down(0, m_end-1); 

		return ret; 
	}

	int size() const 
	{
		return m_end;
	}
	
	/** Part 4: new find() and remove() methods */ 

	/*
	 *	This method returns true if given key is found in the queue, otherwise returns false
	 */
	pq_iterator find(const T& key)
	{
		vector<elem_ptr>::iterator it = std::find(m_heap.begin(), m_heap.end(), &key); 
		return it;
	}

	void remove(const T& elem)
	{
		pq_iterator it; 
		if ((it = find(elem)) == m_heap.end())
			return; 

		std::swap(*it, m_heap[m_end-1]);
		--m_end; 
		
		// It the element being removed is the root, then we have to shift down to get the heap order back. 
		if (m_heap.begin() == it)
		{
			shift_down(0, m_end-1); 
		}
	}

private:

	void shift_up(int start, int end)
	{
		int child = end;
		int parent = -1; 
		while (child > start)
		{
			parent = (child - 1) / 2; 
			if (compare_elem(m_heap[child], m_heap[parent]) < 0)
			{
				std::swap(m_heap[parent], m_heap[child]); 
				child = parent; 
			}
			else 
				return; 
		}
	}

	void shift_down(int start, int end)
	{
		int root = start;
		while ((root * 2 + 1) <= end)
		{
			int child = root * 2 + 1; 
			int swap = root; 
			if (compare_elem(m_heap[child], m_heap[swap]) < 0)
				swap = child; 
			if (child + 1 <= end && compare_elem(m_heap[child+1], m_heap[swap]) < 0)
				swap = child + 1; 
			if (swap != root)
			{
				std::swap(m_heap[root], m_heap[swap]); 
				root = swap; 
			}
			else
				return; 
		}
	}

	void heapify()
	{
		int end = 1;	// first left child 
		while (end < m_end)
		{
			shift_up(0, end);
			end++; 
		}
	}

	int compare_elem(elem_ptr p1, elem_ptr p2)
	{
		return m_comp_functor(*p1, *p2); 
	}

private:

	vector<elem_ptr> m_heap; 
	Compare m_comp_functor;
	int m_end;
};