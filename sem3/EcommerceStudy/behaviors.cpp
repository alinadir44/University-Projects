#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>
#include<string>
#include<map>
#define MAX 700000
using namespace std;

class DynArrInt
{
	private:
		int* arr;
		int size;
		int capacity;
		
	public:
		enum { SPARE_CAPACITY = 10 };
		
		// Constructor
		DynArrInt(int size_=0){
			// Todo: check size can be zero or negative
			size = size_;
			capacity  = size + SPARE_CAPACITY;
			arr = new(nothrow) int[capacity];
			
			for (int i=0;i<size;i++){
				arr[i] = 0;
			}
		}
		
		// Copy constructor
		DynArrInt(const DynArrInt& otherObject){
			size= otherObject.size;
			capacity = otherObject.capacity;
			
			arr = new(nothrow) int[capacity];
			for(int i=0;i<size;i++){
				arr[i] = otherObject.arr[i];
			}
		}
		
		// Assignment operator
		DynArrInt& operator=(const DynArrInt& rightObject){
			if (this != &rightObject){
				size = rightObject.size;
				capacity = rightObject.capacity;
				
				delete [] arr;
				arr = new(nothrow) int[capacity];
				for (int i=0;i<size;i++){
					arr[i] = rightObject.arr[i];
				}
			}
			return *this;
		}
		
		// Access operator
		int& operator[](int index){
			if (index < 0 || index >= size){
				throw ("Exception: Index out of bound!");
			}
			return arr[index];
		}
		
		// Equal to operator
		bool operator==(DynArrInt& rightObject)  {
		  	if (rightObject.size != size) return false;
		
		  	for (int i = 0; i < rightObject.size; i++) {
		    	if (rightObject[i] != arr[i]) return false;
		  }
		  return true;
		}
		
		// Not equal to operator
		bool operator!=(DynArrInt& rightObject)  {
		  	if (rightObject.size != size) return true;
		
		  	for (int i = 0; i < rightObject.size; i++) {
		    	if (rightObject[i] != arr[i]) return true;
		  }
		  return false;
			// alternatively,
			// return !(*this == rightObject);
		}
		
		// Destructor
		~DynArrInt(){
			delete [] arr;
		}
		
		// PushBack
		void pushBack(int val){
			if(size == capacity){
				int* new_arr = new(nothrow) int[2*capacity];
				for (int i=0;i<size;i++){
					new_arr[i] = arr[i];
				}
				delete [] arr;
				arr = new_arr;
				capacity = 2*capacity;
			}
			arr[size++]=val;
			// the above is same as,
			// arr[size] = val; 
			// size += 1;
		}
		
		// Get
		int get(int index){
			if(index < 0 || index >= size){
				throw ("Exception: Index out of bound!");
			}
			return arr[index];
		}
		
		// Set
		void set(int val, int index){
			if(index < 0 || index >= size){
				throw ("Exception: Index out of bound!");
			}
			arr[index] = val;
		}
		
		// Remove
		void remove(int index){
			if(index <0 || index >= size){
				throw ("Exception: Index out of bound!");
			}
			for (int i=index;i<size-1;i++){
				arr[i] = arr[i+1];
			}
			size -= 1;
		}
		
		// Size
		int getSize(){
			return size;
		}
		
		// print array
		void printArray(){
			for (int i=0;i< size;i++){
				cout<<arr[i]<<",";
			}
			cout<<endl;
		}
};

class Data{
	public:
	friend class AVLNode;
	int product_id;
	long long int category_id;
	int user_id;
	string event_time;
	string event_type;
	string category_code;
	string brand;
	float price;
	string user_session;
	Data()
	{
		
	}
	void setitems(int pid,long long int cid,int uid,string etime,string etype,string cc,string br,float pr,string session)
	{
		product_id=pid;
		category_id=cid;
		user_id=uid;
		event_time=etime;
		event_type=etype;
		category_code=cc;
		brand=br;
		price=pr;
		user_session=session;	
	}
	
	void setitems(Data data1)
	{
		this->brand=data1.brand;
		this->category_code=data1.category_code;
		this->category_id=data1.category_id;
		this->event_time=data1.event_time;
		this->event_type=data1.event_type;
		this->price=data1.price;
		this->product_id=data1.product_id;
		this->user_id=data1.user_id;
		this->user_session=data1.user_session;
	}
	void displayitems()
	{
		cout<<endl<<endl<<product_id<<"\t"
		<<category_id<<"\t"
		<<user_id<<"\t"
		<<event_time<<"\t"
		<<event_type<<"\t"
		<<category_code<<"\t"
		<<brand<<"\t"
		<<price<<"\t"
		<<user_session<<"\n\n";
	}
};

class listnode{
	public:
	int key;
	listnode* next;
	Data d1;
	
	listnode()
	{
		next=NULL;
	}
	
	listnode(int d)
	{
		key=d;
		next=NULL;
	}
};

class AVLNode
{
    friend class AVLTree;

public:
    int key_;
    int pcount;
    int height_;
    Data data;
	listnode *head;
    AVLNode* left_node_;
    AVLNode* right_node_;
	
	AVLNode()
	{
		
	}
	
