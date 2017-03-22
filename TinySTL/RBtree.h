#pragma once
#ifndef RBTREE
#define RBTREE

#include<iostream>
#include<iterator>
#include<algorithm>

#include"allocator.h"


namespace TinySTL
{
	enum RB{red,black};

	template<class T>
	class RBtree_iterator;

	template <class T>
	class RBtree_node
	{
	public:
		T data;
		RB color;
		RBtree_node* left;
		RBtree_node* right;
		RBtree_node* parent;


		RBtree_node() {}
		RBtree_node(T Data,RB Color, RBtree_node*Left=0, RBtree_node* Right=0, RBtree_node*Parent=0):
							data(Data),color(Color),left(Left),right(Right),parent(Parent) {}
	};

	template<class T>
	void leftRotate(RBtree_node<T>* x)
	{

		RBtree_node<T>* y = x->right;
		RBtree_node<T>* b = y->left;
		RBtree_node<T>* p = x->parent;

		b->parent = x;
		x->right = b;

		if (x == p->left)
		{
			p->left = y;
		}
		else
		{
			p->right = y;
		}

		x->parent = y;
		y->left = x;
		y->parent = p;
	}

	template<class T>
	void rightRotate(RBtree_node<T>* x)
	{

		RBtree_node<T>*y = x->left;
		RBtree_node<T>*b = y->right;
		RBtree_node<T>*p = x->parent;

		x->left = b;
		b->parent = x;

		if (x == p->left)
		{
			p->left = y;
		}
		else
		{
			p->right = y;
		}

		x->parent = y;
		y->right = x;
		y->parent = p;
	}

	template<class T>
	class RBtree
	{
		//							root == nil->left
		friend class RBtree_iterator<T>;
		typedef RBtree_node<T> node;
		node* nil;
		size_t num;
		allocator<node > alloc;
		node* next(node*item)
		{
			if (item->right == nil)
			{
				node* mov = item;
				while (mov != nil)
				{
					node*p = mov->parent;
					if (mov == p->left)
					{
						return p;
					}
					mov = p;
				}
				return nil;
			}
			else
			{
				node*mov = item->right;
				node*p = mov;
				while (mov != nil)
				{
					p = mov;
					mov = mov->left;
				}
				return p;
			}
		}
		node* pre(node*item)
		{
			if (item->left == nil)
			{
				node* mov = item;
				while (mov != nil)
				{
					node*p = mov->parent;
					if (mov == p->right)
					{
						return p;
					}
					mov = p;
				}
				return nil;
			}
			else
			{
				node*mov = item->left;
				node*p = mov;
				while (mov != nil)
				{
					p = mov;
					mov = mov->right;
				}
				return p;
			}
		}
		void insert_fix(node* x)
		{
			while (x!=nil->left)
			{
				node* p = x->parent;
				if (p->color == black)return;
				node*pp = p->parent;
				if (p == pp->left)
				{
					node*u = pp->right;
					if (u->color == red)		//case 1
					{
						u->color = black;
						p->color = black;
						pp->color = red;
						x = pp;
						continue;
					}
					else
					{
						if (x == p->right)		//case 2
						{
							leftRotate(p);
							p = x;
							x = x->parent;
						}
						rightRotate(pp);		//case 3
						p->color = black;
						pp->color = red;
					}
				}
				else
				{
					node*u = pp->left;
					if (u->color == red)		//case 1
					{
						u->color = black;
						p->color = black;
						pp->color = red;
						x = pp;
						continue;
					}
					else
					{
						if (x == p->left)		//case 2
						{
							rightRotate(p);
							p = x;
							x = x->parent;
						}
						leftRotate(pp);			//case 3
						p->color = black;
						pp->color = red;
					}
				}
			}
			nil->left->color = black;
		}
		void erase_fix(node* x)
		{
			while (x != nil->left && x->color != red)
			{
				node* p = x->parent;
				if (x == p->left)
				{
					node*b = p->right;
					if (b->color == red)			//case 1
					{
						b->color = p->color;
						p->color = red;
						leftRotate(p);
						b = p->right;
					}
					if (b->left->color == black && b->right->color == black)		//case 2
					{
						b->color = red;
						x = p;
						continue;
					}
					if (b->left->color == red && b->right->color == black)			//case 3
					{
						rightRotate(b);
						b = p->right;
					}
					if (b->right->color==red)			//case 4
					{
						RB temp = p->color;			//swap p[color] and b[color]
						p->color = b->color;
						b->color = temp;
						b->right->color = black;
						leftRotate(p);
						break;
					}
				}
				else
				{
					node*b = p->left;
					if (b->color == red)			//case 1
					{
						b->color = p->color;
						p->color = red;
						rightRotate(p);
						b = p->left;
					}
					if (b->right->color == black && b->left->color == black)		//case 2
					{
						b->color = red;
						x = p;
						continue;
					}
					if (b->right->color == red && b->left->color == black)			//case 3
					{
						leftRotate(b);
						b = p->left;
					}
					if (b->left->color==red)			//case 4
					{
						RB temp = p->color;			//swap p[color] and b[color]
						p->color = b->color;
						b->color = temp;
						b->left->color = black;
						rightRotate(p);
						break;
					}
				}
			}
			x->color = black;
		}
		void copy_aux(node* source,node* dest,node* const snil)
		{
			if (source == snil)return;
			node* temp = alloc.allocate(1);
			node* sp = source->parent;
			alloc.construct(temp, node(source->data, source->color, nil, nil, dest));
			if (source == sp->left)dest->left = temp;
			else dest->right = temp;
			copy_aux(source->left, temp,snil);
			copy_aux(source->right, temp,snil);
		}
		void clear_aux(node* item)
		{
			if (item == nil)return;
			clear_aux(item->left);
			clear_aux(item->right);
			alloc.destroy(item);
			alloc.deallocate(item);
		}
		node* search(const T& item)const //different from find,search return node,while find return iterator
		{
			node* mov = nil->left;
			while (mov != nil)
			{
				if (item > mov->data)mov = mov->right;
				else if (item == mov->data)break;
				else mov = mov->left;
			}
			return mov;

		}
		

