#ifndef _MYSORTS_2020_
#define _MYSORTS_2020_

#include <utility>
#include <ctime>

#ifdef SORTSTAT
#include <iostream>
#endif

template <typename T>
void BubbleSort(T* M, int n) {
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t tiktok = clock();
#endif	
	for (int j = 0; j < n - 1; ++j) {
		bool isSorted = true;
		for (int i = n - 1; i > j; --i) {
#ifdef SORTSTAT			
			++c1;
#endif			
			if (M[i] < M[i - 1]) {
				std::swap(M[i], M[i - 1]); // int tmp = M[i]; M[i] = M[i - 1]; M[i - 1] = tmp;
#ifdef SORTSTAT			
				c2 += 3;
#endif				
				isSorted = false;
			}
		}
		if (isSorted) break;
	}

#ifdef SORTSTAT
	tiktok = clock() - tiktok;
	std::cout << "<" << c1 << ", =" << c2 << ", tics: " << tiktok << std::endl;
#endif
}


template <typename T>
void ChooseSort(T* M, int n) {
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t tiktok = clock();
#endif	

	for (int j = 0; j < n - 1; ++j) {
		int k = j; // индекс минимального элемента
		for (int i = k + 1; i < n; ++i) {
#ifdef SORTSTAT			
			++c1;
#endif
			if (M[i] < M[k])
				k = i;
		}
		if (j < k) {
			std::swap(M[k], M[j]);
#ifdef SORTSTAT			
			c2 += 3;
#endif	
		}
	}

#ifdef SORTSTAT
	tiktok = clock() - tiktok;
	std::cout << "<" << c1 << ", =" << c2 << ", tics: " << tiktok << std::endl;
#endif
}


template <typename T>
void InsertSort(T* M, int n) {
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t tiktok = clock();
#endif	
	T tmp;
	int i, j;
	for (j = 1; j < n; ++j) {
#ifdef SORTSTAT			
		++c2;
#endif
		tmp = M[j];
		for (i = j; i > 0; --i) {
#ifdef SORTSTAT			
			++c1;
#endif
			if (tmp < M[i - 1]) {
				M[i] = M[i - 1];
#ifdef SORTSTAT			
				++c2;
#endif
			}
			else
				break;
		}
		if (i != j) {
			M[i] = tmp;
#ifdef SORTSTAT			
			++c2;
#endif
		}
	}
#ifdef SORTSTAT
	tiktok = clock() - tiktok;
	std::cout << "<" << c1 << ", =" << c2 << ", tics: " << tiktok << std::endl;
#endif
}

template <typename T>
void InsertSortA(T* M, int n) {
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t tiktok = clock();
#endif	
	T tmp;
	for (int j = 1; j < n; ++j) {
		// Ќайти местоположение элемента M[j] в уже отсортированном M[0]...M[j-1], 
		// пусть номер right
		int left = 0, right = j;
		int mid;
		do {
			mid = left + (right - left) / 2;
#ifdef SORTSTAT			
			++c1;
#endif
			if (M[j] < M[mid])
				right = mid - 1;
			else
				left = mid + 1;
		} while (left<right);
		if (right >= 0) {
#ifdef SORTSTAT			
			++c1;
#endif
			if (M[j] < M[right]) --right;
		}
		
		if (j > right + 1) {
			tmp = M[j];
#ifdef SORTSTAT			
			++c2;
#endif
			// с номера right+1 до j-1 сдвинуть элементы вправо на 1
			for (int i = j; i > right + 1; --i) {
				M[i] = M[i - 1];
#ifdef SORTSTAT			
				++c2;
#endif
			}
			// на место M[right+1] записать tmp (бывший элемент M[j])
			M[right + 1] = tmp;
#ifdef SORTSTAT			
			++c2;
#endif
		}
	}
#ifdef SORTSTAT
	tiktok = clock() - tiktok;
	std::cout << "<" << c1 << ", =" << c2 << ", tics: " << tiktok << std::endl;
#endif
}


template <typename T>
void QuickSortR(T* M, int n) {
	int left = 0, right = n - 1;
	int pindex = left + (right - left) / 2;
	int i = left, j = right;
	
	T p = M[pindex];
	while(i<j){
		while (M[i] < p) ++i;
		while (p < M[j]) --j;
		if (i < j) {
			std::swap(M[i], M[j]); 
			++i; --j;
		} else if (i == j) {
			++i; --j;
		}
	}

	if (pindex < i) { // ѕрава€ часть меньше, чем лева€
		if (i < right) QuickSortR(M + i, right - i + 1);
		if (j > left) QuickSortR(M + left, j - left + 1);
	} else { // Ћева€ часть меньше, чем права€
		if (j > left) QuickSortR(M + left, j - left + 1);
		if (i < right) QuickSortR(M + i, right - i + 1);
	}
}

