#pragma once
typedef int Rank;	//��
#define DEFAULT_CAPACITY 3	//Ĭ�ϵ���С����
#include <algorithm>
#include <cstdlib>

template <typename T> class Vector {	//����ģ����
protected:
	Rank _size;	//��ģ
	int _capacity;	//����
	T* _elem;	//������
	void copyFrom(T const* A, Rank lo, Rank hi);	//��ֵ����
	void expand();									//�ռ䲻��ʱ����
	void shrink();									//��װ���ӹ�Сʱ��ѹ��
	bool bubble(Rank lo, Rank hi);					//ɨ�轻��
	void bubbleSort(Rank lo, Rank hi);				//ð�������㷨
	Rank max(Rank lo, Rank hi);						//ѡȡ����Ԫ��
													//	void selectionSort(Rank lo, Rank hi);			//ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi);					//�鲢�㷨
	void mergeSort(Rank lo, Rank hi);				//�鲢�����㷨
													//	Rank paitision(Rank lo, Rank hi);				//��㹹���㷨
													//	void quickSort(Rank lo, Rank hi);				//���������㷨
													//	void heapSort(Rank lo, Rank hi);				//�������㷨�������ȫ�ѽ��⣩
public:
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)	//����c, ��ģs, ����Ԫ��Ϊv
	{
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
	}

	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }	//�������临��
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }	//�������帴��
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }	//�������临��
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }	//��������
																	//��������
	~Vector() { delete[] _elem; }	//�ͷ��ڲ��ռ�
									//ֻ�����ʽӿ�
	Rank size()const { return _size; }	//��ģ
	bool empty() const { return !_size; }	//�п�
	int disordered() const;
	//���������ӿ�
	Rank find(T const& e) const { return find(e, 0, (Rank)_size); }	//���������������
	Rank find(T const& e, Rank lo, Rank hi) const;	//���������������
													//���������ӿ�
	Rank search(T const& e) const { return (_size <= 0) ? -1 : search(e, (Rank)0, (Rank)_size); }	//���������������
	Rank search(T const& e, Rank lo, Rank hi) const;	//���������������
														//��д���ʽӿ�
	T& operator[](Rank r)const;	//�����±�������������������������ʽ���ø�Ԫ��
	Vector<T>& operator = (Vector<T> const&);	//���ظ�ֵ������
	T remove(Rank r);	//ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi);	//ɾ������[lo,hi)��Ԫ��
	Rank insert(Rank r, T const& e);	//����Ԫ��e����Ϊr��λ��
	Rank insert(T const& e) { return insert(_size, e); }	//ĩβ����Ԫ��
	void sort(Rank lo, Rank hi);	//��������
	void sort() { sort(0, _size); }	//��������
	void unsort(Rank lo, Rank hi);	//����������
	void unsort() { unsort(0, _size); }	//����������
	int deduplicate();	//����ȥ��
	int uniquify();		//����ȥ��
						//����
	void traverse(void(*)(T&));		//������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
									//	template <typename VST> void traverse(VST&);	//������ʹ�ú������󣬿�ȫ���޸ģ�
};//Vector



  //����


template <typename T> void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {	//������[lo,hi)Ϊ��������
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

template <typename T> Vector<T>& Vector<T>::operator = (Vector<T> const& V) {	//���ظ�ֵ�����
	if (_elem) delete[] _elem;
	copyFrom(V, 0, V._size);
	return *this;
}

template <typename T> void Vector<T>::expand() {	//�����ռ���������������
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;
	T* oldelem = _elem; _elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)					//����ԭ�ռ������
		_elem[i] = oldelem[i];
	delete[] oldelem;								//�ͷ�ԭ�ռ�
}

template <typename T> void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1)return;			//����2����������Ĳ�������
	if (size << 2 > _capacity)return;						//����0.25�Ĳ�������
	T* oldelem = _elem; _elem = new T[_capacity >> 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;
}

