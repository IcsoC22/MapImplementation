#include <iostream>
#include <iterator>

using namespace std;

// Node Class
// Contains a key and an element, which contains the key and element of the node
// has a pointer to its right and left children as well as its parent

template <class T,class R>
class Node{
	T key;
	R element;

public:	
	Node *right;
	Node *left;
	Node *parent;

	//Default contructor, sets all pointers to NULL
	Node(){
		right = NULL;
		left = NULL;
		parent = NULL;
	}

	//Contructor which takes in a key and an element
	//sets key/element to the pair and all pointers to NULL
	Node(T k, R e){
		key = k;
		element = e;
		right = NULL;
		left = NULL;
		parent = NULL;
	}

	//Constructor which takes a refrence to another node
	//sets the key/element to that of the passed node
	//sets the pointers to those of the passed node 
	Node(Node<T,R>& n){
		key = n.get_Key();
		element = n.get_Element();
		right = n.get_Right();
		left = n.get_Left();
		parent = n.get_Parent();
	}
	
	//Destructor
	~Node(){
	}

	//Sets the key to k
	void set_Key(T k){
		key = k;
	}

	//Sets the element to e
	void set_Element(R e){
		element = e;
	}

	//sets the right pointer to r
	void set_Right(Node<T,R>* r){
		right = r;
	}

	//Sets the left pointer to l
	void set_Left(Node<T,R>* l){
		left = l;
	}
	
	//Sets the parent pointer to p
	void set_Parent(Node<T,R>* p){
		parent = p;
	}
	
	//Returns the key
	T get_Key(){
		return key;
	}
	
	//Returns the element
	R get_Element(){
		return element;
	}

	R& get_Element_Address(){
		return element;
	}

	//Returns the right pointer
	Node<T,R> * get_Right(){
		return right;
	}
	
	//Returns the left pointer
	Node<T,R> * get_Left(){
		return left;
	}

	//Returns the parent pointer
	Node<T,R> * get_Parent(){
		return parent;
	}

	//Returns the key_element pair
	pair<T,R> get_Pair(){
		return make_pair(key, element);
	}
};

//NodeIterator Class
//Contains a pointer to a node and functions to traverse a map
template <class T,class R>
class NodeIterator : public iterator<input_iterator_tag, Node<T,R> >{
	Node<T,R> * node;
public:
	//Default Contructor
	NodeIterator(){
	}

	//Constructor which takes a pointer to a node
	//sets the iterator pointer to the passed one
	NodeIterator(Node<T,R>* n){
		node = n;
	}

	//Tests if two iterators are equal 
	bool operator==(NodeIterator<T,R> n){
		return node == n.get_Node();
	}

	//Tests if two iterators are unequal
	bool operator!=(NodeIterator<T,R>  n){
		return node != n.get_Node();
	}

	//Increments the iterator to the next key value
	void  operator++(){
		if((*node).get_Right() != NULL){
			node = (*node).get_Right();
			while((*node).get_Left() != NULL){
				node = (*node).get_Left();
			}
		}
		else{
			Node<T,R> * y = (*node).get_Parent();
			while(y != NULL and (*y).get_Right()){
					node = y;
					y = (*node).get_Parent();	
			} 
			node = y;
		}
	}

	//Derefrences the iterator, returning a refrence to the key_element pair 
	pair<T,R> operator*(){
		return (*node).get_Pair();
	}
	
	//Sets the node pointer
	void set_Node(Node<T,R> * n){
		node = n;
	}

	//Retrieves the node pointer
	Node<T,R>* get_Node(){
		return node;
	}
	
};


//Map Class
//Contains a root node, an int representing the current size and a NodeIterator
template <class T, class R>
class Map{
	Node<T,R>* root;
	int s;

public:
	NodeIterator<T,R> itr;
	
	//Default Contructor
	//Calls the Node default constructor, set the iterator to the root
	//size = 0
	Map(){
		root = NULL;
		itr.set_Node(root);
		s = 0;
	}

	//Contructor which takes a node
	//sets the root to the node
	//sets the root parent to NULL
	//sets the iterator to the root
	//size = 1 
	Map(Node<T,R> n){
		root = &n;
		(*root).set_Parent(NULL);
		itr.set_Node(root);
		s = 1;
	}

