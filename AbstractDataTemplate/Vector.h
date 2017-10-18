#pragma once
typedef int Rank;	//秩
#define DEFAULT_CAPACITY 3	//默认的最小的秩
#include <algorithm>
#include <cstdlib>

template <typename T> class Vector {	//向量模板类
protected:
	Rank _size;	//规模
	int _capacity;	//容量
	T* _elem;	//数据区
	void copyFrom(T const* A, Rank lo, Rank hi);	//赋值区间
	void expand();									//空间不足时扩容
	void shrink();									//填装因子过小时候压缩
	bool bubble(Rank lo, Rank hi);					//扫描交换
	void bubbleSort(Rank lo, Rank hi);				//冒泡排序算法
	Rank max(Rank lo, Rank hi);						//选取最大的元素
													//	void selectionSort(Rank lo, Rank hi);			//选择排序算法
	void merge(Rank lo, Rank mi, Rank hi);					//归并算法
	void mergeSort(Rank lo, Rank hi);				//归并排序算法
													//	Rank paitision(Rank lo, Rank hi);				//轴点构造算法
													//	void quickSort(Rank lo, Rank hi);				//快速排序算法
													//	void heapSort(Rank lo, Rank hi);				//堆排序算法（结合完全堆讲解）
public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)	//容量c, 规模s, 所有元素为v
	{
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
	}

	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }	//数组区间复制
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }	//数组整体复制
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }	//向量区间复制
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }	//向量复制
																	//析构函数
	~Vector() { delete[] _elem; }	//释放内部空间
									//只读访问接口
	Rank size()const { return _size; }	//规模
	bool empty() const { return !_size; }	//判空
	int disordered() const;
	//无序向量接口
	Rank find(T const& e) const { return find(e, 0, (Rank)_size); }	//无序向量整体查找
	Rank find(T const& e, Rank lo, Rank hi) const;	//无序向量区间查找
													//有序向量接口
	Rank search(T const& e) const { return (_size <= 0) ? -1 : search(e, (Rank)0, (Rank)_size); }	//有序向量整体查找
	Rank search(T const& e, Rank lo, Rank hi) const;	//有序向量区间查找
														//可写访问接口
	T& operator[](Rank r)const;	//重载下标操作符；可以类似于数组的形式引用个元素
	Vector<T>& operator = (Vector<T> const&);	//重载赋值操作符
	T remove(Rank r);	//删除秩为r的元素
	int remove(Rank lo, Rank hi);	//删除区间[lo,hi)的元素
	Rank insert(Rank r, T const& e);	//插入元素e到秩为r的位置
	Rank insert(T const& e) { return insert(_size, e); }	//末尾插入元素
	void sort(Rank lo, Rank hi);	//区间排序
	void sort() { sort(0, _size); }	//整体排序
	void unsort(Rank lo, Rank hi);	//对区间置乱
	void unsort() { unsort(0, _size); }	//对整体置乱
	int deduplicate();	//无序去重
	int uniquify();		//有序去重
						//遍历
	void traverse(void(*)(T&));		//遍历（使用函数指针，只读或局部性修改）
									//	template <typename VST> void traverse(VST&);	//遍历（使用函数对象，可全局修改）
};//Vector



  //定义


template <typename T> void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {	//以区间[lo,hi)为蓝本复制
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

template <typename T> Vector<T>& Vector<T>::operator = (Vector<T> const& V) {	//重载赋值运算符
	if (_elem) delete[] _elem;
	copyFrom(V, 0, V._size);
	return *this;
}

template <typename T> void Vector<T>::expand() {	//向量空间容量不足是扩容
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;
	T* oldelem = _elem; _elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)					//复制原空间的内容
		_elem[i] = oldelem[i];
	delete[] oldelem;								//释放原空间
}

template <typename T> void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1)return;			//低于2倍最低容量的不用缩容
	if (size << 2 > _capacity)return;						//高于0.25的不比缩容
	T* oldelem = _elem; _elem = new T[_capacity >> 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;
}