	AVLNode(int key)
	{
		key_= key;
        left_node_ = NULL;
        right_node_ = NULL;
        height_ = 0;
        head=NULL;
        pcount=1;
	}
	
    AVLNode(int key,int pid,long long int cid,int uid,string etime,string etype,string cc,string br,float pr,string session)
    {
        key_= key;
        left_node_ = NULL;
        right_node_ = NULL;
        height_ = 0;
        data.setitems(pid,cid,uid,etime,etype,cc,br,pr,session);
        head=NULL;
        pcount=1;
    }
    
    void addtolist(AVLNode* node1)
    {
    	listnode* temp=new listnode(node1->key_);
    	temp->key=node1->key_;
    	temp->d1.setitems(node1->data);
    	temp->next=NULL;
		
		if(head==NULL)
    	{
			head=temp;
		}
		else
		{
			listnode* t1;
			t1=head;
			while(t1->next!=NULL)
			{
				t1=t1->next;
			}
			t1->next=temp;
		}
		pcount++;
	}
    
    ~AVLNode()
    {

    }
};

class AVLTree
{
private:
    AVLNode* root_;

    AVLNode* right_rotation(AVLNode* p)
    {
        AVLNode* new_p = p->left_node_;
        p->left_node_ = new_p->right_node_;
        new_p->right_node_ = p;

        p->height_ = max(sub_tree_height(p->left_node_), sub_tree_height(p->right_node_));
        new_p->height_ = max(sub_tree_height(new_p->left_node_), sub_tree_height(new_p->right_node_));

        return new_p;
    }

    AVLNode* left_rotation(AVLNode* p)
    {
        AVLNode* new_p = p->right_node_;
        p->right_node_ = new_p->left_node_;
        new_p->left_node_ = p;

        p->height_ = max(sub_tree_height(p->left_node_), sub_tree_height(p->right_node_));
        new_p->height_ = max(sub_tree_height(new_p->left_node_), sub_tree_height(new_p->right_node_));

        return new_p;
    }

    AVLNode* maximum_node_of_tree(AVLNode* node)
    {
        if(node->right_node_ == nullptr) return node;
        else return maximum_node_of_tree(node->right_node_);
    }

    int sub_tree_height(AVLNode* node)
    {
        return (node != nullptr)?node->height_ + 1:0;
    }

    AVLNode* insert_(int key, AVLNode* node)
    {
        if(node == nullptr)
        {
            return node = new AVLNode(key);
        }

        if(key < node->key_) 
        {
            node->left_node_ = insert_(key, node->left_node_);
        }
        else if(key > node->key_) 
        {
            node->right_node_ = insert_(key, node->right_node_);
        }
        else if(node->key_ == key)
		{
			AVLNode* anode= new AVLNode(key);
			node->addtolist(anode);
			return node;	
		}

        int height_L = sub_tree_height(node->left_node_);
        int height_R = sub_tree_height(node->right_node_);

        node->height_ = max(height_L, height_R);
        
        int balance_factor = height_L - height_R;

        if(balance_factor > 1)//L
        {
            if(key < node->left_node_->key_)//L
            {
                return node = right_rotation(node);
            }
            else//R
            {
                node->left_node_ = left_rotation(node->left_node_);
                return node = right_rotation(node);
            }
        }
        else if(balance_factor < -1)//R
        {
            if(key < node->right_node_->key_)//L
            {
                node->right_node_ = right_rotation(node->right_node_);
                return node = left_rotation(node);
            }
            else//R
            {
                return node = left_rotation(node);
            }
        }

        return node;
    }
    
    AVLNode* insert_(int key,int pid,long long int cid,int uid,string etime,string etype,string cc,string br,float pr,string session, AVLNode* node)
    {
        if(node == nullptr)
        {
            return node = new AVLNode(key,pid,cid,uid,etime,etype,cc,br,pr,session);
        }

        if(key < node->key_) 
        {
            node->left_node_ = insert_(key,pid,cid,uid,etime,etype,cc,br,pr,session,node->left_node_);
        }
        else if(key > node->key_) 
        {
            node->right_node_ = insert_(key,pid,cid,uid,etime,etype,cc,br,pr,session,node->right_node_);
        }
        else if(node->key_ == key)
		{
			AVLNode* anode= new AVLNode(key,pid,cid,uid,etime,etype,cc,br,pr,session);
			node->addtolist(anode);
			return node;	
		}

        int height_L = sub_tree_height(node->left_node_);
        int height_R = sub_tree_height(node->right_node_);

        node->height_ = max(height_L, height_R);
        
        int balance_factor = height_L - height_R;

        if(balance_factor > 1)//L
        {
            if(key < node->left_node_->key_)//L
            {
                return node = right_rotation(node);
            }
            else//R
            {
                node->left_node_ = left_rotation(node->left_node_);
                return node = right_rotation(node);
            }
        }
        else if(balance_factor < -1)//R
        {
            if(key < node->right_node_->key_)//L
            {
                node->right_node_ = right_rotation(node->right_node_);
                return node = left_rotation(node);
            }
            else//R
            {
                return node = left_rotation(node);
            }
        }

        return node;
    }

