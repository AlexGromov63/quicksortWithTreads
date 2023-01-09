#include<vector>
#include<iostream>
#include<thread>
using namespace std;

void QuickSort(vector<int>& vec, int start = 0, int end = -1)
{
	if (end == -1)
		end = vec.size() - 1;
	int i = start;
	int j = end;

	int temp;
	int pivot = vec[(i + j) / 2];
	while (i <= j)
	{
		while (vec[i] < pivot)
			i++;
		while (vec[j] > pivot)
			j--;
		if (i <= j)
		{
			temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
			i++;
			j--;
		}
	}
	if (j > start)
		QuickSort(vec, start, j);
	if (i < end)
		QuickSort(vec, i, end);
}

void Quick2Threads(vector<int>& vec, int start = 0, int end = -1)
{
	if (end == -1)
		end = vec.size() - 1;
	int i = start;
	int j = end;

	int temp;
	int pivot = vec[(i + j) / 2];
	while (i <= j)
	{
		while (vec[i] < pivot)
			i++;
		while (vec[j] > pivot)
			j--;
		if (i <= j)
		{
			temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
			i++;
			j--;
		}
	}
	thread* t1 = nullptr;
	thread* t2 = nullptr;

	if (j > start)
		t1 = new thread(QuickSort, ref(vec), start, j);
	if (i < end)
		t2 = new thread(QuickSort, ref(vec), i, end);

	t1->join();
	t2->join();
}

void PrintVector(vector<int>& vec) {

	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}
void CheckVector(vector<int>& vec)
{
	for (int i = 0; i < vec.size() - 1; i++)
	{
		if (vec[i] > vec[i + 1])
		{
			cout << "Error" << endl;
			return;
		}
	}
	cout << "OK" << endl;
}

void AddRandItems(vector<int>& vec, int count)
{
	for (size_t i = 0; i < count; i++)
	{
		vec.push_back(rand() % 100);
	}

}

void printKeyboard()
{
	for (size_t i = 0; i < 256; i++)
	{
		cout << (char)i;
	}
	cout << endl;
}

int main()
{

	vector<int> vec = { 5, 2, 8, 4, 10, 6, 7, 3, 9, 1 };
	AddRandItems(vec, 2000000);

	//PrintVector(vec);
	long start = clock();
	Quick2Threads(vec);
	long end = clock();
	//PrintVector(vec);
	CheckVector(vec);

	cout << "Time = " << (end - start) * 1.0 / CLOCKS_PER_SEC << endl;
}