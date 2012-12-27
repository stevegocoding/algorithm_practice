#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

#define SAFE_DELETE(p) if (p) {delete (p); (p) = NULL; }

using namespace std;

struct linked_list_node
{
	linked_list_node(int _val) 
		: val(_val) 
		, next(NULL) 
	{}
	~linked_list_node()
	{
		// cout << "node: " << val << " has been deleted!" << endl; 
	}

	linked_list_node *next; 
	int val; 
};

linked_list_node* creat_linked_list(const vector<int>& data)
{
	if (data.empty()) 
		return NULL;
	
	linked_list_node *head_p = NULL; 
	linked_list_node *tail_p = NULL; 
	
	head_p = new linked_list_node(data.size()); 
	tail_p = head_p;  
	
	vector<int>::const_iterator it = data.begin(); 
	for (; it != data.end(); ++it)
	{
		linked_list_node *list_p = new linked_list_node(*it);
		tail_p->next = list_p; 
		tail_p = tail_p->next; 
	} 
	
	return head_p; 
}

void destroy_linked_list(linked_list_node *head)
{
	if (!head)
		return; 
	
	int size = head->val; 
	linked_list_node *cursor_p = head->next; 

	while (cursor_p)
	{
		linked_list_node *delete_p = cursor_p;
		cursor_p = cursor_p->next; 
		SAFE_DELETE(delete_p); 
	}
}

void print_linked_list(linked_list_node *head)
{
	if (!head)
	{
		cout << "Empty List! " << endl;
		return; 
	}
	linked_list_node *cursor_p = head->next;

	while (cursor_p)
	{
		cout << cursor_p->val << " "; 
		cursor_p = cursor_p->next;
	} 
}

linked_list_node* reverse_list_recursive(linked_list_node *head) 
{
	if (head == NULL) 
		return head; 
	
	if (head->next == NULL)
		return head;

	linked_list_node *reversed_head = reverse_list_recursive(head->next); 

	head->next->next = head; 
	head->next = NULL;
	return reversed_head;
}

linked_list_node* reverse_list_iterative(linked_list_node *head)
{
	if (head == NULL) 
		return NULL;

	if (head->next == NULL) 
		return head;

	linked_list_node *node_p = head;
	linked_list_node *prev_p = NULL; 
	linked_list_node *reversed_head = NULL; 

	while (node_p)
	{
		linked_list_node *next_p = node_p->next; 
		if (next_p == NULL)
			reversed_head = node_p; 
		
		node_p->next = prev_p;  
		node_p = next_p; 
		prev_p = node_p;  
	}
	return reversed_head; 
}


int main(int argc, char **argv) 
{
	ifstream ifs("ms100_08-3.in");
	vector<int> data_vec;
	copy(istream_iterator<int>(ifs), istream_iterator<int>(), back_inserter(data_vec));
	ifs.close(); 

	linked_list_node *head = creat_linked_list(data_vec);
	print_linked_list(head); 
	cout << endl; 
	destroy_linked_list(head); 
	
	return 0; 
}