    AVLNode* pop_(int key, AVLNode* node)
    {
        if(node == nullptr) return nullptr;

        if(key < node->key_) 
        {
            node->left_node_ = pop_(key, node->left_node_);
        }
        else if(key > node->key_) 
        {
            node->right_node_ = pop_(key, node->right_node_);
        }
        else //if(node->key_ == key) 
        {
            if(node->left_node_ == nullptr && node->right_node_ == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if(node->left_node_ == nullptr && node->right_node_ != nullptr)
            {
                AVLNode* sub_right_tree = node->right_node_;
                delete node;
                return sub_right_tree;
            }
            else if(node->left_node_ != nullptr && node->right_node_ == nullptr)
            {
                AVLNode* sub_left_tree = node->left_node_;
                delete node;
                return sub_left_tree;
            }
            else            
            {
                AVLNode* maxium_node_in_sub_left_tree = maximum_node_of_tree(node->left_node_);
                node->key_ = maxium_node_in_sub_left_tree->key_;
                node->left_node_ = pop_(maxium_node_in_sub_left_tree->key_, node->left_node_);
            }
        }

        int height_L = sub_tree_height(node->left_node_);
        int height_R = sub_tree_height(node->right_node_);

        node->height_ = max(height_L, height_R);
        
        int balance_factor = height_L - height_R;

        if(balance_factor > 1)//L
        {
            if(sub_tree_height(node->left_node_->left_node_) > sub_tree_height(node->left_node_->right_node_))//L
            {
                return node = right_rotation(node);
            }
            else//R
            {
                node->left_node_ = left_rotation(node->left_node_);
                return node = right_rotation(node);
            }
        }
        else if(balance_factor < -1)//R
        {
            if(sub_tree_height(node->right_node_->left_node_) > sub_tree_height(node->right_node_->right_node_))//L
            {
                node->right_node_ = right_rotation(node->right_node_);
                return node = left_rotation(node);
            }
            else//R
            {
                return node = left_rotation(node);
            }
        }

        return node;
    }

public:

    AVLTree()
    {
        root_ = nullptr;
    }

    ~AVLTree()
    {

    }

    void insert(int key)
    {
        root_ = insert_(key, root_);
    }

	void insert(int key,int pid,long long int cid,int uid,string etime,string etype,string cc,string br,float pr,string session)
	{
		root_=insert_(key,pid,cid,uid,etime,etype,cc,br,pr,session,root_);
	}
    void pop(int key)
    {
        root_ = pop_(key, root_);
    }
    
    AVLNode* getroot()
    {
    	return root_;
	}
};

class Node{
public:
long long int data;
string ccode;
int pcount;
Node *left;
Node *right;
Node()
{
	pcount=1;
	left=NULL;
	right=NULL;
}
Node(long long int d,string cc,Node *l,Node *r)
{
data=d;
left=l;
right=r;
pcount=1;
ccode=cc;
}

void increment()
{
	pcount++;
}
};

class bst{

public:
Node *root;
bst()
{
root=NULL;
}
int addnode(long long int val,string cc)
{
Node *temp=new Node(val,cc,NULL,NULL);
Node *current,*parent;
if(root==NULL)
{
root=temp;
return 1;
}
current=root;
parent=NULL;
while(1)
{
parent=current;
if(val<parent->data)
{
current=current->left;
if(current==NULL)
{
parent->left=temp;
return 1;
}
}
else if(val>parent->data)
{
current=current->right;
if(current==NULL)
{
parent->right=temp;
return 1;
}
}
else
{
	parent->increment();
	return 1;
}
}


}


int searchtree(long long int k1)
{
	Node *curr,*p;
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		curr=root;
		while(curr!=NULL)
		{
			if(curr->data==k1)
			{
				return 1;
			}
			else if(k1<curr->data)
			{
				curr=curr->left;
			}
			else if(k1>curr->data)
			{
				curr=curr->right;
			}
		}
		return 0;
	}
}

};

class listnode1{
	public:
	long long int key;
	listnode1* next;
	Data d1;
	
	listnode1()
	{
		next=NULL;
	}
	
	listnode1(long long int d)
	{
		key=d;
		next=NULL;
	}
};

class avlnode
{
    friend class AVLTree1;

public:
    long long int key_;
    int pcount;
    int height_;
    Data data;
	listnode1 *head;
    avlnode* left_node_;
    avlnode* right_node_;
	
	avlnode()
	{
		head=NULL;
		left_node_ = NULL;
        right_node_ = NULL;
	}
	
	avlnode(long long int key)
	{
		key_= key;
        left_node_ = NULL;
        right_node_ = NULL;
        height_ = 0;
        head=NULL;
        pcount=1;
	}
	
    avlnode(avlnode* left_node, avlnode* right_node,int pid,long long int cid,int uid,string etime,string etype,string cc,string br,float pr,string session)
    {
        key_= cid;
        left_node_ = left_node;
        right_node_ = right_node;
        height_ = 0;
        data.setitems(pid,cid,uid,etime,etype,cc,br,pr,session);
        head=NULL;
        pcount=1;
    }
    