template <typename T> T& Vector<T>::operator[](Rank r)const {
	return _elem[r];	//�˴�����ϸ���һ��r��0<=r<_size
}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) {	//������������㷨�ӿ�
	T* V = _elem + lo;
	for (int i = hi - lo, i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

template <typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {		//��������˳�����
	while ((lo < hi--) && (e != _elem[hi]));										//�������ǰ
	return hi;
}

template <typename T> Rank Vector<T>::insert(Rank r, T const& e) {					//����Ԫ��
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = elem[i - 1];
	return r;
}

template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) {					//ɾ������Ԫ��
	if (lo == hi)return 0;
	while (high < _size)_elem[lo++] = elem[high++];
	_size = lo;
	shrink();
	return hi - lo;
}



template <typename T> T Vector<T>::remove(Rank r) {									//ɾ������Ԫ��
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T> int Vector<T>::deduplicate() {								//ȥ�ز���
	int oldsize = _size;
	Rank i = 1;
	while (i < _size)(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldsize - _size;
}

template <typename T> void Vector<T>::traverse(void(*visit)(T&)) {					//�������е�ÿ��Ԫ�ؽ��в���
	for (int i = 0; i < _size; i++)visit(_elem[i]);
}

/*
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit)
{
for (int i = 0; i < _size; i++)visit(_elem[i]);
}
*/

template <typename T> int Vector<T>::disordered()const {							//���ж��Ƿ�����ĺ���
	int n = 0;
	for (int i = 1; i < _size; i++)
		if (_elem[i - 1] > _elem[i])n++;
	return n;				//n=0��������
}
/*
template <typename T> int Vector<T>::uniquify() {						//��Ч�档�������������޳��ظ�Ԫ��
int oldsize = _size; int i = 0;
while (i < _size - 1)
(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;				//ɾ����ͬԪ�أ�������һ����ֵ��Ԫ��
return oldsize - _size;
}
*/

template <typename T> int Vector<T>::uniquify() {						//��Ч�档�������������޳��ظ�Ԫ��
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[i++] = _elem[j];
	_size = i++; shrink();
	return j - i;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const {				//���ҽӿڣ����ѡȡ���ֲ��һ���fibnacci����
	binSearch(_elem, e, lo, hi);
}
/*
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {		//�汾A ���ֲ���O(logn)
while (lo < hi) {
Rank mi = (lo + hi) >> 1);
if (e < A[mi])hi = mi;
else if (A[mi] < e)lo = mi + 1;
else return mi;
}
return -1;
}
*/
/*
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {		//�汾B,����Ķ��ֲ���
while (1 < hi - lo) {
Rank mi = (lo + hi) >> 1;
(e < A[mi]) ? hi = mi : lo = mi;
}
return (e == A[lo]) ? lo : -1;
}
*/
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {//�汾C������ʧ�ܷ���һ������ķ������������������
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}
template <typename T> void Vector<T>::sort(Rank lo, Rank hi) {		//����ӿ�
																	//	switch(rand() % 5) {
																	//		case 1: bubbleSort(lo, hi); break;			//ð������
																	//		case 2: selectionSort(lo, hi); break;		//ѡ������
																	//		case 2: mergeSort(lo, hi); break;			//�鲢����
																	//		case 4: heapSort(lo, hi); break;			//������
																	//		default: quickSort(lo, hi); break;			//��������
																	//	}
	(rand() % 2) ? bubbleSort(lo, hi) : mergeSort(lo, hi);
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi--));		//ֻҪð���ˣ��ͻ��ü���ɨ�衣
}

template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi) {	//һ��ɨ�裬ðһ������
	bool sorted = true;
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) {
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

template <typename T>	//�鲢����
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2)return;
	Rank mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);	//��·�鲢����������µ�����������Ԫ�ص��ö�·�鲢���أ��ڵ��ö�·�鲢��һֱ��������ȥ��
}

template <typename T>  //��·�鲢�ӿ�
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T* A = _elem + lo;
	int lb = mi - lo;
	int lc = hi - mi;
	T* B = new T[lb]; for (int i = 0; i < lb; i++)B[i] = A[i];
	T* C = _elem + mi;
	for (Rank i = 0, j = 0, k = 0; (j < lb || k < lc);) {	//j,k,��Ϊ��·��ͷ��i��ΪA��β�͡�
		if ((j < lb) && (!(k < lc) || (B[j] < C[k])))A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] < B[j])))A[i++] = C[k++];
	}
	delete[] B;	//�ͷ�ԭ�пռ����Ҫ
}


