#pragma once
#include <iostream>

template<typename T> class LinkList;
template<typename Node> class ListIterator;

//Шаблонный класс для хранения элементов и их указателей
template<typename T>
class node
{
public:
	using Value = typename T;

	node() : m_data(), m_next(this) {}
	node(Value* data) : m_data(data) { m_next = this; }
	node(Value* data, node* next) : m_data(data), m_next(next) {}

	~node() { delete m_data; }

	//функции получения значений

	//указатуль на следующий элемент в списке
	node* next() const { return m_next; }
	//даные
	Value* data() const { return m_data; }

	//функции установки значений
	void setData(Value* data) { m_data = data; }
	void setNext(node* next) { m_next = next; }

private:
	node* m_next;
	Value* m_data;
};

//Класс итератора для упращения обхода элементов
template<typename Node>
class ListIterator
{
	using ValueType = typename Node::Value;
public:

	ListIterator(Node* data = nullptr) : m_ptr(data) {}

	//Перегруженные операторы
	//operator Node() { return m_ptr; }
	ValueType& operator*() { return *m_ptr->data(); }
	Node* operator->() { return m_ptr; }
	bool operator==(const ListIterator& rightIter) { return m_ptr == rightIter.m_ptr; }
	bool operator!=(const ListIterator& rightIter) { return m_ptr != rightIter.m_ptr; }
	bool operator==(Node* rightPtr) { return m_ptr == rightPtr; }
	bool operator!=(Node* rightPtr) { return m_ptr != rightPtr; }
	bool operator!() { return !m_ptr; }
	operator ValueType* () { return m_ptr->data(); }
	ListIterator operator++(int) 
	{
		if (m_ptr == nullptr) return *this;

		ListIterator temp = *this;
		++(*this);
		return temp;
	}
	ListIterator operator++() 
	{
		if (m_ptr == nullptr) return *this;
		m_ptr = m_ptr->next();
		return *this; 
	}

	//Чтобы не добавлять класс как дружественный в LinkList<T>, функция объявлена как public
	Node* _getPtr() const { return m_ptr; }

private:
	Node* m_ptr;
};

//Класс циклического списка
template<typename T> 
class LinkList
{
	using Node = node<T>;
	friend class Node;
public:
	using iterator = ListIterator<Node>;

	LinkList() : m_begin(nullptr), m_size(0) {}
	//Конструктор копирования
	LinkList(const LinkList<T>& li)
	{
		LinkList<T>::iterator it = li.begin();
		LinkList<T>::iterator thisIt;
		thisIt = insert(begin(), *it++);
		while (it != li.begin()) 
			thisIt = insert(thisIt, *it++);
	}
	~LinkList()
	{
		clear();
		_CrtDumpMemoryLeaks();
	}

	//служебные методы возвращают размер списка, 
	//проверку на пустоту списка и итератор на начало соответственно
	int size() const { return m_size; }
	bool isEmpty() const { return !m_size; }
	iterator begin() const { return iterator(m_begin); }

	LinkList<T>& operator=(const LinkList<T>& li)
	{
		if (this == &li)
			return *this;

		LinkList<T>::iterator it = li.begin();
		LinkList<T>::iterator thisIt;

		thisIt = insert(begin(), *it++);
		while(it != li.begin())
			thisIt = insert(thisIt, *it++);

		return *this;
	}
	bool operator==(const LinkList<T>& li)
	{
		bool isEqual = true;
		if (li.size() != size())
			return false;

		LinkList<T>::iterator it = li.begin();
		LinkList<T>::iterator thisIt = begin();

		if (*it++ == *thisIt++) isEqual = false;
		while (it != li.begin() || isEqual != false)
			if (*it++ == *thisIt++) isEqual = false;
		return isEqual;
	}
	/*
	* Произовдит вставку в связанный список после элемента,
	* на который указывает итератор pos
	* Возвращает итератор, указывающий на вставленный элемент
	*/
	iterator insert(iterator pos, const T& elem)
	{
		//Проверка недействительность переданного итератора
		//Если итератор недействителен и список пуст, то итератор указывает 
		//на начало списка и необходимо создание первого элемента
		//Иначе передан недействительный итератор (функция возвращает 
		//переданный недействительный итератор)
		if (!pos) {
			if (!isEmpty())
				return pos;
			m_begin = new Node(new T(elem));
			++m_size;
			return iterator(m_begin);
		}

		//Вставка нового элемена 
		pos->setNext(new Node(new T(elem), pos->next()));
		++m_size;
		return iterator(pos->next());
	}

	/*
	* Производит удаление элемента следующего за тем, на который указывает итератор pos из списка
	* Возвращает итератор на элемент перед удаляемым
	* Передаваемый в функцию итератор становится недействительным
	*/
	iterator erase_after(iterator pos)
	{
		if (pos->next() == m_begin) {
			m_begin = m_begin->next();
		}
		Node* iter = pos._getPtr();
		Node* newNext = iter->next()->next();
		delete iter->next();
		iter->setNext(newNext);
		--m_size;
		return iterator(iter);
	}

	/*
	* Производит удаление элемента, на который указывает итератор pos из списка
	* Возвращает итератор на элемент после удаляемого
	* Передаваемый в функцию итератор становится недействительным
	*/
	iterator erase(iterator pos)
	{
		//проверяем, является ли элемент первым
		//если это так передвигаем указатель на начало на один элемент вперед
		if (pos == begin())
			m_begin = m_begin->next();

		Node* iter = pos._getPtr();
		//поиск элемент предшествующий данному
		while (pos != iter->next())
			iter = iter->next();

		//Сохранение элемента следующего за данным
		Node* newNext = iter->next()->next();
		//Удаляем переданный в функцию элемент
		delete iter->next();
		//Связываем разорванный список
		iter->setNext(newNext);
		--m_size;
		return iterator(newNext);
	}

	//очищает связанный список
	void clear()
	{
		Node* iter = m_begin;
		while (!isEmpty()) {
			if (iter->next() == m_begin) {
				m_begin = m_begin->next();
			}

			Node* newNext = iter->next()->next();
			delete iter->next();
			iter->setNext(newNext);
			--m_size;
		}
	}

	/*
	* Производит поиск элемента elem в связанном списке
	* Возвращает итератор на (нужно чтобы на предидущий) найденный элемент, если элемент elem есть в списке
	* Иначе возвращает итератор на начало списка
	*/
	iterator find(const T& elem)
	{
		//если списко пуст поиск не имеет смысла
		if (isEmpty())
			return begin();
		//Если искомый элемент равен первому возвратить его
		if (elem == *m_begin->data())
			return begin();
		//Итераторы для обхода списка
		iterator beg = begin();
		iterator it = beg;
		//В цикле с передаваемым значением сравниваются все элементы кроме первого
		//Если элемент не найден, возвращается итератор на начало списка
		while (++it != beg) {
			if(*it == elem)
				return it;
		}
		return beg;
	}

private:
	Node* m_begin;
	int m_size;
};