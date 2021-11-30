#include <bits/stdc++.h>
#include <random>
using namespace std;

// A Treap Node
struct TreapNode
{
        int key, priority;
        TreapNode *left, *right;
};

/* T1, T2 and T3 are subtrees of the tree rooted with y
   (on left side) or x (on right side)
   y                               x
   / \     Right Rotation          /  \
   x   T3   – – – – – – – >        T1   y
   / \       < - - - - - - -            / \
   T1  T2     Left Rotation            T2  T3 */

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
TreapNode *rightRotate(TreapNode *y)
{
        TreapNode *x = y->left,  *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Return new root
        return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TreapNode *leftRotate(TreapNode *x)
{
        TreapNode *y = x->right, *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Return new root
        return y;
}

/* Utility function to add a new key */
TreapNode* newNode(int key)
{
        TreapNode* temp = new TreapNode;
        temp->key = key;
        temp->priority = rand()%100;
        temp->left = temp->right = NULL;
        return temp;
}

// C function to search a given key in a given BST
TreapNode* search(TreapNode* root, int key)
{
        // Base Cases: root is null or key is present at root
        if (root == NULL || root->key == key)
                return root;

        // Key is greater than root's key
        if (root->key < key)
                return search(root->right, key);

        // Key is smaller than root's key
        return search(root->left, key);
}

/* Recursive implementation of insertion in Treap */
TreapNode* insert(TreapNode* root, int key)
{
        // If root is NULL, create a new node and return it
        if (!root)
                return newNode(key);

        // If key is smaller than root
        if (key <= root->key)
        {
                // Insert in left subtree
                root->left = insert(root->left, key);

                // Fix Heap property if it is violated
                if (root->left->priority > root->priority)
                        root = rightRotate(root);
        }
        else  // If key is greater
        {
                // Insert in right subtree
                root->right = insert(root->right, key);

                // Fix Heap property if it is violated
                if (root->right->priority > root->priority)
                        root = leftRotate(root);
        }
        return root;
}

/* Recursive implementation of Delete() */
TreapNode* deleteNode(TreapNode* root, int key)
{
        if (root == NULL)
                return root;

        if (key < root->key)
                root->left = deleteNode(root->left, key);
        else if (key > root->key)
                root->right = deleteNode(root->right, key);

        // IF KEY IS AT ROOT

        // If left is NULL
        else if (root->left == NULL)
        {
                TreapNode *temp = root->right;
                delete(root);
                root = temp;  // Make right child as root
        }

        // If Right is NULL
        else if (root->right == NULL)
        {
                TreapNode *temp = root->left;
                delete(root);
                root = temp;  // Make left child as root
        }

        // If ksy is at root and both left and right are not NULL
        else if (root->left->priority < root->right->priority)
        {
                root = leftRotate(root);
                root->left = deleteNode(root->left, key);
        }
        else
        {
                root = rightRotate(root);
                root->right = deleteNode(root->right, key);
        }

        return root;
}

// A utility function to print tree
void inorder(TreapNode* root)
{
        if (root)
        {
                inorder(root->left);
                cout << "key: "<< root->key << " | priority: %d "
                        << root->priority;
                if (root->left)
                        cout << " | left child: " << root->left->key;
                if (root->right)
                        cout << " | right child: " << root->right->key;
                cout << endl;
                inorder(root->right);
        }
}

int main(){

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned long long> dis(1, pow(2,30));

        struct TreapNode *root = NULL;

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
                        root = insert(root,arr[i]);

                end = clock();

                double ans1;
                ans1 = ((double) (end - start)) / CLOCKS_PER_SEC;
                //cout << "insert.time= " << ans1 << "sec" << endl;

                start = clock();

                TreapNode* res;
                for(int i = 0; i < 100000; ++i){
                         res = search(root, dis(gen));
                }

                end = clock();

                double ans2;
                ans2 = ((double) (end-start)) / CLOCKS_PER_SEC;
                //cout << "search.time= " << ans2 << "sec" << endl;

                cout << pow << ", " << ans1 << ", " << ans2 << endl;
                delete [] arr;
        }

        return 0;
}

