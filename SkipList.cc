#include <bits/stdc++.h>
using namespace std;

class Node
{
	public:
		int key;

		Node **forward;
		Node(int, int);
};

Node::Node(int key, int level)
{
	this->key = key;

	forward = new Node*[level+1];
  
  memset(forward, 0, sizeof(Node*)*(level+1));
};

class SkipList
{
	int MAXLVL;
	float P;
	int level;
	Node *header;
	public:
	SkipList(int, float);
	int randomLevel();
	Node* createNode(int, int);
	void insertElement(int);
	void deleteElement(int);
	void searchElement(int);
	void displayList();
	
	//get number of lists and count data's additional copy average 
	int getlevel();
	double getcount();
	double count = 0;
};

SkipList::SkipList(int MAXLVL, float P)
{
	this->MAXLVL = MAXLVL;
	this->P = P;
	level = 0;

	header = new Node(-1, MAXLVL);
};

int SkipList::randomLevel()
{
	float r = (float)rand()/RAND_MAX;
	int lvl = 0;
	while(r < P && lvl < MAXLVL)
	{
		lvl++;
		r = (float)rand()/RAND_MAX;
	}
	return lvl;
};

Node* SkipList::createNode(int key, int level)
{
	Node *n = new Node(key, level);
	return n;
};

//get number of lists
int SkipList::getlevel()
{
	return level;
}

void SkipList::insertElement(int key)
{
	Node *current = header;

	Node *update[MAXLVL+1];
	memset(update, 0, sizeof(Node*)*(MAXLVL+1));

	for(int i = level; i >= 0; i--)
	{
		while(current->forward[i] != NULL &&
				current->forward[i]->key < key)
			current = current->forward[i];
		update[i] = current;
	}

	current = current->forward[0];

	if (current == NULL || current->key != key)
	{
	  int rlevel = randomLevel();
		
		if(rlevel > level)
		{
			for(int i=level+1;i<rlevel+1;i++)
				update[i] = header;

			level = rlevel;
		}

		//count data's additional copy
		count += rlevel;
		
		Node* n = createNode(key, rlevel);

		for(int i=0;i<=rlevel;i++)
		{
			n->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = n;
		}
	}
};

void SkipList::searchElement(int key)
{
	Node *current = header;

	for(int i = level; i >= 0; i--)
	{
		while(current->forward[i] &&
				current->forward[i]->key < key)
			current = current->forward[i];

	}

	current = current->forward[0];
};

int main(){
	
	//0.9 is head's probability, can change to 0.1 or 0.5
	SkipList sk(5000,0.9);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<unsigned long long> dis(1, pow(2,30));

	for(int pow=10;pow <= 30;++pow){
		int num = 1 << pow;
		int *arr = new int[num];
		int size = 0;
		clock_t start,end;
		for(int j=0;j<num;++j){
			*(arr+j) =  dis(gen);
			size++;
		}
		start = clock();

		for(int i = 0; i < size; ++i)
			sk.insertElement(arr[i]);

		end = clock();
		
		double ans1;
		ans1 = ((double) (end - start)) / CLOCKS_PER_SEC;

		start = clock();

		for(int i = 0; i < 100000; ++i){
			sk.searchElement(dis(gen));
		}

		end = clock();
		
		double ans2;
		ans2 = ((double) (end-start)) / CLOCKS_PER_SEC;
		
		cout << pow << ", " << ans1 << ", " << ans2 << ", " << sk.getlevel() << ", " << sk.count/num << endl;
		delete [] arr;
	}

	return 0;
}
