#include "Sorting.h"

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

vector<int> _array0;
vector<int> _array1;
int _length;

vector<vector<int>> _compResultsMS;
vector<vector<int>> _swapResultsMS;

vector<vector<int>> _compResultsQS;
vector<vector<int>> _swapResultsQS;

vector<double> _avgCompMS;
vector<int> _minCompMS;
vector<int> _maxCompMS;
vector<double> _avgSwapMS;
vector<int> _minSwapMS;
vector<int> _maxSwapMS;

vector<double> _avgCompQS;
vector<int> _minCompQS;
vector<int> _maxCompQS;
vector<double> _avgSwapQS;
vector<int> _minSwapQS;
vector<int> _maxSwapQS;

int _compareCount;
int _swapCount;

void Initialize(int length);
void MergeSort(int* arr, int low, int high);
void QuickSort(int* arr, int low, int high);
void CalculateResults();
void PrintResults();
void ExportResults();

void DoSorting()
{	
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

	CalculateResults();
	
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

double getAverage(vector<int> vec)
{
	int sum = 0;
	
	for (int i = 0; i < vec.size(); i++)
	{
		sum += vec[i];
	}

	return (double)sum / vec.size();
}

int getMinimum(vector<int> vec)
{
	int min = INT_MAX;

	for (int i = 0; i < vec.size(); i++)
	{
		if (min > vec[i])
			min = vec[i];
	}

	return min;
}

int getMaximum(vector<int> vec)
{
	int max = INT_MIN;

	for (int i = 0; i < vec.size(); i++)
	{
		if (max < vec[i])
			max = vec[i];
	}

	return max;
}

void CalculateResults()
{
	for (int i = 0; i < _compResultsMS.size(); i++)
	{
		_avgCompMS.push_back(getAverage(_compResultsMS[i]));
		_minCompMS.push_back(getMinimum(_compResultsMS[i]));
		_maxCompMS.push_back(getMaximum(_compResultsMS[i]));

		_avgSwapMS.push_back(getAverage(_swapResultsMS[i]));
		_minSwapMS.push_back(getMinimum(_swapResultsMS[i]));
		_maxSwapMS.push_back(getMaximum(_swapResultsMS[i]));
	}
	
	for (int i = 0; i < _compResultsQS.size(); i++)
	{
		_avgCompQS.push_back(getAverage(_compResultsQS[i]));
		_minCompQS.push_back(getMinimum(_compResultsQS[i]));
		_maxCompQS.push_back(getMaximum(_compResultsQS[i]));

		_avgSwapQS.push_back(getAverage(_swapResultsQS[i]));
		_minSwapQS.push_back(getMinimum(_swapResultsQS[i]));
		_maxSwapQS.push_back(getMaximum(_swapResultsQS[i]));
	}
}

void PrintResults()
{
	cout << endl << "*** MERGESORT RESULTS ***" << endl;
	cout << "---- Compare Count ----";
	for (int i = 0; i < _avgCompMS.size(); i++)
	{
		cout << "Size " << 50 * (i + 1) << "..." << endl;
		cout << "Average: " << _avgCompMS[i] << endl;
		cout << "Minimum: " << _minCompMS[i] << endl;
		cout << "Maximum: " << _maxCompMS[i] << endl;
	}
	cout << "---- Swap Count ----";
	for (int i = 0; i < _avgSwapMS.size(); i++)
	{
		cout << "Size " << 50 * (i + 1) << "..." << endl;
		cout << "Average: " << _avgSwapMS[i] << endl;
		cout << "Minimum: " << _minSwapMS[i] << endl;
		cout << "Maximum: " << _maxSwapMS[i] << endl;
	}

	cout << endl << "*** QUICKSORT RESULTS ***" << endl;
	cout << "---- Compare Count ----";
	for (int i = 0; i < _avgCompQS.size(); i++)
	{
		cout << "Size " << 50 * (i + 1) << "..." << endl;
		cout << "Average: " << _avgCompQS[i] << endl;
		cout << "Minimum: " << _minCompQS[i] << endl;
		cout << "Maximum: " << _maxCompQS[i] << endl;
	}
	cout << "---- Swap Count ----";
	for (int i = 0; i < _avgSwapQS.size(); i++)
	{
		cout << "Size " << 50 * (i + 1) << "..." << endl;
		cout << "Average: " << _avgSwapQS[i] << endl;
		cout << "Minimum: " << _minSwapQS[i] << endl;
		cout << "Maximum: " << _maxSwapQS[i] << endl;
	}

	//Export results to files
	ExportResults();
}

void ExportResults()
{
	ofstream myfile1;
	myfile1.open("MergeSort_Compare.csv");
	myfile1 << "Input Size,Average,Minimum,Maximum\n";
	for (int i = 0; i < _avgCompMS.size(); i++)
	{
		myfile1 << 50*(i+1) << "," << _avgCompMS[i] << "," << _minCompMS[i] << "," << _maxCompMS[i] << "\n";
	}
	myfile1.close();

	ofstream myfile2;
	myfile2.open("MergeSort_Swap.csv");
	myfile2 << "Input Size,Average,Minimum,Maximum\n";
	for (int i = 0; i < _avgSwapMS.size(); i++)
	{
		myfile2 << 50 * (i + 1) << "," << _avgSwapMS[i] << "," << _minSwapMS[i] << "," << _maxSwapMS[i] << "\n";
	}
	myfile2.close();

	ofstream myfile3;
	myfile3.open("QuickSort_Compare.csv");
	myfile3 << "Input Size,Average,Minimum,Maximum\n";
	for (int i = 0; i < _avgCompQS.size(); i++)
	{
		myfile3 << 50 * (i + 1) << "," << _avgCompQS[i] << "," << _minCompQS[i] << "," << _maxCompQS[i] << "\n";
	}
	myfile3.close();

	ofstream myfile4;
	myfile4.open("QuickSort_Swap.csv");
	myfile4 << "Input Size,Average,Minimum,Maximum\n";
	for (int i = 0; i < _avgSwapQS.size(); i++)
	{
		myfile4 << 50 * (i + 1) << "," << _avgSwapQS[i] << "," << _minSwapQS[i] << "," << _maxSwapQS[i] << "\n";
	}
	myfile4.close();
}