    void addtolist(avlnode* node1)
    {
    	listnode1* temp=new listnode1(node1->key_);
    	temp->key=node1->key_;
    	temp->d1.setitems(node1->data);
    	temp->next=NULL;
		
		if(head==NULL)
    	{
			head=temp;
		}
		else
		{
			listnode1* t1;
			t1=head;
			while(t1->next!=NULL)
			{
				t1=t1->next;
			}
			t1->next=temp;
		}
		pcount++;
	}
    
    ~avlnode()
    {

    }
};

class AVLTree1
{
private:
    avlnode* root_;

    avlnode* right_rotation(avlnode* p)
    {
        avlnode* new_p = p->left_node_;
        p->left_node_ = new_p->right_node_;
        new_p->right_node_ = p;

        p->height_ = max(sub_tree_height(p->left_node_), sub_tree_height(p->right_node_));
        new_p->height_ = max(sub_tree_height(new_p->left_node_), sub_tree_height(new_p->right_node_));

        return new_p;
    }

    avlnode* left_rotation(avlnode* p)
    {
        avlnode* new_p = p->right_node_;
        p->right_node_ = new_p->left_node_;
        new_p->left_node_ = p;

        p->height_ = max(sub_tree_height(p->left_node_), sub_tree_height(p->right_node_));
        new_p->height_ = max(sub_tree_height(new_p->left_node_), sub_tree_height(new_p->right_node_));

        return new_p;
    }

    avlnode* maximum_node_of_tree(avlnode* node)
    {
        if(node->right_node_ == nullptr) return node;
        else return maximum_node_of_tree(node->right_node_);
    }

    int sub_tree_height(avlnode* node)
    {
        return (node != nullptr)?node->height_ + 1:0;
    }

    avlnode* insert_(long long int key,avlnode* node)
    {
        if(node == nullptr)
        {
            return node = new avlnode(key);
        }

        if(key < node->key_) 
        {
            node->left_node_ = insert_(key, node->left_node_);
        }
        else if(key > node->key_) 
        {
            node->right_node_ = insert_(key, node->right_node_);
        }
        else if(node->key_ == key)
		{
			avlnode* anode= new avlnode(key);
			node->addtolist(anode);
			return node;	
		}

        int height_L = sub_tree_height(node->left_node_);
        int height_R = sub_tree_height(node->right_node_);

        node->height_ = max(height_L, height_R);
        
        int balance_factor = height_L - height_R;

        if(balance_factor > 1)//L
        {
            if(key < node->left_node_->key_)//L
            {
                return node = right_rotation(node);
            }
            else//R
            {
                node->left_node_ = left_rotation(node->left_node_);
                return node = right_rotation(node);
            }
        }
        else if(balance_factor < -1)//R
        {
            if(key < node->right_node_->key_)//L
            {
                node->right_node_ = right_rotation(node->right_node_);
                return node = left_rotation(node);
            }
            else//R
            {
                return node = left_rotation(node);
            }
        }

        return node;
    }

    avlnode* pop_(long long int key, avlnode* node)
    {
        if(node == nullptr) return nullptr;

        if(key < node->key_) 
        {
            node->left_node_ = pop_(key, node->left_node_);
        }
        else if(key > node->key_) 
        {
            node->right_node_ = pop_(key, node->right_node_);
        }
        else //if(node->key_ == key) 
        {
            if(node->left_node_ == nullptr && node->right_node_ == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if(node->left_node_ == nullptr && node->right_node_ != nullptr)
            {
                avlnode* sub_right_tree = node->right_node_;
                delete node;
                return sub_right_tree;
            }
            else if(node->left_node_ != nullptr && node->right_node_ == nullptr)
            {
                avlnode* sub_left_tree = node->left_node_;
                delete node;
                return sub_left_tree;
            }
            else            
            {
                avlnode* maxium_node_in_sub_left_tree = maximum_node_of_tree(node->left_node_);
                node->key_ = maxium_node_in_sub_left_tree->key_;
                node->left_node_ = pop_(maxium_node_in_sub_left_tree->key_, node->left_node_);
            }
        }

        int height_L = sub_tree_height(node->left_node_);
        int height_R = sub_tree_height(node->right_node_);

        node->height_ = max(height_L, height_R);
        
        int balance_factor = height_L - height_R;

        if(balance_factor > 1)//L
        {
            if(sub_tree_height(node->left_node_->left_node_) > sub_tree_height(node->left_node_->right_node_))//L
            {
                return node = right_rotation(node);
            }
            else//R
            {
                node->left_node_ = left_rotation(node->left_node_);
                return node = right_rotation(node);
            }
        }
        else if(balance_factor < -1)//R
        {
            if(sub_tree_height(node->right_node_->left_node_) > sub_tree_height(node->right_node_->right_node_))//L
            {
                node->right_node_ = right_rotation(node->right_node_);
                return node = left_rotation(node);
            }
            else//R
            {
                return node = left_rotation(node);
            }
        }

        return node;
    }

public:

    AVLTree1()
    {
        root_ = nullptr;
    }

    ~AVLTree1()
    {

    }

    void insert(long long int key)
    {
        root_ = insert_(key,root_);
    }

    void pop(long long int key)
    {
        root_ = pop_(key, root_);
    }
    
    avlnode* getroot()
    {
    	return root_;
	}
};

class htnode{
	public:
	long long int key;
	string code;
	htnode* next;
	htnode()
	{
		next=NULL;
	}
	htnode(long long int k,string cc)
	{
		key=k;
		code=cc;
		next=NULL;
	}
};

class hmap{
	public:
	htnode **htable;
	int capacity;
	int size;
	hmap()
	{
		int capacity=MAX;
		size=0;
		htable=new htnode*[capacity];
		for(int i=0;i<capacity;i++)
		{
			htable[i]=NULL;
		}	
	}
	
