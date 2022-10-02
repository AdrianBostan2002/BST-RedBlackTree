#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>
#define ESC "\033["
#define WHITE_BKG "47"
#define	RED "41"
#define BLACK "30"
#define RESET "\033[m"


class ARN
{
private:
	class Node
	{
	public:
		int key;
		Node* left;
		Node* right;
		Node* parent;
		bool color;
		Node();
		Node(int key)
		{
			this->key = key;
			color = 1;
			Node* left = nullptr;
			Node* right = nullptr;
			Node* parent = nullptr;
		}
	};
	Node* root;
	Node* nil;

public:

	ARN()
	{
		nil = new Node(0);
		nil->color = 0;
		root = nil;
		root->parent = nil;
	}

	~ARN()
	{
		clear_tree();
		delete root;
	}

	void insert(int cheia)
	{
		Node* nod_de_inserat = new Node(cheia);
		Node* x = root;
		Node* y = nil;
		while (x != nil)
		{
			y = x;
			if (nod_de_inserat->key < x->key)
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}
		nod_de_inserat->parent = y;
		if (y == nil)
		{
			root = nod_de_inserat;
			root->color = 0;
			root->parent = nil;
		}
		else
		{
			if (nod_de_inserat->key < y->key)
			{
				y->left = nod_de_inserat;
			}
			else
			{
				y->right = nod_de_inserat;
			}
		}
		nod_de_inserat->left = nil;
		nod_de_inserat->right = nil;
		if (nod_de_inserat->parent != nil && nod_de_inserat->parent->color == 1)
		{
			insert_repare(nod_de_inserat);
		}
	}

	void insert_repare(Node* z)
	{
		Node* U;
		while (z->parent != nil && z->parent->color == 1)
		{
			if (z->parent == z->parent->parent->left)
			{

				if (z->parent->parent->right != nil && z->parent->parent->right->color == 1)
				{
					U = z->parent->parent->right;
					z->parent->color = 0;
					U->color = 0;
					z->parent->parent->color = 1;
					z = z->parent->parent;
				}
				else
				{
					if (z->parent != nil && z == z->parent->right)
					{
						z = z->parent;
						rot_st(z);
					}
					z->parent->color = 0;
					z->parent->parent->color = 1;
					rot_dr(z->parent->parent);
				}
			}
			else
			{
				if (z->parent->parent->left != nil && z->parent->parent->left->color == 1)
				{
					U = z->parent->parent->left;
					z->parent->color = 0;
					U->color = 0;
					z->parent->parent->color = 1;
					z = z->parent->parent;
				}
				else
				{
					if (z->parent != nil && z == z->parent->left)
					{
						z = z->parent;
						rot_dr(z);
					}
					z->parent->color = 0;
					z->parent->parent->color = 1;
					rot_st(z->parent->parent);
				}

			}
		}

		root->color = 0;
	}

	void rot_st(Node* y)
	{
		Node* x = y->right;
		y->right = x->left;
		if (x->left != nil)
		{
			x->left->parent = y;
		}
		x->parent = y->parent;
		if (y->parent == nil)
		{
			root = x;
			root->parent = nil;
		}
		else
		{
			if (y == y->parent->left)
			{
				y->parent->left = x;
			}
			else
			{
				y->parent->right = x;
			}
		}
		x->left = y;
		y->parent = x;
	}

	void rot_dr(Node* y)
	{
		Node* x = y->left;
		y->left = x->right;
		if (x->right != nil)
		{
			x->right->parent = y;
		}
		x->parent = y->parent;
		if (y->parent == nil)
		{
			root = x;
			root->parent = nil;
		}
		else
		{
			if (y == y->parent->right)
			{
				y->parent->right = x;
			}
			else
			{
				y->parent->left = x;
			}
		}
		x->right = y;
		y->parent = x;
	}

