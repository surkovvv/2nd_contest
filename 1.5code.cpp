#include <iostream>
#include <string>
using std::cout;
using std::cin;
template <class T>
struct lane {
	int size;
	//lane(int k) { size = k; };
	lane() =  default;
	std::string name;
	T* mas;
};
template <class T>
void set_size(int k, lane<T> &our_lane) { // тут все окей,по ссылке ориг
	our_lane.size = k;
	our_lane.mas = new T[k];
}
template <class T>
void change_priority(int *transposition, lane<T>* data, int k, int N) { //передавать параметры по ссылке!!!
	lane<T>* copy = new lane<T>[N];
	for (int i = 0; i < N; i++) {
		set_size(k, copy[i]);
		for (int j = 0; j < k; j++) {
			copy[i].mas[j] = data[i].mas[j];
		}
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < k; i++) {
			int index = transposition[i] - 1;
				data[j].mas[i] = copy[j].mas[index];
		}
	}
	delete[] copy;
}
template <class T>
bool operator < (const lane<T>& lane1, const lane<T>& lane2) { // перегрузка
	for (int i = 0; i < lane1.size; i++) { //!!!
		if (lane1.mas[i] == lane2.mas[i]) continue;
		if (lane1.mas[i] < lane2.mas[i]) return true;
		else return false;
	}
	return false;
}
template <class T>
void insert_sort(lane<T>* data, int N) {
	for (int i = 0; i < N; ++i) {
		int k = i;
		while (k > 0 && data[k] < data[k-1]) {
			lane<T> temp = data[k - 1];
			data[k - 1] = data[k];
			data[k] = temp;
			k--;
		}
	}
}
//template <class T>
//void print_data(lane<T>* data, int N, int k) {
//	cout << "Output data: " << std::endl;
//	for (int i = 0; i < N; i++) {
//		cout << data[i].name << " - name and massiv: ";
//		for (int j = 0; j < k; j++) {
//			cout << data[i].mas[j] << " ";
//		}
//		cout << std::endl;
//	}
//}
int main() {
	int N, k;
	cin >> N;
	cin >> k;
	lane<int>* data = new lane<int>[N];
	int* trans = new int[k];
	for (int i = 0; i < k; i++) {
		int number;
		cin >> number;
		trans[i] = number;
	}
	int* transposition = &trans[0];
	for (int i = 0; i < N; i++) {
		std::string name; int a;
		set_size(k, data[i]);
		cin >> name;
		data[i].name = name;
		for (int j = 0; j < k; j++) {
			cin >> a;
			data[i].mas[j] = a;
		}
	}
	change_priority(transposition, data, k, N);
	//print_data(data, N, k);
	insert_sort(data, N);
	for (int i = 0; i < N; i++) {
		cout << data[N- i -1].name << std::endl;
	}
	return 0;
}