	int hashf(long long int kkey)
	{
		return (kkey%capacity);
	}
	
	void hinsert(long long int k,string cc)
	{
		int hindex=hashf(k);
		htnode *nn=new htnode(k,cc);
		htnode *head=htable[hindex];
		if(head==NULL)
		{
			head=nn;
		}
		else
		{
			htnode* temp=head;
			while(temp->next!=NULL)
			{
				temp=temp->next;
			}
			temp->next=nn;
		}
		size++;
		//rehash
		//if(((float)size/(float)capacity)>0.65)
		//{
			//rehash();
		//}
	}

	void rehash()
	{
		int ncapacity=capacity*100;
		htnode **newtable=new htnode*[ncapacity];
		for(int i=0;i<capacity;i++)
		{
			htnode* head=htable[i];
			if(head!=NULL)
			{
				
			}
		}
	}
	
	string getcode(long long int k)
	{
		int hindex=hashf(k);
		string str="NULL";
		htnode *head=htable[hindex];
		htnode* temp=head;
		if(head==NULL)
		{
			return str;
		}
		else
		{
			while(temp!=NULL)
			{
				if(temp->key==k)
				{
					return temp->code; 
				}
				temp=temp->next;
			}
			return str;
		}
	}
};


void inorder(AVLNode* node)
{
    if(node!=NULL)
    {
    	inorder(node->left_node_);
    	cout<<node->key_<<" ";
    	inorder(node->right_node_);
	}
}

void inorder(avlnode* node,hmap m1)
{
    if(node!=NULL)
    {
    	inorder(node->left_node_,m1);
    	cout<<"| "<<node->key_<<"\t\t"<<m1.getcode(node->key_)<<" |\n";
    	inorder(node->right_node_,m1);
	}
}

void getsize(AVLNode *root,int &count)
{
	if(root!=NULL)
    {
    	count++;
    	getsize(root->left_node_,count);
    	getsize(root->right_node_,count);
	}
}

void getsize(avlnode *root,int &count)
{
	if(root!=NULL)
    {
    	count++;
    	getsize(root->left_node_,count);
    	getsize(root->right_node_,count);
	}
}

void tSize(Node* root,int &count,int &total)
{
	if(root!=NULL)
	{
		total+=root->pcount;
		count++;
		tSize(root->left,count,total);
		tSize(root->right,count,total);
	}
	
}


void gettotal(AVLNode *root,int &count)
{
	if(root!=NULL)
	{
		count+=root->pcount;
		gettotal(root->left_node_,count);
		gettotal(root->right_node_,count);
	}
}

void gettotal(avlnode *root,int &count)
{
	if(root!=NULL)
	{
		count+=root->pcount;
		gettotal(root->left_node_,count);
		gettotal(root->right_node_,count);
	}
}

void largestcategory(Node* rt,string &cc,int &count,long long int &id)
{
	static int max=0;
	if(rt!=NULL)
	{
			if(rt->pcount>max)
			{
				max=rt->pcount;
				cc=rt->ccode;
				count=rt->pcount;
				id=rt->data;	
			}
			largestcategory(rt->left,cc,count,id);
			largestcategory(rt->right,cc,count,id);		
	}	
}

int maxDepth(AVLNode* node) 
{ 
    if (node == NULL) 
        return -1;
    else
    { 
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left_node_); 
        int rDepth = maxDepth(node->right_node_); 
    
        /* use the larger one */
        if (lDepth > rDepth) 
            return(lDepth + 1); 
        else return(rDepth + 1); 
    } 
}