	void transplant(Node* u, Node* v)
	{
		if (u->parent == nil)
		{
			root = v;
			root->parent = nil;
		}
		else if (u == u->parent->left)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void delete_node(Node* z)
	{
		Node* y = z;
		bool y_original_color = y->color;
		Node* x;
		if (z->left == nil)
		{
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == nil)
		{
			x = z->left;
			transplant(z, z->left);
		}
		else
		{
			y = getMinNode(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (y_original_color == 0)
		{
			delete_repare(x);
		}
	}

	void delete_repare(Node* x)
	{
		Node* w;
		while (x != root && x->color == 0)
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;
				if (w->color == 1)
				{
					w->color = 0;
					x->parent->color = 1;
					rot_st(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == 0 && w->right->color == 0)
				{
					w->color = 1;
					x = x->parent;
				}
				else if (w->right->color == 0)
				{
					w->left->color = 0;
					w->color = 1;
					rot_dr(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 0;
				w->right->color = 0;
				rot_st(x->parent);
			}
			else
			{
				w = x->parent->left;
				if (w->color == 1)
				{
					w->color = 0;
					x->parent->color = 1;
					rot_dr(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == 0 && w->right->color == 0)
				{
					w->color = 1;
					x = x->parent;
				}
				else if (w->left->color == 0)
				{
					w->right->color = 0;
					w->color = 1;
					rot_st(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 0;
				w->left->color = 0;
				rot_dr(x->parent);
			}
		}
		x->color = 0;
	}

	Node* find(int cheie)
	{
		Node* nod_curent = root;
		while (nod_curent != nil)
		{
			if (nod_curent->key == cheie)
			{
				return nod_curent;
			}
			if (cheie < nod_curent->key)
			{
				nod_curent = nod_curent->left;
			}
			else
			{
				nod_curent = nod_curent->right;
			}
		}
		return nil;
	}

	void erase_key(int key)
	{
		Node* nod = find(key);
		if (nod != nil)
		{
			delete_node(nod);
		}
	}

	Node* getMinNode(Node* nod_curent = nullptr)
	{
		if (nod_curent == nullptr)
		{
			nod_curent = root;
		}
		Node* min_key = nil;
		while (nod_curent != nil)
		{
			min_key = nod_curent;
			nod_curent = nod_curent->left;
		}
		return min_key;
	}

	Node* getMaxNode(Node* nod_curent = nullptr)
	{
		if (nod_curent == nullptr)
		{
			nod_curent = root;
		}
		Node* max_key = nil;
		while (nod_curent != nil)
		{
			max_key = nod_curent;
			nod_curent = nod_curent->right;
		}
		return max_key;
	}

	Node* getSuccesor(Node* nod)
	{
		if (nod != nil)
		{
			Node* Succesor;
			if (nod->right != nil)
			{
				Succesor = getMinNode(nod->right);
			}
			else
			{
				Succesor = nod->parent;
				while (Succesor != nil && nod == Succesor->right)
				{
					nod = Succesor;
					Succesor = nod->parent;
				}
			}
			return Succesor;
		}
		else return nil;
	}

	Node* getPredecessor(Node* nod)
	{
		if (nod != nil)
		{
			Node* Predecessor;
			if (nod->left != nil)
			{
				Predecessor = getMaxNode(nod->left);
			}
			else
			{
				Predecessor = nod->parent;
				while (Predecessor != nil && nod == Predecessor->left)
				{
					nod = Predecessor;
					Predecessor = nod->parent;
				}
				return Predecessor;
			}
		}
		else return nil;
	}

	Node* getRoot()
	{
		return root;
	}

	void print_tree(int op)
	{
		if (op == 1)
		{
			printPreOrder(root);
		}
		if (op == 2)
		{
			printInOrder(root);
		}
		if (op == 3)
		{
			printPostOrder(root);
		}
		if (op == 4)
		{
			printPeNiveluri();
		}
	}

	void printPreOrder(Node* nod)
	{
		if (nod == nil)
		{
			return;
		}
		if (nod->color == 1)
		{
			std::cout << ESC << WHITE_BKG << ";" << RED << "m" << nod->key << RESET << "\n";
		}
		else
		{
			std::cout << ESC << WHITE_BKG << ";" << BLACK << "m" << nod->key << RESET << "\n";
		}
		printPreOrder(nod->left);
		printPreOrder(nod->right);
	}

	void printInOrder(Node* nod)
	{
		if (nod == nil)
		{
			return;
		}
		printInOrder(nod->left);
		if (nod->color == 1)
		{
			std::cout << ESC << WHITE_BKG << ";" << RED << "m" << nod->key << RESET << "\n";
		}
		else
		{
			std::cout << ESC << WHITE_BKG << ";" << BLACK << "m" << nod->key << RESET << "\n";
		}
		printInOrder(nod->right);
	}

	void printPostOrder(Node* nod)
	{
		if (nod == nil)
		{
			return;
		}

		printPostOrder(nod->left);
		printPostOrder(nod->right);

		if (nod->color == 1)
		{
			std::cout << ESC << WHITE_BKG << ";" << RED << "m" << nod->key << RESET << "\n";
		}
		else
		{
			std::cout << ESC << WHITE_BKG << ";" << BLACK << "m" << nod->key << RESET << "\n";
		}

	}

	void printPeNiveluri()
	{
		Node* parinte;
		std::queue<Node*>coada;
		coada.push(root);
		while (coada.size() != 0)
		{
			if (coada.front()->color == 1)
			{
				std::cout << ESC << WHITE_BKG << ";" << RED << "m" << coada.front()->key << RESET << "\n";
			}
			else
			{
				std::cout << ESC << WHITE_BKG << ";" << BLACK << "m" << coada.front()->key << RESET << "\n";
			}
			if (coada.front()->left != nil)
			{
				coada.push(coada.front()->left);
			}
			if (coada.front()->right != nil)
			{
				coada.push(coada.front()->right);
			}
			coada.pop();
		}
	}

	void construct(std::vector<int>vector)
	{
		clear_tree();
		for (int i = 0; i < vector.size(); i++)
		{
			insert(vector[i]);
		}
	}

	void clear_tree()
	{
		if (root != nil)
		{
			std::queue<Node*>coada_de_noduri;
			Node* parinte = root;
			coada_de_noduri.push(parinte);
			while (coada_de_noduri.size() != 0)
			{
				parinte = coada_de_noduri.front();
				coada_de_noduri.pop();
				if (parinte->left != nil)
				{
					coada_de_noduri.push(parinte->left);
				}
				if (parinte->right != nil)
				{
					coada_de_noduri.push(parinte->right);
				}
				delete parinte;
			}
			root = nil;
		}
	}

	bool empty()
	{
		if (root != nil)
		{
			return true;
		}
		return false;
	}

	void print2DUtil(Node* root, int space, int COUNT = 10)
	{
		if (root == NULL)
			return;

		space += COUNT;

		print2DUtil(root->right, space);

		std::cout << std::endl;
		for (int i = COUNT; i < space; i++)
			std::cout << " ";
		if (root->color == 1)
		{
			std::cout << ESC << WHITE_BKG << ";" << RED << "m" << root->key << RESET << "\n";
		}
		else if (root != nil)
		{
			std::cout << ESC << WHITE_BKG << ";" << BLACK << "m" << root->key << RESET << "\n";
		}

		print2DUtil(root->left, space);
	}

	void print2D()
	{
		print2DUtil(root, 0);
	}

	Node* getNil()
	{
		return nil;
	}

};

void menu(ARN s)
{
	int op = 1, element;
	while (op != 0)
	{
		std::cout << std::endl;
		std::cout << "Meniu" << std::endl;
		std::cout << "1. Inserare" << std::endl;
		std::cout << "2. Cautare" << std::endl;
		std::cout << "3. Stergere" << std::endl;
		std::cout << "4. Minim" << std::endl;
		std::cout << "5. Maxim" << std::endl;
		std::cout << "6. Succesor" << std::endl;
		std::cout << "7. Predecesor" << std::endl;
		std::cout << "8. Afisare" << std::endl;
		std::cout << std::endl;

		std::cin >> op;

		std::cout << std::endl;

		switch (op)
		{
		case 1:
			std::cout << "Alege valoarea pe care vrei sa o inserezi: ";
			std::cin >> element;
			s.insert(element);
			break;
		case 2:
			std::cout << "Alege valoarea pe care vrei sa o cauti: ";
			std::cin >> element;
			if (s.find(element) != s.getNil())
			{
				std::cout << std::endl;
				std::cout << "Elementul a fost gasit";
				std::cout << std::endl;
			}
			else
			{
				std::cout << std::endl;
				std::cout << "Elementul NU a fost gasit";
				std::cout << std::endl;
			}
			break;
		case 3:
			std::cout << "Alege valoarea pe care vrei sa o stergi: ";
			std::cin >> element;
			s.erase_key(element);
			break;
		case 4:
			std::cout << "Cheia minima din arbore este " << s.getMinNode()->key;
			std::cout << std::endl;
			break;
		case 5:
			std::cout << "Cheia maxima din arbore este " << s.getMaxNode()->key;
			std::cout << std::endl;
			break;
		case 6:
			std::cout << "Citeste cheia pentru care doresti sa afli succesorul: ";
			std::cin >> element;
			std::cout << std::endl;
			if (s.getSuccesor(s.find(element)) != s.getNil())
			{
				std::cout << "Succesorul este " << s.getSuccesor(s.find(element))->key;
			}
			else std::cout << "Elementul nu are Succesor";
			std::cout << std::endl;
			break;
		case 7:
			std::cout << "Citeste cheia pentru care doresti sa afli predecesorul: ";
			std::cin >> element;
			std::cout << std::endl;
			if (s.getPredecessor(s.find(element)) != s.getNil())
			{
				std::cout << "Succesorul este " << s.getPredecessor(s.find(element))->key;
			}
			else std::cout << "Elementul nu are Predecesor";
			std::cout << std::endl;
			break;
		case 8:
			std::cout << "1. Afisare in PreOrdine" << std::endl;
			std::cout << "2. Afisare in InOrdine" << std::endl;
			std::cout << "3. Afisare in PostOrdine" << std::endl;
			std::cout << "4. Afisare pe Niveluri" << std::endl;
			std::cout << "Alege mod de afisare: ";
			std::cin >> element;
			std::cout << std::endl;
			s.print_tree(element);
			std::cout << std::endl;
			break;
		case 0:
		{
			break;
		}
		}
	}
}


int main()
{
	ARN a;
	a.insert(69);
	a.insert(55);
	a.insert(83);
	a.insert(29);
	a.insert(60);
	a.insert(32);
	a.insert(23);
	a.insert(59);
	a.insert(57);
	a.insert(26);
	a.print2D();
	return 0;
}