	//Contructor which takes a refrence to a Map
	//sets root to that of the passed Map
	//sets iterator to the root
	//size = size of passed Map
	Map(Map<T,R>& m){
		root =m.get_Root();
		itr.set_Node(root);
		s = m.size();
	}

	//Destructor
	//Calls Node Destructor on Root 
	//sets s to 0
	~Map(){
		clear();
	}

	void clear(){
		if(root!=NULL){
			(*root).~Node<T,R>();	
		}
		s = 0;
	}

	//Returns the root of the Map
	Node<T,R>* get_Root(){
		return root;
	}

	//Sets the map equal to another map
	//root is the root of second map
	//s is the size of the second mao
	//itr set to root

	Map<T,R> operator=(Map<T,R> m){
		root = m.get_Root();
		s = m.size();
		itr.set_Node(root);
	}

	void set_Root(Node<T,R>* r){
		root = r;
	}

	void set_Size(int sz){
		s = sz;
	}	

	//returns the size of the map
	int size(){
		return s;	
	}

	//returns if the map is empty
	bool empty(){
		return (s == 0);
	}
	
	//Returns an iterator to the beginning of the map
	NodeIterator<T,R> begin(){
		return NodeIterator<T,R>(min(root));
	}

	//Returns an iterator to the end of the map
	NodeIterator<T,R> end(){
		return NodeIterator<T,R>(max(root));
	}
	
	//Returns a pointer to the node that is the min of the tree starting at x
	Node<T,R> * min(Node<T,R>* x){
		while((*x).get_Left() != NULL){
			x = (*x).get_Left();
		}
		return x;
	} 
	
	//Returns a pointer to the node that is the max of the tree starting at x
	Node<T,R> * max(Node<T,R>* x){
		while((*x).get_Right() != NULL){
			x = (*x).get_Right();
		}
		return x;
	}

	//Returns the amount of times a node with key k appears (1 or 0)
	int count(T k){
		Node<T,R> n = *root;
		while(1){
			if(k == n.get_Key()){
				return 1;
			}
			else if(k < n.get_Key()){
				if(n.get_Left() == NULL){
					return 0;
				}
				else{
					n=*(n.get_Left());
				}
			}
			else if(k > n.get_Key()){
				if(n.get_Right() == NULL){
					return 0;
				}
				else{
					n=*(n.get_Right());
				}
			}
		}	
	}

	//Swaps two maps
	void swap(Map<T,R>* m){
		Map<T,R> temp = *m;

		(*m).set_Root(root);
		(*m).set_Size(s);	

		root = temp.get_Root();
		s = temp.size();	
	} 

	//Inserts a pair into the map
	//Returns true if successful
	//Returns false if it fails, i.e. there is already a node with the key
	bool insert(Node<T,R> *z){
		if (root == NULL){
			root = z;
			s = 1;
			return true;
		}

		else{
			Node<T,R>* y = NULL;
			Node<T,R>* x = root;
			while(x!=NULL){
				y = x;
				if((*z).get_Key() == (*x).get_Key()){
					itr.set_Node(x);
					return false;
				}
				else if((*z).get_Key() < (*x).get_Key()){
					x = (*x).get_Left();
				}
				else if((*z).get_Key() > (*x).get_Key()){
					x = (*x).get_Right();
				}
			}

			if((*z).get_Key() < (*y).get_Key()){
				(*y).set_Left(z);
			} 
			
			if((*z).get_Key() > (*y).get_Key()){
				(*y).set_Right(z);
			} 
			
			(*z).set_Parent(y);
			s++;
			return true;
		}	
	}	

	//Indexing Operator
	//Returns a refrence to the element at the key specified and makes a node with said key if it does not already exist
	R& operator[](T k){
		Node<T,R>* x = root;
		Node<T,R>* y = NULL;
		while(x!=NULL){
			y = x;
			if(k == (*x).get_Key()){
				return (*x).get_Element_Address();
			}
			else if(k < (*x).get_Key()){
				cout<<"Left ";
				x = (*x).get_Left();
			}
			else if(k > (*x).get_Key()){
				cout<<"Right ";
				x = (*x).get_Right();
			}
		}
		Node<T,R> n;
		n.set_Key(k);
		if(k < (*y).get_Key()){
			(*y).set_Left(&n);
		} 
			
		if(k > (*y).get_Key()){
			(*y).set_Right(&n);
		} 
			
		n.set_Parent(y);
		s++;
		return n.get_Element_Address();

	}