	public:
		typedef RBtree_iterator<T> iterator;
		
		RBtree() :num(0)
		{
			nil = alloc.allocate(1);
			alloc.construct(nil, node(T(), black, nil, nil, nil));
		}
		RBtree(std::initializer_list<T> list) :num(list.size())
		{
			nil = alloc.allocate(1);
			alloc.construct(nil, node(T(), black, nil, nil, nil));
			nil->left = nil;
			for (auto mov = list.begin(); mov != list.end(); ++mov)
			{
				insert(*mov);
			}
		}
		RBtree(const RBtree& item)
		{
			nil = alloc.allocate(1);
			alloc.construct(nil, node(T(), black, nil, nil, nil));
			nil->left = nil;
			copy_aux(item.nil->left, nil, item.nil);
		}

		RBtree& operator=(const RBtree& item)
		{
			clear();
			copy_aux(item.nil->left, nil, item.nil);
			return *this;
		}
		iterator begin()
		{
			node* mov = nil->left;
			node* p = mov;
			while (mov != nil)
			{
				p = mov;
				mov = mov->left;
			}
			return iterator(p, this);
		}
		iterator end()
		{
			return iterator(nil, this);
		}
		size_t size()const { return num; }

		bool empty()const { return nil->left == nil; }
		void clear()
		{
			clear_aux(nil->left);
			nil->left = nil;
			nil->right = nil;
			nil->parent = nil;

		}
		void erase(node* x)
		{
			if (x == nil) //test
			{
				std::cerr << "delete nil";
				system("puase");
			}

			if (x->left != nil && x->right != nil)
			{
				node* n = next(x);
				T temp = x->data;
				x->data = n->data;
				n->data = temp;
				erase(n);
				return;
			}
			node*p = x->parent;
			node*son = x->left == nil ? x->right : x->left;
			if (x == p->left)p->left = son;
			else p->right = son;
			son->parent = p;
			if (x->color == black)erase_fix(son);
			alloc.destroy(x);
			alloc.deallocate(x);
			--num;
		}
		void erase(const T& item)
		{
			node* temp = search(item);
			if (temp != nil)erase(temp);
		}
		void erase(iterator item)
		{
			erase(item.node);
		}
		void insert(const T& item)
		{
			++num;
			if (empty())
			{
				nil->left = alloc.allocate(1);
				alloc.construct(nil->left, node(item, black, nil, nil, nil));
				nil->left = nil->left;
				nil->right = nil->left;
				return;
			}
			else
			{
				node* p = nil->left;
				node* mov = nil->left;
				while (mov != nil)
				{
					p = mov;
					if (item > p->data)
					{
						mov = p->right;
					}
					else
					{
						mov = p->left;
					}
				}

				mov = alloc.allocate(1);
				alloc.construct(mov, node(item, red, nil, nil, p));
				if (item > p->data)p->right = mov;
				else p->left = mov;
				insert_fix(mov);
			}
		}
		iterator find(const T& item)
		{
			node* temp = search(item);
			iterator res(temp,this);
			return res;
		}

