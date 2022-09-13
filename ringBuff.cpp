#include <iostream>

using namespace std;

struct ringBuff1 {
	ringBuff1(size_t size) :size(size) {
		rb = new int[size];
		for (int i = 0; i < size; ++i)rb[i] = 0;
		curr = rb;
		first = rb;
		end = rb + size;
		empty = true;
	}

	~ringBuff1() {
		delete[] rb;
	}

	void append(int num) {
		if (curr == first && !empty) { //здесь проверяется перезапись
			first++;
			if (first == end)first = rb;
		}
		*curr = num;
		empty = false;
		curr++;
		if (curr == end)curr = rb;
	}

	void pop() {
		*first = 0;
		first++;
		if (first == end)first = rb;
		if (first == curr) {
			empty = true;
			return;
		}
	}

	void pop(size_t n) {
		for (size_t i = 0; i < n; ++i)pop();
	}

	int getNum(size_t i) {
		if (i >= size) {
			cout << "Error: no such index" << endl;
			return 0;
		}
		if (first + i < end) {
			return *(first + i);
		}
		return *(first + i - size);
	}
private:
	int* rb;
	int* first;
	int* curr;
	int* end;
	size_t size;
	bool empty;
};

int main()
{
	ringBuff1 a(7);
	for (int i = 0; i < 14; i++)a.append(i);
	a.pop(6);
	cout << a.getNum(0);
}