void read_record(AVLTree &rt,hmap &m1,AVLTree1 &rt1)
{
  
    // File pointer
    fstream fin;
  	fstream fout;
    // Open an existing file
    fin.open("E:\\downloads\\ecommercePurchase.csv", ios::in);
    //fout.open("E:\\downloads\\ecommercePurchase.csv",ios::out);
    if(fin==NULL)
    {
    cout<<"File not found\n";
  	exit(0);
	}
    // Get the roll number
    // of which the data is required
    int count=0;
    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
  
    while (!fin.eof())
	 {
  		getline(fin, line);
        row.clear();
        // read an entire row and
        // store it in a string variable 'line'
        
  
        // used for breaking words
        stringstream s(line);
  	//	cout<<"in1 ";
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
  
        // convert string to integer for comparision
  
        // Compare the roll number
        // Print the found data
        /*if(row[1]==" purchase")
        {
        	count++;
        	//cout <<row[0]<< "\t\t";
            //cout <<row[1]<< "\t\t";
        	//cout <<row[2]<< "\t\t";
            //cout <<row[3]<< "\t\t";
            int pid=stoi(row[2]);
			long long int cid=stoll(row[3]);
			int uid=stoi(row[7]);
			float price=stof(row[6]);
			string etime=row[0];
			string etype=row[1];
			string cc=row[4];
			string br=row[5];
			string session=row[8];
			cout <<etime<< "\t\t";
            cout <<etype<< "\t\t";
        	cout <<pid<< "\t\t";
            cout <<cid<< "\t\t";
            cout <<cc<< "\t\t";
            cout <<br<< "\t\t";
			cout<<price<<"\t\t";
			cout <<uid<< "\t\t";
			cout <<session<< "\n";
		}*/
		int pid=stoi(row[2]);
		long long int cid=stoll(row[3]);
		int uid=stoi(row[7]);
		float price=stof(row[6]);
		string etime=row[0];
		string etype=row[1];
		string cc=row[4];
		string br=row[5];
		string session=row[8];
		//cout<<price<<"\n";
		rt.insert(uid,pid,cid,uid,etime,etype,cc,br,price,session);
		//rt1.insert(uid);
		
	//	m1.hinsert(cid,cc);
		//cout<<cid<<"\n";
       	/*if(row[1]=="purchase")
       	{
       		 if(!fin.eof())
        	{
        	//	count++;
        		for(int i=0;i<row.size()-1;i++)
        	    {
        	    	fout<<row[i]<<", ";
				}
				fout<<row[row.size()-1]<<"\n";
			}
       		
       	}*/
        if(fin.eof())
        {
        	fin.close();
        	break;
		}
		if (count == 10)
    	break;
	}
	fin.close();
	fout.close();
}

void read_record(bst &rt)
{
  
    // File pointer
    fstream fin;
  	fstream fout;
    // Open an existing file
    fin.open("E:\\downloads\\ecommercePurchase.csv", ios::in);
    //fout.open("E:\\downloads\\ecommercePurchase.csv",ios::out);
    if(fin==NULL)
    {
    cout<<"File not found\n";
  	exit(0);
	}
    // Get the roll number
    // of which the data is required
    int count=0;
    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
  
    while (!fin.eof())
	 {
  		getline(fin, line);
        row.clear();
        // read an entire row and
        // store it in a string variable 'line'
        
  
        // used for breaking words
        stringstream s(line);
  	//	cout<<"in1 ";
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
  
        // convert string to integer for comparision
  
        // Compare the roll number
        // Print the found data
        /*if(row[1]==" purchase")
        {
        	count++;
        	//cout <<row[0]<< "\t\t";
            //cout <<row[1]<< "\t\t";
        	//cout <<row[2]<< "\t\t";
            //cout <<row[3]<< "\t\t";
            int pid=stoi(row[2]);
			long long int cid=stoll(row[3]);
			int uid=stoi(row[7]);
			float price=stof(row[6]);
			string etime=row[0];
			string etype=row[1];
			string cc=row[4];
			string br=row[5];
			string session=row[8];
			cout <<etime<< "\t\t";
            cout <<etype<< "\t\t";
        	cout <<pid<< "\t\t";
            cout <<cid<< "\t\t";
            cout <<cc<< "\t\t";
            cout <<br<< "\t\t";
			cout<<price<<"\t\t";
			cout <<uid<< "\t\t";
			cout <<session<< "\n";
		}*/
		int pid=stoi(row[2]);
		long long int cid=stoll(row[3]);
		int uid=stoi(row[7]);
		float price=stof(row[6]);
		string etime=row[0];
		string etype=row[1];
		string cc=row[4];
		string br=row[5];
		string session=row[8];
		//cout<<price<<"\n";
		//int n1=cid%1000000000;
		rt.addnode(cid,cc);
		
		//cout<<cid<<"\n";
       	/*if(row[1]=="purchase")
       	{
       		 if(!fin.eof())
        	{
        	//	count++;
        		for(int i=0;i<row.size()-1;i++)
        	    {
        	    	fout<<row[i]<<", ";
				}
				fout<<row[row.size()-1]<<"\n";
			}
       		
       	}*/
        if(fin.eof())
        {
        	fin.close();
        	break;
		}
		if (count == 10)
    	break;
	}
	fin.close();
	//fout.close();
}



void menu()
{
	cout<<"\t\tECOMMERCE DATASET\t\t\n"<<"1. Get customer information\n2. Most popular item category\n3. Transaction frequency w.r.t. date/time\n4. Average bill per customer order\n\nEnter your choice: ";
}

void getUsers(AVLTree t1)
{
	int c1=0,c2=0;
	getsize(t1.getroot(),c1);
	gettotal(t1.getroot(),c2);
	cout<<"\n\n*There are  "<<c1<<"  unique users who had made at least 1 purchase\n";
	cout<<"*There are  "<<c2<<"  total transactions in the dataset\n";
	cout<<"*There are  "<<((float)c2/(float)c1)<<"  average transactions per user in the dataset\n";
	cout<<"*Height of generated User AVL tree: "<<maxDepth(t1.getroot());
}

