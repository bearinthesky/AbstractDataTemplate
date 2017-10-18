#pragma once
#include "ListNode.h"

template <typename T> class List {
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T), int);
	void merge(ListNodePosi(T), int, List<T>&, ListNodePosi(T), int);
	void mergeSort(ListNodePosi(T)&, int);
	void selectionSort(ListNodePosi(T), int);
	void insertionSort(ListNodePosi(T), int);

public:
//构造函数
	List() { init(); }							//默认初始化
	List(List<T> const& L);						//整体复制列表初始化
	void copyNodes(ListNodePosi(T) p, int n);	//复制n数字
	void copyNodes(ListNodePosi(T) p, Rank r, int n)	//从第r项开始复制n个
//析构函数
	~List();
//只读访问接口
	Rank size() const { return _size; }
	bool empty() const { return _size < 0; }
	T& operator[](int r)const;
	ListNodePosi(T) first()const { return head->succ; }
	ListNodePosi(T) last()const { return trailer->pred;}
	bool valid(ListNodePosi(T) p) { return p && (trailer != p) && (header != p); }
	int disordered()const;
	ListNodePosi(T) find(T const& e)const { return find(e, _size, trailer); }
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p)const;
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p)const;
	ListNodePosi(T) search(T cosst& e)const { return search(e, _size, trailer); }
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }
//可写访问接口
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T)	insertAsLast(T const& e);
	ListNodePosi(T)	insertBefore(ListNodePosi(T) p, T const& e);
	ListNodePosi(T)	insertAfter(ListNodePosi(T)p, T const& e);
	T remove(ListNodePosi(T) p);
	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); }
	void sort(ListNodePosi(T) p, int n);
	void sort() { sort(L.first(), _size);}
	int deduplicate();
	int uniquify();
	void reverse();
//遍历
	void traverse(void(*)(T&));				//利用函数指针遍历列表
	template <typename VST>					//利用函数对象遍历列表
	void traverse(VST&);
};

template <typename T> List<T>::List(ListNodePosi(T) p, int n) {
	copyNodes(p, n);
}

template <typename T> void List<T>::init() {//列表初始化，在创建列表对象时统一调用
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	trailer->pred = header;
	header->pred = nullptr;
	trailer->succ = nullptr;
	_size = 0;
}

template <typename T> void List<T>::copyNodes(ListNodePosi(T) p, int n) {
	init();
	while (n--) {
		insertAsLast(p->data);
		p = p->succ;
	}
}

template <typename T> List<T>::List(List<T> const& L) {
	copyNodes(L.first(), L._size);
}

template <typename T> List<T>::List(List<T> const& L, int r, int n) {
	copyNodes(L[r], n);
}

template <typename T>
T& List<T>::operator[](int r)const {
	ListNodePosi(T) p = first();
	while (0 < r--) {
		p = p->succ;
	}
	return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) {
	while (0 < n--) {
		if (e == (p = p->pred)->data)return p;
	}
	return nullptr;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e) {
	_size++;
	return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e) {
	_size++;
	return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const& e) {
	_size++;
	return p->insertAsPred(e);

}

template <typename T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const& e) {
	_size++;
	return p->insertAsSucc(e);
}

template <typename T> T List<T>::remove(ListNodePosi(T) p) {
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template <typename T> List<T>::~List() {
	clear();
	delete header;
	delete trailer;
}

template <typename T> int List<T>::clear() {
	int oldSize = _size;
	while (0 < _size) {
		remove(header->succ);
	}
	return oldSize;
}

template <typename T> int List<T>::deduplicate() {
	if (_size < 2)return 0;
	int oldSize = _size;
	ListNodePosi(T) p = header; Rank r = 0;
	while (trailer != (p = p->succ)) {
		ListNodePosi(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template <typename T> void List<T>::traverse(void(*)(T&)) {		//函数指针的形式
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
 }

template <typename T> template <typename VST>
void List<T>::traverse(VST& visit) {
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

template <typename T> 




