	//Erases the element with key k, if it exists
	//Returns true if successful
	//Returns false if not, i.e. node with that key does not exist 
	bool erase(T k){
		Node<T,R>* x = root;
		while(x!=NULL){
			if(k == (*x).get_Key()){
				if((*x).get_Left()==NULL){
					transplant(x, (*x).right);
				}
				else if((*x).get_Right() == NULL){
					transplant(x, (*x).left);
				}
				else{
					Node<T,R> *y = min((*x).get_Right());
					if(y != (*x).get_Right()){
						transplant(y, (*y).right);
						(*y).set_Right((*x).get_Right());
						(*(*x).get_Right()).set_Parent(y);
					}
					transplant(x, y);
					(*y).set_Left((*x).get_Left());
					(*(*y).get_Left()).set_Parent(y);

					
				}
				
				s--;
				return true;
			}
			
			else if(k < (*x).get_Key()){
				x = (*x).get_Left();
			}

			else if(k > (*x).get_Key()){
				x = (*x).get_Right();
			}
		}
		
		return false;
	}

	//Erases the node at the given iterator
	//Returns an iterator pointing to the next node
	NodeIterator<T,R> erase(NodeIterator<T,R> i){
		Node<T,R>* x = i.get_Node();
			if((*x).get_Left()==NULL){
				transplant(x, (*x).right);
				s--;
				if((*x).right == NULL){
					NodeIterator<T,R> i(x);
					++i;
					return i; 
				}
				else return NodeIterator<T,R>((*x).right);
			}
			else if((*x).get_Right() == NULL){
				transplant(x, (*x).left);
				s--;
				if((*x).left== NULL){
					NodeIterator<T,R> a(x);
					++a;
					return a; 
				}
				else return NodeIterator<T,R>((*x).left);
			}
			else{
				Node<T,R> *y(min((*x).get_Right()));
				if(y != (*x).get_Right()){
					transplant(y, (*y).right);
					(*y).set_Right((*x).get_Right());
					(*(*x).get_Right()).set_Parent(y);
				}
				transplant(x, y);
				(*y).set_Left((*x).get_Left());
				(*(*y).get_Left()).set_Parent(y);
				s--;
				return NodeIterator<T,R>(y);
			}
	}
	
	//Used in Erase
	//Switches two nodes and their pointers where necessary
	void transplant(Node<T,R> *&u, Node<T,R> *&v){
		if(root == u){
			root = v;
			(*v).set_Parent(NULL);
		}
		
		else {
			Node<T,R>* q = (*u).get_Parent();
			if ((*q).get_Left() == u){
				(*q).set_Left(v);
			}
			else{
				(*q).set_Right(v);
			}
			if(v != NULL){
				(*v).set_Parent(q);
			}
		}
	}

	//Finds a node with key k
	//Returns an iterator pointing at that node or the end if no such key exists
	NodeIterator<T,R> find(T k){
		Node<T,R>* x = root;
		while(x != NULL){
			if(k == (*x).get_Key()){
				return NodeIterator<T,R>(x);
			}
			else if(k < (*x).get_Key()){
				x = (*x).get_Left();
			}

			else if(k > (*x).get_Key()){
				x = (*x).get_Right();
			}
		}
		return end();
	}

	
};