void updatefreq(AVLNode* rt,DynArrInt &arr1)
{
	if(rt!=NULL)
	{
		string str;
		str=rt->data.event_time;
		int n1= str[8]-'0';
		n1*=10;
		n1+=str[9]-'0';
		if(n1>=1 && n1<=31)
		{
			arr1[n1-1]++;	
		}
		listnode* temp=rt->head;
		while(temp!=NULL)
		{
			str=temp->d1.event_time;
			n1= str[8]-'0';
			n1*=10;
			n1+=str[9]-'0';
			arr1[n1-1]++;
			temp=temp->next;
		}
		updatefreq(rt->left_node_,arr1);
		updatefreq(rt->right_node_,arr1);
	}
}

void dtfreq(AVLNode* rt)
{
	DynArrInt arr1(31);
	updatefreq(rt,arr1);
	int max=0,mi=0,sum=0;
	cout<<"\nFor the month of October 2019:\n";
	
	for(int i=0;i<31;i++)
	{
		sum+=arr1[i];
	}
	
	cout<<"Total transactions: "<<sum<<"\nDaily transactions: \n\n";
	for(int i=0;i<31;i++)
	{
		cout<<"Day "<<i+1<<": "<<arr1[i]<<" transactions; Percentage total: "<<(((float)arr1[i]/(float)sum)*100)<<"%\n";
		if(arr1[i]>max)
		{
			max=arr1[i];
			mi=i;	
		}
	}
	
	cout<<"\nDay with most traffic: "<<mi+1<<"\nOverall purchases made: "<<(((float)arr1[mi]/(float)sum)*100)<<"%\n";
}

int getsum(string str1)
{
	int sum=0;
	for(int i=0;i<str1.length();i++)
	{
		sum+=str1[i];
	}
	return sum;
}

class Hnode{
	public:
	int key;
	float val;
	Hnode* next;
	Hnode()
	{
		next=NULL;
	}
	Hnode(int k,float v)
	{
		key=k;
		val=v;
		next=NULL;
	}
};

class hashmap{
	private:
	Hnode **ht;
	int capacity;
	public:
	hashmap(int cap=10)
	{
		capacity=cap;
		ht=new Hnode*[capacity];
		for(int i=0;i<capacity;i++)
		{
			ht[i]=NULL;
		}
	}
	
	int hashfunc(int k1)
	{
		return (k1%capacity);
	}
	
	void insert(int k1,float v1)
	{
		int hindex=hashfunc(k1);
		Hnode* n=new Hnode(k1,v1);
		Hnode* temp=ht[hindex];
		if(temp==NULL)
		{
			ht[hindex]=n;
		}
		else
		{
			while(temp->next!=NULL)
			{
				temp=temp->next;
			}
			temp->next=n;
		}
	}
	
	void remove(int k1)
	{
		int hindex=hashfunc(k1);
		Hnode *temp=ht[hindex];
		Hnode *prev=NULL;
		if(temp!=NULL)
		{
			while(temp!=NULL)
			{
				if(temp->key==k1)
				{
					cout<<"\nDeleted value: "<<temp->val;
					if(prev==NULL)
					{
						Hnode* t1=temp;
						temp=temp->next;
						delete t1;
						ht[hindex]=temp;
					}
					else
					{
						prev->next=temp->next;
						delete temp;
						temp=prev->next;
					}
				}
				else
				{
					prev=temp;
					temp=temp->next;
				}
			}
		}
		else
		{
			cout<<"\nNo such entry\n";
		}
		
	}
	
	int search(int k1,float v1)
	{
		int hindex=hashfunc(k1);
		Hnode *temp=ht[hindex];
		if(temp!=NULL)
		{
			//cout<<"\n\nValues: ";
			while(temp!=NULL)
			{
				if(temp->key==k1)
				{
					temp->val=temp->val+v1;
					return 1;
				}
				temp=temp->next;
			}
			return 0;
			//cout<<endl;	
		}
		else
		{
			//cout<<"\nNo such entry\n";
			return 0;
		}
	}
	
	float search(int k1)
	{
		int hindex=hashfunc(k1);
		Hnode *temp=ht[hindex];
		if(temp!=NULL)
		{
			//cout<<"\n\nValues: ";
			while(temp!=NULL)
			{
				if(temp->key==k1)
				{
					return temp->val;
				}
				temp=temp->next;
			}
			return 0;
			//cout<<endl;	
		}
		else
		{
			//cout<<"\nNo such entry\n";
			return 0;
		}
	}
	
	void menu()
	{
		int ch,k1,v1;
		while(1)
		{
			cout<<"\n\n1. Insert\n2. Remove\n3. Search\nEnter choice: ";
			cin>>ch;
			switch(ch)
			{
				case 1:
					cout<<"\nEnter key value: ";
					cin>>k1>>v1;
					insert(k1,v1);
					break;
				case 2:
					cout<<"\nEnter key: ";
					cin>>k1;
					remove(k1);
					break;
				case 3:
					cout<<"\nEnter key: ";
					cin>>k1;
					//search(k1);
					break;
				default:
					ch=4;
					break;
			}
			if(ch==4)
			break;	
		}
	}
};

