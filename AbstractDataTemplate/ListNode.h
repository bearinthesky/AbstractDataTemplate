#pragma once
typedef int Rank;
#define ListNodePosi(T) ListNode<T>*		//�б�ڵ��λ�ã���Ҫ��ָ��ָ��ǰ��ڵ�ͺ�̽ڵ�

template <typename T> struct ListNode {		//�б�ڵ��࣬˫���б����ʽ��ʾ
											//��Ա
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;
	//���캯��
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) :data(e), pred(p), succ(s) {
	}//����һ��ֵ�Ĺ��캯��
	 //�����ӿ�
	ListNodePosi(T) insertAsPred(T const& e);
	ListNodePosi(T) insertAsSucc(T const& e);
};//ListNode

  //�������������ģ����˵�ǵ���ͬһ��ͷ�ļ�����
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