template <typename T> T& Vector<T>::operator[](Rank r)const {
	return _elem[r];	//此处最好严格处理一下r，0<=r<_size
}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) {	//随机均匀置乱算法接口
	T* V = _elem + lo;
	for (int i = hi - lo, i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

template <typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {		//无序向量顺序查找
	while ((lo < hi--) && (e != _elem[hi]));										//从最后往前
	return hi;
}

template <typename T> Rank Vector<T>::insert(Rank r, T const& e) {					//插入元素
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = elem[i - 1];
	return r;
}

template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) {					//删除区间元素
	if (lo == hi)return 0;
	while (high < _size)_elem[lo++] = elem[high++];
	_size = lo;
	shrink();
	return hi - lo;
}



template <typename T> T Vector<T>::remove(Rank r) {									//删除单个元素
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T> int Vector<T>::deduplicate() {								//去重操作
	int oldsize = _size;
	Rank i = 1;
	while (i < _size)(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldsize - _size;
}

template <typename T> void Vector<T>::traverse(void(*visit)(T&)) {					//对向量中的每个元素进行操作
	for (int i = 0; i < _size; i++)visit(_elem[i]);
}

/*
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit)
{
for (int i = 0; i < _size; i++)visit(_elem[i]);
}
*/

template <typename T> int Vector<T>::disordered()const {							//先判断是否有序的函数
	int n = 0;
	for (int i = 1; i < _size; i++)
		if (_elem[i - 1] > _elem[i])n++;
	return n;				//n=0代表有序
}
/*
template <typename T> int Vector<T>::uniquify() {						//低效版。。。有序向量剔除重复元素
int oldsize = _size; int i = 0;
while (i < _size - 1)
(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;				//删除相同元素，保留第一个该值的元素
return oldsize - _size;
}
*/

template <typename T> int Vector<T>::uniquify() {						//高效版。。。有序向量剔除重复元素
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[i++] = _elem[j];
	_size = i++; shrink();
	return j - i;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const {				//查找接口，随机选取二分查找或者fibnacci查找
	binSearch(_elem, e, lo, hi);
}
/*
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {		//版本A 二分查找O(logn)
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
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {		//版本B,均衡的二分查找
while (1 < hi - lo) {
Rank mi = (lo + hi) >> 1;
(e < A[mi]) ? hi = mi : lo = mi;
}
return (e == A[lo]) ? lo : -1;
}
*/
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {//版本C，查找失败返回一个合理的符合有序向量语义的秩
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}
template <typename T> void Vector<T>::sort(Rank lo, Rank hi) {		//排序接口
																	//	switch(rand() % 5) {
																	//		case 1: bubbleSort(lo, hi); break;			//冒泡排序
																	//		case 2: selectionSort(lo, hi); break;		//选择排序
																	//		case 2: mergeSort(lo, hi); break;			//归并排序
																	//		case 4: heapSort(lo, hi); break;			//堆排序
																	//		default: quickSort(lo, hi); break;			//快速排序
																	//	}
	(rand() % 2) ? bubbleSort(lo, hi) : mergeSort(lo, hi);
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi--));		//只要冒泡了，就还得继续扫描。
}

template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi) {	//一趟扫描，冒一个气泡
	bool sorted = true;
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) {
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

template <typename T>	//归并排序
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2)return;
	Rank mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);	//二路归并，理解成最底下的两个单个的元素调用二路归并返回，在调用二路归并，一直就这样下去。
}

template <typename T>  //二路归并接口
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T* A = _elem + lo;
	int lb = mi - lo;
	int lc = hi - mi;
	T* B = new T[lb]; for (int i = 0; i < lb; i++)B[i] = A[i];
	T* C = _elem + mi;
	for (Rank i = 0, j = 0, k = 0; (j < lb || k < lc);) {	//j,k,作为两路的头，i作为A的尾巴。
		if ((j < lb) && (!(k < lc) || (B[j] < C[k])))A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] < B[j])))A[i++] = C[k++];
	}
	delete[] B;	//释放原有空间很重要
}