void searchUser(AVLNode* root,bst &b1,hashmap &hm1)
{
	if(root!=NULL)
	{
		int sum1=getsum(root->data.user_session);
		b1.addnode(sum1,root->data.user_session);
		if(!hm1.search(sum1,root->data.price))
		{
			hm1.insert(sum1,root->data.price);	
		}
		listnode* temp=root->head;
		while(temp!=NULL)
		{
			sum1=getsum(temp->d1.user_session);
			b1.addnode(sum1,temp->d1.user_session);
			if(!hm1.search(sum1,temp->d1.price))
			{
				hm1.insert(sum1,temp->d1.price);	
			}
			temp=temp->next;
		}
		searchUser(root->left_node_,b1,hm1);
		searchUser(root->right_node_,b1,hm1);
	}
}

void searchBill(Node* root,long double &atotal,int &items,string &str1,hashmap hm1)
{
	static long double max=0;
	if(root!=NULL)
	{
		int sum=root->data;
		int itms=root->pcount;
		float f1=hm1.search(sum);
		float avg=(f1/(float)itms);
		if(avg>max)
		{
			max=f1;
			items=root->pcount;
			atotal=f1;
			str1=root->ccode;
		}
		searchBill(root->left,atotal,items,str1,hm1);
		searchBill(root->right,atotal,items,str1,hm1);
	}
}

void searchBill(Node* root,long double &atotal,hashmap hm1)
{
	if(root!=NULL)
	{
		int sum=root->data;
		long double f1=hm1.search(sum);
		atotal+=f1;
		searchBill(root->left,atotal,hm1);
		searchBill(root->right,atotal,hm1);
	}
}

void avgbill(AVLNode* root)
{
	bst billtree;
	hashmap hm1(5000);
	searchUser(root,billtree,hm1);
	int c1=0,t1=0;
	tSize(billtree.root,c1,t1);
	long double atotal=0;
	int items=0;
	string str1;
	searchBill(billtree.root,atotal,hm1);
	cout<<"\n\n*There were a total of  "<<c1<<" unique orders\n";
	cout<<"\n*There are a total of  "<<t1<<" transactions in the dataset\n";
	cout<<"\n\nBill details: \n";
	cout<<"*Total amount spent by people:  "<<atotal<<"  USD";
	cout<<"\n*Average bill order: "<<((atotal)/((float)c1*100))<<"  USD\n";
	
}

void precc()
{
	
}

inordert(Node* root)
{
	if(root!=NULL)
	{
		cout<<root->data<<" "<<root->ccode<<endl;
		inordert(root->left);
		inordert(root->right);
	}
}

//void getCategory(AVLTree t1,hmap m1);

void getCategory(AVLTree t1,hmap m1)
{
	bst t2;
	int c1=0,c2=0;
	string str1;
	int ct1=0;
	long long int id=0;		
	cout<<"\nGenerating category tree...\n";
	read_record(t2);
	cout<<"\nTree generated...\n";
	tSize(t2.root,c1,c2);
	cout<<"\n*There are  "<<c1<<"  unique cateogries in the dataset";
	cout<<"\n*There are  "<<c2<<"  total purchases in the dataset";
	cout<<"\n1. Display all categories\n2. Display most popular category\n\nEnter your choice: ";
	cin>>c1;
	switch(c1)
	{
		case 1:
			cout<<"| Category ID\t\tCategory Code |\n\n";
			//inorder(t2.getroot(),m1);
			inordert(t2.root);
			break;
		case 2:
			largestcategory(t2.root,str1,ct1,id);
			cout<<"\n*Most popular category: \n\n-Category ID: "<<id<<"\n-Category Code (possibly empty): "<<str1<<"\n-Number of purchases: "<<ct1<<endl;
			break;
		default:
			break;
	}
}

void Menu(AVLTree t1,hmap m1)
{
	int ch1;
	while(1)
	{
		system("cls");
		cout<<"\n";
		menu();
		cin>>ch1;
		switch(ch1)
		{
			case 1:
			getUsers(t1);
			cout<<"\nPress any key to continue.";
			getchar();
			getchar();
			break;
			case 2:
			getCategory(t1,m1);
			cout<<"\nPress any key to continue.";
			getchar();
			getchar();
			break;
			case 3:
			dtfreq(t1.getroot());
			cout<<"\nPress any key to continue.";
			getchar();
			getchar();
			break;
			case 4:
			avgbill(t1.getroot());
			cout<<"\nPress any key to continue.";
			getchar();
			getchar();
			default:
			break;	
		}
		if(ch1<1 || ch1>4)
		{
			cout<<"\n\nNow exiting\n\n";
			break;
		}
	}
}

int main()
{
	AVLTree t1;//,t2;
	AVLTree1 t2;
	hmap m1;
	cout<<"\n\nPress any key to generate customer tree";
	getchar();
	read_record(t1,m1,t2);
	int c1=0;
	Menu(t1,m1);
	//cout<<"\nread--\n";
	///read_record(t2);
	//getUsers(t1);
	//dtfreq(t1.getroot());
	//cout<<m1.getcode(2053013552326770905);
	//getCategory(t1,m1);
	//int c1=0,c2=0;
	//getsize(t1.getroot(),c1);	
	//gettotal(t1.getroot(),c2);
	
	//cout<<"\n"<<c1<<endl<<c2;
}
