#include <iostream>

template <class T>
class Btree{
public:
struct Node{
	Node() : key(0), 
				left(nullptr), 
				right(nullptr) {}
	Node(int value) : key(value), 
						left(nullptr), 
						right(nullptr){}
	int key;
	Node* left;
	Node* right;
};

public:
	Btree();
	Btree(const Btree&);
	Btree(Btree&&);
	Btree &operator=(const Btree&);
	Btree &operator=(Btree&&);
	~Btree();
	void insert(T);
	void destroy_tree();
	void inorder_print();
	void preorder_print();
	void postorder_print();
	void search(T);
	Node *copy_helper(const Node*);
	Node *delete_item(T);
	Node *min_value_node(Node*);
	Node *n_search(T);
private:
	void destroy_tree(Node *);
	void insert(T, Node *&);
	void inorder_print(Node *node);
	void preorder_print(Node *node);
	void postorder_print(Node *node);
	Node *n_search(T, Node *leaf);
	Node *delete_item(Node *root, T key);
	Node* root;
};

template <class T>
Btree<T>::Btree() : root(nullptr) {}

template <class T>
Btree<T>::~Btree() {
	destroy_tree();
}

template <class T>
Btree<T>::Btree(const Btree & to_copy) : root(copy_helper(to_copy.root)){}

template <class T>
Btree<T>::Btree(Btree && to_move) : root(to_move.root){
	to_move.root = nullptr;
} 

template <class T>
Btree<T> & Btree<T>::operator=(const Btree & to_assign)
{
	if(this == & to_assign){
		return *this;
	} else {
	destroy_tree(root);
	root = copy_helper(to_assign.root);
	}
	return *this;
}

template <class T>
Btree<T> & Btree<T>::operator=(Btree && to_assign)
{
	if(this == & to_assign){
		return *this;
	} else {
		destroy_tree(root);
		root = to_assign.root;
		to_assign.root = nullptr;
	}
	return *this;
}

template <class T>
void Btree<T>::destroy_tree()
{
	destroy_tree(root);
}

template <class T>
void Btree<T>::destroy_tree(Node *leaf)
{
	if(nullptr != leaf){
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
		leaf = nullptr;
	}
}

template <class T>
void Btree<T>::insert(T key)
{
	if(nullptr != root){
		insert(key, root);
	} else {
		root = new Node(key);//use param ctor in new
		//Node(key);		
		//root->key = key;
		//root->left = nullptr;
		//root->right = nullptr;
	}
}

template <class T>
void Btree<T>::insert(T key, Node *&leaf)
{
	if(key < leaf->key){
		if(nullptr != leaf->left){
			insert(key, leaf->left);
		} else {
			leaf->left = new Node(key);//use param ctor in new
			//Node(key);
			//leaf->left->key = key;
			//leaf->left->left = nullptr;
			//leaf->left->right = nullptr;
		}
	} else if(key >= leaf->key){
		if(nullptr != leaf->right){
			insert(key, leaf->right);
		} else {
			leaf->right = new Node(key);//use param ctor in new
			//Node(key);
			//leaf->right->key = key;
			//leaf->right->left = nullptr;
			//leaf->right->right = nullptr;
		}
	}
}

template <class T>
void Btree<T>::inorder_print()
{
	std::cout << "inorder traverse " << std::endl;
	inorder_print(root);
}

template <class T>
void Btree<T>::inorder_print(Node *leaf)
{
	if(nullptr == leaf){
		return;
	}
	inorder_print(leaf->left);
	std::cout << leaf->key << std::endl;
	inorder_print(leaf->right);
}

template <class T>
void Btree<T>::preorder_print()
{
	std::cout << "preorder traverse " << std::endl;
	preorder_print(root);
}

template <class T>
void Btree<T>::preorder_print(Node *leaf)
{
	if(nullptr == leaf){
		return;
	}
	std::cout << leaf->key << std::endl;
	preorder_print(leaf->left);
	preorder_print(leaf->right);
}

template <class T>
void Btree<T>::postorder_print()
{
	std::cout << "postorder traverse " << std::endl;
	postorder_print(root);
}

template <class T>
void Btree<T>::postorder_print(Node *leaf)
{
	if(nullptr == leaf){
		return;
	}
	postorder_print(leaf->left);
	postorder_print(leaf->right);
	std::cout << leaf->key << std::endl;
}

template <class T>
void Btree<T>::search(T key)
{
    int level = 0;
    Node * temp = new Node();
    temp = root;
    while(temp) {
        ++level;
        if(temp->key == key) {
            std::cout << "There is an element: " << key 
                      << " in level: " << level << std::endl;
            return;
        } else if(key < temp->key) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    std::cout << "There is no element " << key << std::endl;
    return;
}

template <class T>
typename Btree<T>::Node* Btree<T>::copy_helper(const Node* to_copy)
{
	if(nullptr == to_copy){
		return nullptr;
	}
	Node *copy_node = new Node;
	copy_node->key = to_copy->key;
	copy_node->left = copy_helper(to_copy->left);
	copy_node->right = copy_helper(to_copy->right);
	return copy_node;
}

template <class T>
typename Btree<T>::Node* Btree<T>::delete_item(T key)
{
	delete_item(root, key);
	return root;
}

template <class T>
typename Btree<T>::Node* Btree<T>::delete_item(Node* root, T key)
{
	if(nullptr == root){
		return root;
	}
	if(key < root->key){
		root->left = delete_item(root->left, key);
	}
	else if(key > root->key){
		root->right = delete_item(root->right, key);
	} else {
		if(nullptr == root->left){
			Node *temp = root->right;
			delete root;
			return temp;
		}
		else if(nullptr == root->right){
			Node *temp = root->right;
			delete root;
			return temp;
		}
		Node *temp = min_value_node(root->right);
		root->key = temp->key;
		root->right = delete_item(root->right, temp->key);
	}
	return root;
}

template <class T>
typename Btree<T>::Node * Btree<T>::min_value_node(Node* node)
{
	Node* current_node = node;
	while(current_node && current_node->left != nullptr){
		current_node = current_node->left;
	}
	return current_node;
}

template <class T>
typename Btree<T>::Node *Btree<T>::n_search(T key)
{
	return n_search(key, root);
}

template <class T>
typename Btree<T>::Node *Btree<T>::n_search(T key, Node *leaf){
	if(leaf != nullptr){
		if(key == leaf->key){
			return leaf;
		}
		if(key < leaf->key){
			return n_search(key, leaf->left);
		}else{
			return n_search(key, leaf->right);
		}
	}else{
		return nullptr;
	}
}


int main()
{
	Btree <int> b;
	b.insert(5);
	b.insert(3);
	b.insert(7);
	b.insert(2);
	b.insert(4);
	b.insert(6);
	b.insert(8);
	b.inorder_print();
	std::cout << std::endl;
	b.preorder_print();
	std::cout << std::endl;
	b.postorder_print();
	b.search(2);
	b.search(8);
	b.search(39);
	b.search(22);
	b.n_search(22);
	Btree <int> b2(b);
	std::cout << "------Copied object's " << std::endl;
	b2.inorder_print();
	Btree <int> b3(std::move(b2));
	std::cout << "------Moved object's " << std::endl;
	b3.inorder_print();
	Btree <int> b4;
	b4 = b3;
	std::cout << "------Assign object " << std::endl;
	b4.inorder_print();
	Btree <int> b5;
	b5 = std::move(b4);
	std::cout << "------Move ass " << std::endl;
	b5.inorder_print();
	b5.delete_item(4);
	b5.inorder_print();
	return 0;
}
