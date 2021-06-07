#include "Sorting.h"

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>

vector<int> _array0;
vector<int> _array1;
int _length;

int _currentTry;
int _currentSize;
vector<vector<int>> _compResultsMS;
vector<vector<int>> _swapResultsMS;
vector<vector<int>> _compResultsQS;
vector<vector<int>> _swapResultsQS;

int _compareCount;
int _swapCount;

void Initialize(int length);
void MergeSort(int* arr, int low, int high);
void QuickSort(int* arr, int low, int high);
void PrintResults();
void ExportResults();

void DoSorting()
{
	_currentSize = 0;
	_currentTry = 0;
	
	srand((unsigned int)time(NULL));

	for (int size = 50; size <= 2000; size = size + 50)
	{
		cout << endl << "Initializing length " << size << endl;
		for (int i = 0; i < 50; i++)
		{
			_array0.push_back(0);
			_array1.push_back(0);
		}

		vector<int> sizeCompResultsMS;
		vector<int> sizeSwapResultsMS;
		vector<int> sizeCompResultsQS;
		vector<int> sizeSwapResultsQS;

		for(int iter = 0; iter < 10; iter++)
		{
			cout << endl << "Generating random content: Try "<< iter <<"..." << endl;
			Initialize(size);

			_compareCount = 0;
			_swapCount = 0;
			cout << endl << "Performing MERGESORT for length " << _length << "..." << endl;
			MergeSort(_array0.data(), 0, _length);
			cout << "Swap count: " << _swapCount << endl;
			cout << "Compare count: " << _compareCount << endl;
			sizeSwapResultsMS.push_back(_swapCount);
			sizeCompResultsMS.push_back(_compareCount);
			
			_compareCount = 0;
			_swapCount = 0;
			cout << "Performing QUICKSORT for length " << _length << "..." << endl;
			QuickSort(_array1.data(), 0, _length);
			cout << "Swap count: " << _swapCount << endl;
			cout << "Compare count: " << _compareCount << endl;
			sizeSwapResultsQS.push_back(_swapCount);
			sizeCompResultsQS.push_back(_compareCount);
		}

		_compResultsMS.push_back(sizeCompResultsMS);
		_swapResultsMS.push_back(sizeSwapResultsMS);
		_compResultsQS.push_back(sizeCompResultsQS);
		_swapResultsQS.push_back(sizeSwapResultsQS);
	}

	PrintResults();
}

void Initialize(int length)
{
	_length = length;

	int randomNumber;

	for (int i = 0; i < _length; i++)
	{
		randomNumber = rand();
		_array0[i] = randomNumber;
		_array1[i] = randomNumber;
	}
}

void merge(int A[], int low, int mid, int high)
{
	int n1, n2, i, j, k;
	//size of left array=n1
	//size of right array=n2       
	n1 = mid - low + 1;
	n2 = high - mid;
	int* L = new int[n1];
	int* R = new int[n2];
	//initializing the value of Left part to L[]
	for (i = 0; i < n1; i++)
	{
		L[i] = A[low + i];
		_swapCount++;
	}
	//initializing the value of Right Part to R[]
	for (j = 0; j < n2; j++)
	{
		R[j] = A[mid + j + 1];
		_swapCount++;
	}
	i = 0, j = 0;
	//Comparing and merging them
	//into new array in sorted order 
	for (k = low; i < n1 && j < n2; k++)
	{
		_compareCount++;
		if (L[i] < R[j])
		{
			A[k] = L[i++];
		}
		else
		{
			A[k] = R[j++];
		}
		_swapCount++;
	}
	//If Left Array L[] has more elements than Right Array R[]
	//then it will put all the
	// remaining elements of L[] into A[]
	while (i < n1)
	{
		A[k++] = L[i++];
		_swapCount++;
	}
	//If Right Array R[] has more elements than Left Array L[]
	//then it will put all the
	// reamining elements of L[] into A[]
	while (j < n2)
	{
		A[k++] = R[j++];
		_swapCount++;
	}

	delete[] L;
	delete[] R;
}

void MergeSort(int* arr, int low, int high)
{
	int mid;
	if (low < high) {
		//divide the array at mid and sort independently using merge sort
		mid = (low + high) / 2;
		MergeSort(arr, low, mid);
		MergeSort(arr, mid + 1, high);
		//merge or conquer sorted arrays
		merge(arr, low, mid, high);
	}
}

int partition(int* arr, int low, int high)
{
	int pivot = arr[high];
	//P-index indicates the pivot value index

	int idx = low;
	int i, t; //t is temporary variable

	//Here we will check if array value is 
	//less than pivot
	//then we will place it at left side
	//by swapping 

	for (i = low; i < high; i++)
	{
		_compareCount++;
		if (arr[i] <= pivot)
		{
			t = arr[i];
			arr[i] = arr[idx];
			arr[idx] = t;
			idx++;
			_swapCount++;
		}
	}
	//Now exchanging value of
	//pivot and P-index
	t = arr[high];
	arr[high] = arr[idx];
	arr[idx] = t;
	_swapCount++;

	//at last returning the pivot value index
	return idx;
}

void QuickSort(int* arr, int low, int high)
{
	if (low < high)
	{
		int idx = partition(arr, low, high);
		QuickSort(arr, low, idx - 1);
		QuickSort(arr, idx + 1, high);
	}
}

void PrintResults()
{
	for (int i = 0; i < _compResultsMS.size(); i++)
	{
		int sum = 0;
		double avg = 0.0;
		for (int j = 0; j < _compResultsMS[i].size(); j++)
		{
			sum += _compResultsMS[i][j];
		}
		avg = (double)sum / _compResultsMS[i].size();

	}
	//TODO
}

void ExportResults()
{
	//TODO
}