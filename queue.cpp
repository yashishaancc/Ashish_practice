#include<iostream>
// using namespace std;

template <typename T>
struct Node{
	T val;
	Node* next;
};

template <typename T>
Node<T>* getNewNode(T val){
	Node<T>* node = (Node<T>*)malloc(sizeof(Node<T>));
	node->val = val;
	node->next = NULL;
	return node;
}

template <typename T>
class Queue{
	Node<T>* head, *tail;
public:
	Queue(){
		head = NULL;
		tail = NULL;
	}

	void push(T val){
		if(head == NULL){
			Node<T>* node = getNewNode(val);
			head = node;
			tail = node;
		}else{
			Node<T>* node = getNewNode(val);
			tail->next = node;
			tail = node;
		}
	}	

	T pop(){
		if(head == NULL)return -1;
		T to_return = head->val;
		Node<T>* next = head->next;
		free(head);
		head = next;
		return to_return;
	}

	bool isEmpty(){
		return head == NULL;
	}

	void print(){
		Node<T>* head = this->head;
		while(head != NULL){
			std::cout << head->val << ", ";
			head = head->next;
		}
		std::cout << std::endl;
	}

};

int main(){
    Queue<int> q_ints;
    Queue<char> q_chars;
    Queue<std::string> q_strings;
    q_ints.push(2);
    q_ints.push(8);
    q_ints.push(4);
    q_chars.push('c');
    q_chars.push('b');
    q_strings.push("this is a string");
    q_ints.print();
    q_chars.print();
    q_strings.print();
    int popped_value = q_ints.pop();
    
    // q.isEmpty();
    // q.size();
}