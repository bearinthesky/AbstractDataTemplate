#pragma once
typedef int Rank;
#define ListNodePosi(T) ListNode<T>*		//列表节点的位置，主要用指针指向前向节点和后继节点

template <typename T> struct ListNode {		//列表节点类，双向列表的形式表示
											//成员
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;
	//构造函数
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) :data(e), pred(p), succ(s) {
	}//传入一个值的构造函数
	 //操作接口
	ListNodePosi(T) insertAsPred(T const& e);
	ListNodePosi(T) insertAsSucc(T const& e);
};//ListNode

  //定义和声明对于模板来说是得在同一个头文件里面
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) {
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}