int main(){
 
Node <int,char> n(10, 'a');

//Map Class and NodeIterator Class Function Tests

//Default contructor 
cout<<"Map Contructors: \n";
Map<int, char> mp;	
if(mp.get_Root()==NULL){
	cout<<"Root is NULL"<<'\n';
}

//Node Contructor
// Size
Map<int, char> l(n);
cout<<(*(l.get_Root())).get_Key()<<" ";
cout<<(*(l.get_Root())).get_Element()<<" ";
cout<<l.size()<<'\n';

//Copy Contructor
Map<int, char> r(l);
cout<<(*(r.get_Root())).get_Key()<<" ";
cout<<(*(r.get_Root())).get_Element()<<" ";
cout<<r.size()<<'\n';

//empty
cout<<"Empty\n";
if(mp.empty()){
	cout<<"Map is empty"<<'\n';
}
if(!l.empty()){
	cout<<"Map is not empty"<<'\n';
}

//insert
cout<<"Insert\n";
Node<int,char> n1(4, 'g');
Node<int,char> n2(16, 'b');

if(!l.insert(&n1)){
	cout<<"error in insert\n";
}
if(!l.insert(&n2)){
	cout<<"error in insert\n";
} 

cout<<"Root: "<<(*(l.get_Root())).get_Key()<<" ";
cout<<(*(l.get_Root())).get_Element()<<" || ";
cout<<"Right: "<<(*((*(l.get_Root())).get_Right())).get_Key()<<" ";
cout<<(*((*(l.get_Root())).get_Right())).get_Element()<<" || ";
cout<<"Left: "<<(*((*(l.get_Root())).get_Left())).get_Key()<<" ";
cout<<(*((*(l.get_Root())).get_Left())).get_Element()<<" || ";
cout<<l.size()<<'\n';


//count
cout<<"Count\n";
cout<<l.count(5)<<'\n';
cout<<l.count(4)<<'\n';

//begin and end
//Node Iterator *
cout<<"Begin, End, and NodeIterator *\n";
cout<<(*(l.begin())).first<<'\n';
cout<<(*(l.end())).first<<'\n';

//Assignment Operator
cout<<"Assignment Operator\n";
mp = l;
cout<<(*(mp.get_Root())).get_Key()<<" ";
cout<<(*(mp.get_Root())).get_Element()<<" ";
cout<<mp.size()<<'\n';

//Indexing operator
cout<<"Indexing Operator\n";
cout<<l[4]<<'\n';

//Find
cout<<"Find\n";
cout<<(*(l.find(4))).first<<'\n';

//erase(key)
cout<<"Erase Key\n";
Node<int,char> n3(5, 'f');
Node<int,char> n4(2, 'd');
Node<int,char> n5(12, 'e');
Node<int,char> n6(20, 'u');

l.insert(&n3);
l.insert(&n4);
l.insert(&n5);
l.insert(&n6);

cout<<"Root: "<<(*(l.get_Root())).get_Key()<<" ";
cout<<(*(l.get_Root())).get_Element()<<"\n";
cout<<"Left: "<<(*((*(l.get_Root())).get_Left())).get_Key()<<" ";
cout<<(*((*(l.get_Root())).get_Left())).get_Element()<<" ||  ";
cout<<"Right: "<<(*((*(l.get_Root())).get_Right())).get_Key()<<" ";
cout<<(*((*(l.get_Root())).get_Right())).get_Element()<<"\n";

cout<<"Left Left: "<<(*(*((*(l.get_Root())).get_Left())).get_Left()).get_Key()<<" ";
cout<<(*(*((*(l.get_Root())).get_Left())).get_Left()).get_Element()<<" ||  ";
cout<<"Left Right: "<<(*(*((*(l.get_Root())).get_Left())).get_Right()).get_Key()<<" ";
cout<<(*(*((*(l.get_Root())).get_Left())).get_Right()).get_Element()<<" || ";

cout<<"Right Left: "<<(*(*((*(l.get_Root())).get_Right())).get_Left()).get_Key()<<" ";
cout<<(*(*((*(l.get_Root())).get_Left())).get_Left()).get_Element()<<" ||  ";
cout<<"Right Right: "<<(*(*((*(l.get_Root())).get_Right())).get_Right()).get_Key()<<" ";
cout<<(*(*((*(l.get_Root())).get_Right())).get_Right()).get_Element()<<"\n";

cout<<l.size()<<'\n';

l.erase(16); // (16, 'b') will be deleted and replaced by (20, 'u')


cout<<"Root: "<<(*(l.get_Root())).get_Key()<<" ";
cout<<(*(l.get_Root())).get_Element()<<"\n";
cout<<"Left: "<<(*((*(l.get_Root())).get_Left())).get_Key()<<" ";
cout<<(*((*(l.get_Root())).get_Left())).get_Element()<<" ||  ";
cout<<"Right: "<<(*((*(l.get_Root())).get_Right())).get_Key()<<" ";
cout<<(*((*(l.get_Root())).get_Right())).get_Element()<<"\n";

cout<<"Left Left: "<<(*(*((*(l.get_Root())).get_Left())).get_Left()).get_Key()<<" ";
cout<<(*(*((*(l.get_Root())).get_Left())).get_Left()).get_Element()<<" ||  ";
cout<<"Left Right: "<<(*(*((*(l.get_Root())).get_Left())).get_Right()).get_Key()<<" ";
cout<<(*(*((*(l.get_Root())).get_Left())).get_Right()).get_Element()<<" || ";

cout<<"Right Left: "<<(*(*((*(l.get_Root())).get_Right())).get_Left()).get_Key()<<" ";
cout<<(*(*((*(l.get_Root())).get_Left())).get_Left()).get_Element()<<"\n";

cout<<l.size()<<'\n';

//swap
cout<<"Swap\n";
l.swap(&mp);

cout<<(*(l.get_Root())).get_Key()<<" ";
cout<<(*(l.get_Root())).get_Element()<<" ";
cout<<l.size()<<'\n';
cout<<(*(mp.get_Root())).get_Key()<<" ";
cout<<(*(mp.get_Root())).get_Element()<<" ";
cout<<mp.size()<<'\n';

//NodeIterator ==, !=
cout<<"NodeIterator == and !=\n";
NodeIterator<int,char> itr1(&n4);
NodeIterator<int,char> itr2(&n1);
NodeIterator<int,char> itr3(&n4);

if(itr1 == itr3){
	cout<<"These are equal!\n";
}

if(itr1 != itr2){
	cout<<"These are not equal!\n";
}

//NodeIterator ++
cout<<"NodeIterator ++\n";
cout<<(*(l.itr)).first<<'\n';
++l.itr;
cout<<(*(l.itr)).first<<'\n';

//erase iterator
cout<<"Erase Iterator\n";
NodeIterator<int,char> itr (&n3);


cout<<"Root: "<<(*(mp.get_Root())).get_Key()<<" ";
cout<<(*(mp.get_Root())).get_Element()<<"\n";
cout<<"Left: "<<(*((*(mp.get_Root())).get_Left())).get_Key()<<" ";
cout<<(*((*(mp.get_Root())).get_Left())).get_Element()<<" ||  ";
cout<<"Right: "<<(*((*(l.get_Root())).get_Right())).get_Key()<<" ";
cout<<(*((*(mp.get_Root())).get_Right())).get_Element()<<"\n";

cout<<"Left Left: "<<(*(*((*(mp.get_Root())).get_Left())).get_Left()).get_Key()<<" ";
cout<<(*(*((*(mp.get_Root())).get_Left())).get_Left()).get_Element()<<" ||  ";
cout<<"Left Right: "<<(*(*((*(mp.get_Root())).get_Left())).get_Right()).get_Key()<<" ";
cout<<(*(*((*(mp.get_Root())).get_Left())).get_Right()).get_Element()<<" || ";

cout<<"Right Left: "<<(*(*((*(mp.get_Root())).get_Right())).get_Left()).get_Key()<<" ";
cout<<(*(*((*(mp.get_Root())).get_Left())).get_Left()).get_Element()<<"\n";

cout<<mp.size()<<'\n';

cout<<(*(mp.erase(itr))).first<<'\n';

cout<<"Root: "<<(*(mp.get_Root())).get_Key()<<" ";
cout<<(*(mp.get_Root())).get_Element()<<"\n";
cout<<"Left: "<<(*((*(mp.get_Root())).get_Left())).get_Key()<<" ";
cout<<(*((*(mp.get_Root())).get_Left())).get_Element()<<" ||  ";
cout<<"Right: "<<(*((*(l.get_Root())).get_Right())).get_Key()<<" ";
cout<<(*((*(mp.get_Root())).get_Right())).get_Element()<<"\n";

cout<<"Left Left: "<<(*(*((*(mp.get_Root())).get_Left())).get_Left()).get_Key()<<" ";
cout<<(*(*((*(mp.get_Root())).get_Left())).get_Left()).get_Element()<<" ||  ";

cout<<"Right Left: "<<(*(*((*(mp.get_Root())).get_Right())).get_Left()).get_Key()<<" ";
cout<<(*(*((*(mp.get_Root())).get_Left())).get_Left()).get_Element()<<"\n";

cout<<mp.size()<<'\n';

return  0;
}
