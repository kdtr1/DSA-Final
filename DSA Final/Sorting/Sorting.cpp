#include <iostream>
#include <vector>
using namespace std;

vector<int> insertionSort(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		int j = i;
		while (j > 0 && v[j] <= v[j-1]) {
			int tmp = v[j - 1];
			v[j - 1] = v[j];
			v[j] = tmp;
			j--;
		}
	}
	return v;
}
vector<int> insertionSortSliding(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		int tmp = v[i];
		int j = i-1;
		while (j >= 0 && v[j] > tmp) {
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = tmp;
	}

	return v;
}
vector<int> selectionSort(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		int idx = i;
		for (int j = i + 1; j < v.size(); j++) {
			if (v[j] < v[idx]) {
				idx = j;
			}
		}
		int tmp = v[i];
		v[i] = v[idx];
		v[idx] = tmp;
	}

	return v;
}
vector<int> selectionSortReverseArrangement(vector<int> v) {
	for (int i = v.size() - 1; i >= 1; i--) {
		int idx = i;
		int val = v[i];
		for (int j = i; j >= 0; j--) {
			if (v[j] > v[idx]){
				idx = j;
			}
		}
		int tmp = v[i];
		v[i] = v[idx];
		v[idx] = tmp;
	}

	return v;
}
vector<int> bubbleSort(vector<int> v) {
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = 0; j < v.size() - 1; j++) {
			if (v[j] > v[j+1]) {
				swap(v[j], v[j+1]);
			}
		}
	}
	return v;
}
vector<int> bubbleSortOptimized(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		bool sorted = false;
		int pass = 1;
		while (!sorted && (pass < v.size())) {
			sorted = true;
			for (int j = 0; j < v.size() - pass; j++) {
				if (v[j] > v[j + 1]) {
					swap(v[j], v[j + 1]);
					sorted = false;
				}
			}
			pass++;
		}
	}

	return v;
}
vector<int> bubbleSortgfg(vector<int> v) {
	bool swapped;
	for (int i = 0; i < v.size(); i++) {
		swapped = false;
		for (int j = 0; j < v.size() - i - 1; j++) {
			if (v[j] > v[j + 1]) {
				swap(v[j], v[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false) break;
	}


	return v;
}

void mergeDirect(vector<int>& v, int left, int middle, int right) {
	vector<int> p(v.size(),0);
	int left1 = left;
	int right1 = middle;
	int left2 = middle + 1;
	int right2 = right;
	//Phan tu duyet cac phan tu dau tien trong cac mang con de tron vao mang lon
	int index = left1;

	while ((left1 <= right1) && (left2 <= right2)) {
		if (v[left1] <= v[left2]) {
			p[index] = v[left1];
			left1++;
		}
		else {
			p[index] = v[left2];
			left2++;
		}
		index++;
	}
	while (left1 <= right1) {
		p[index] = v[left1];
		left1++;
		index++;
	}
	while (left2 <= right2) {
		p[index] = v[left2];
		left2++;
		index++;
	}
	for (int i = left; i <= right; i++) {
		v[i] = p[i];
	}
}
int partition(vector<int>& v, int left, int right) {
	int count = 0;
	int pivot = v[left];
	for (int i = left + 1; i <= right; i++) {
		if (v[i] <= pivot) count++;
	}
	int pivotIndex = left + count;
	swap(v[left], v[pivotIndex]);

	int i = left;
	int j = right;
	while (i < pivotIndex && j > pivotIndex) {
		while (v[i] <= pivot && i < pivotIndex) {
			i++;
		}
		while (v[j] > pivot) {
			j--;
		}
		if ((i < pivotIndex) && (j > pivotIndex)) {
			swap(v[i++], v[j--]);
		}
	}

	return pivotIndex;
}
void quickSort(vector<int>& v, int left, int right) {
	if (left >= right) {
		return;
	}
	int pivot = partition(v, left, right);
	quickSort(v, left, pivot - 1);
	quickSort(v, pivot + 1, right);
}
void merge(vector<int>& v, int left, int middle, int right) {
	int len_left = middle - left + 1;
	int len_right = right - middle;

	vector<int> v_left(len_left);
	vector<int> v_right(len_right);

	for (int i = 0; i < len_left; i++) {
		v_left[i] = v[left + i];
	}

	for (int i = 0; i < len_right; i++) {
		v_right[i] = v[middle + 1 + i];
	}

	//Lay ra roi tron lai
	int i1 = 0;
	int i2 = 0;
	int k = left;

	while (i1 < len_left && i2 < len_right) {
		if (v_left[i1] <= v_right[i2]) {
			v[k] = v_left[i1];
			i1++;
		}
		else {
			v[k] = v_right[i2];
			i2++;
		}
		k++;
	}
	//Neu con du thi tron cho den khi het
	while (i1 < len_left) {
		v[k] = v_left[i1];
		i1++;
		k++;
	}

	while (i2 < len_right) {
		v[k] = v_right[i2];
		i2++;
		k++;
	}
}
void mergeSort(vector<int>& v, int left, int right) {
	if (left < right) {
		int middle = left + ( right - left ) / 2;
		//Xe nho ra den khi khong the xe ra nua
		mergeSort(v, left, middle);
		mergeSort(v, middle + 1, right);
		merge(v, left, middle, right);
	}
}
void radixSort(vector<int>& a, int n) {
	int i, at = 1, t[100], h = 1, max = a[0];
	int s[10];
	for (int i = 0; i < n; i++) if (a[i] > max) max = a[i];
	while (max / h > 0) {
		//mang s luu so lan xuat hien cac chu so tu 0 den 9
		for (int i = 0; i < 10; i++) s[i] = 0;
		for (int i = 0; i < n; i++) s[a[i] / h % 10]++;

		//dem so luong cac so nho hon hoac bang i co chu so dang xet
		for (int i = 1; i < 10; i++) s[i] += s[i - 1];

		if (at == 1) for (int i = n - 1; i >= 0; i--) t[--s[a[i] / h % 10]] = a[i];
		else for (int i = n - 1; i >= 0; i--) a[--s[t[i] / h % 10]] = t[i];
		at = - at; 
		h *= 10;
	}
	if (at == 1) for (int i = 0; i < n; i++) a[i] = t[i];
}
int getMax(vector<int> a) {
	int maxval = a[0];
	for (int i = 0; i < a.size(); i++) {
		if (a[i] > maxval)
			maxval = a[i];
	}

	return maxval;
}
void countSort(vector<int>& a, int exp) {
	vector<int> outp(a.size());
	int i, count[10] = { 0 };
	for (int i = 0; i < a.size(); i++) {
		count[a[i] / exp % 10]++;
	}
	for (int i = 1; i < 10; i++) count[i] += count[i - 1];

	for (int i = a.size() - 1; i >= 0; i--) {
		outp[--count[a[i] / exp % 10]] = a[i];
	}
	for (int i = 0; i < a.size(); i++) {
		a[i] = outp[i];
	}
}
void radixSortUndirect(vector<int>& a) {
	int m = getMax(a);
	for (int exp = 1; m / exp > 0; exp *= 10) {
		countSort(a,exp);
	}
}
void heapify(vector<int>& a, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && a[largest] < a[left]) {
		largest = left;
	}
	if (right < n && a[largest] < a[right]) {
		largest = right;
	}

	if (largest != i) {
		swap(a[i], a[largest]);
		heapify(a,n, largest);
	}
}
void heapSort(vector<int>& a) {
	for (int i = a.size() / 2 - 1; i >= 0; i--) {
		heapify(a, a.size(), i);
	}
	for (int i = a.size() - 1; i >= 0; i--) {
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}

 int main() {
	int n; cin >> n;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		v.push_back(x);
	}
	cout << "Insertion sort: ";
	for (int x : insertionSort(v)) cout << x << " ";
	cout << endl;

	cout << "Selection sort: ";
	for (int x : selectionSort(v)) cout << x << " ";
	cout << endl;

	cout << "Bubble sort:    ";
	for (int x : bubbleSort(v)) cout << x << " ";
	cout << endl;

	cout << "Bubble sort:    ";
	for (int x : bubbleSortOptimized(v)) cout << x << " ";
	cout << endl; 

	cout << "Bubble sort:    ";
	for (int x : bubbleSortgfg(v)) cout << x << " ";
	cout << endl;

	cout << "Merge sort:     ";
	vector<int> s = v;
	mergeSort(s, 0, s.size() - 1);
	for (int x : s) cout << x << " ";
	cout << endl;

	cout << "Quick sort:     ";
	vector<int> q = v;
	quickSort(q, 0, n - 1);
	for(int x : q) cout << x << " ";
	cout << endl;

	vector<int> a = v;
	radixSort(a,a.size());
	cout << "Radix Sort:     ";
	for (int x : a) cout << x << " ";
	cout << endl;

	vector<int> a1 = v;
	radixSortUndirect(a1);
	cout << "Radix Sort:     ";
	for (int x : a1) cout << x << " ";
	cout << endl;


	vector<int> h = v;
	heapSort(h);
	cout << "Heap Sort:      ";
	for (int x : h) cout << x << " ";
	cout << endl;

    
	return 0;
}