		iterator lower_bound(const T& item)
		{
			
			if (empty())return iterator(nil,this);
			node* p = nil->left;
			node* mov = nil->left;
			iterator res(p, this);
			while (mov != nil)
			{
				if (mov->data>=item)
				{
					if (mov->data <= *res)
					{
						res = iterator(mov, this);
					}
				}
				p = mov;
				if (item > p->data)
				{
					mov = p->right;
				}
				else
				{
					mov = p->left;
				}

			}
			return res;

		}
		iterator upper_bound(const T& item)
		{
			if (empty())return iterator(nil, this);
			node* p = nil->left;
			node* mov = nil->left;
			iterator res=--end();
			while (mov != nil)
			{
				if (mov->data>item)
				{
					if (mov->data <= *res)
					{
						res = iterator(mov, this);
					}
				}
				p = mov;
				if (item >= p->data)
				{
					mov = p->right;
				}
				else
				{
					mov = p->left;
				}

			}
			return res;
		}
		size_t count(const T& item)
		{
			iterator start = lower_bound(item);
			iterator finish = upper_bound(item);
			size_t res = 0;
			while (start != finish)
			{
				++res;
				++start;
			}
			return res;
		}

		~RBtree()
		{
			clear();
			alloc.deallocate(nil);
		}

		void print(node* item) //test
		{
			if (item == 0)item = nil->left;
			if (item == nil)return;
			std::cout << item->data;
			if (item->color == red)std::cout << "red"<<"   ";
			else std::cout << "black" << "   ";
			print(item->left);
			print(item->right);
		}
	};

	template<class T>
	class RBtree_iterator:public std::iterator<std::bidirectional_iterator_tag,T>
	{
		friend class RBtree<T>;
		typedef RBtree<T>					container;
		typedef RBtree_iterator<T>    self;
		RBtree_node<T>* node;
		container* tree;

	public:
		RBtree_iterator() {}
		RBtree_iterator(RBtree_node<T>* Node, container* Tree) :node(Node), tree(Tree) {}
		self& operator++()
		{
			node = tree->next(node);
			return *this;
		}
		self    operator++(int)
		{
			RBtree_node<T>* temp= tree->next(node);
			return temp;
		}
		self& operator--()
		{
			node = tree->pre(node);
			return *this;
		}
		self    operator--(int)
		{
			RBtree_node<T>* temp = tree->pre(node);
			return temp;
		}
		T&     operator*()
		{
			return (*(&(node->data)));
		}
		T*		  operator->()
		{
			return (&(node->data));
		}
		bool  operator==(const self& item)
		{
			return node == item.node;
		}
		bool  operator!=(const self& item)
		{
			return node != item.node;
		}


	};


}

#endif // !RBTREE