template <typename T>
void QuickSortS(T* M, int n) {
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t tiktok = clock();
#endif	

	int N = n, size = 1;
	while (N > 0) {
		N >>= 1; // N = N >> 1; // N = N/2;
		++size;
	}
	int* StackLeft = new int[size];
	int* StackRight = new int[size];
	int LastInStack = -1;
	++LastInStack; StackLeft[LastInStack] = 0; StackRight[LastInStack] = n - 1;
	while (LastInStack > -1) {
		int left = StackLeft[LastInStack];
		int right = StackRight[LastInStack];
		--LastInStack;

		int pindex = left + (right - left) / 2;
		int i = left, j = right;

		T p = M[pindex];
#ifdef SORTSTAT			
		c1 += right-left+1;
#endif
		while (i < j) {
			while (M[i] < p) ++i;
			while (p < M[j]) --j;
			if (i < j) {
				std::swap(M[i], M[j]);
				++i; --j;
#ifdef SORTSTAT			
				c2 += 3;
#endif
			}
			else if (i == j) {
				++i; --j;
			}
		}

		if (pindex < i) { // ѕрава€ часть меньше, чем лева€
			if (j > left) { ++LastInStack; StackLeft[LastInStack] = left; StackRight[LastInStack] = j; }
			if (i < right) { ++LastInStack; StackLeft[LastInStack] = i; StackRight[LastInStack] = right; }
		} else {
			if (i < right) { ++LastInStack; StackLeft[LastInStack] = i; StackRight[LastInStack] = right; }
			if (j > left) { ++LastInStack; StackLeft[LastInStack] = left; StackRight[LastInStack] = j; }
		}
	}
	delete[] StackLeft;
	delete[] StackRight;

#ifdef SORTSTAT
	tiktok = clock() - tiktok;
	std::cout << "<" << c1 << ", =" << c2 << ", tics: " << tiktok << std::endl;
#endif
}


template <typename T>
void _Merge(T *M, int first, int middle, int last, unsigned long long& c1, unsigned long long& c2) {
	int size = last - first + 1;
	T* tmp = new T[size];
	int start1 = first, end1 = middle, start2 = middle + 1, end2 = last;
	int i = 0; // индекс в массиве tmp
	while (start1 <= end1 && start2 <= end2) {
		if (M[start1] < M[start2])
			tmp[i++] = M[start1++];
		else
			tmp[i++] = M[start2++];
		++c1; ++c2;
	}
	while (start1 <= end1) { tmp[i++] = M[start1++]; ++c2; }
	while (start2 <= end2) { tmp[i++] = M[start2++]; ++c2; }
	//копируем обратно в M
	i = 0;
	while (first <= last) { M[first++] = tmp[i++]; ++c2; }
	delete[] tmp;
}


template <typename T>
void _Split(T* M, int first, int last, unsigned long long &c1, unsigned long long& c2) {
	if (first < last) {
		int middle = first + (last - first) / 2;
		_Split(M, first, middle, c1, c2);
		_Split(M, middle + 1, last, c1, c2);
		_Merge(M, first, middle, last, c1, c2);
	}
}

template <typename T>
void MergeSort(T* M, int n) {
	unsigned long long c1 = 0, c2 = 0;
	clock_t tiktok = clock();

	_Split(M, 0, n - 1, c1, c2);
#ifdef SORTSTAT
	tiktok = clock() - tiktok;
	std::cout << "<" << c1 << ", =" << c2 << ", tics: " << tiktok << std::endl;
#endif
}


template <typename T>
void MergeSortA(T* M, int n) {
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t tiktok = clock();
#endif


	T* tmp = new T[n];
	T* from = M, * to = tmp;
	for (int step = 1; step < n; step *= 2) { // step<<=1
		int start1 = 0, end1, start2, end2;
		int i = 0; // индекс в массиве tmp;
		for (int start = 0; start < n; start += 2 * step) {
			start1 = start; end1 = start1 + step; end1 = (end1 < n) ? end1 : n;
			start2 = end1;  end2 = start2 + step; end2 = (end2 < n) ? end2 : n;
			while (start1 < end1 && start2 < end2) {
				to[i++] = (from[start1] < from[start2]) ? from[start1++] : from[start2++];
#ifdef SORTSTAT			
				++c1;
#endif
			}
			while (start1 < end1) { to[i++] = from[start1++]; }
			while (start2 < end2) { to[i++] = from[start2++]; }
		}
#ifdef SORTSTAT			
		c2 += n;
#endif
		std::swap(from, to);
	}
	if (from != M) {
		// копируем из отсортированного массива в M
		int i = 0;
		while (i < n) {
			M[i] = tmp[i];
			++i;
		}
#ifdef SORTSTAT			
		c2 += n;
#endif

	}
	delete[] tmp;
#ifdef SORTSTAT
	tiktok = clock() - tiktok;
	std::cout << "<" << c1 << ", =" << c2 << ", tics: " << tiktok << std::endl;
#endif
}


template <typename T>
void HeapSort(T* M, int n) {
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t tiktok = clock();
#endif

	// make heap 
	for (int i = 1; i < n; ++i) {
		int pos = i;
		while (pos != 0) {
#ifdef SORTSTAT			
			++c1;
#endif
			if (M[(pos - 1) / 2] < M[pos]) {
				std::swap(M[pos], M[(pos - 1) / 2]);
#ifdef SORTSTAT			
				c2 += 3;
#endif
				pos = (pos - 1) / 2;
			} else break;
		}
	}

	// shift down each element
	int size = n; // текущий размер пирамиды
	for (int i = 1; i < n; ++i) {
		if (M[size - 1] < M[0]) {
			std::swap(M[0], M[size - 1]);
#ifdef SORTSTAT			
			c2 += 3;
#endif
		}
		--size;
		int pos = 0;
		while (2 * pos + 1 < size) { // ѕока есть хот€ бы левый потомок
			int posMaxChild = 2 * pos + 1;
			if (posMaxChild + 1 < size) { // а есть ли правый потомок?
#ifdef SORTSTAT			
				++c1;
#endif
				if (M[posMaxChild] < M[posMaxChild + 1])
					++posMaxChild;
			}

#ifdef SORTSTAT			
			++c1;
#endif
			if (M[pos] < M[posMaxChild]) {
				std::swap(M[pos], M[posMaxChild]);
#ifdef SORTSTAT			
				c2 += 3;
#endif
				pos = posMaxChild;
			} else break;
		}
	}

#ifdef SORTSTAT
	tiktok = clock() - tiktok;
	std::cout << "<" << c1 << ", =" << c2 << ", tics: " << tiktok << std::endl;
#endif
}

#endif