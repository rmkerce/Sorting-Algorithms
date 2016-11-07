#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <time.h>

using namespace std;

void ALG1(int unsortedArray[], int length);
//void ALG2(int unsortedArray[], int beginningNum, int endNum);
//void theMerge(int unsortedArray[], int beginningNum, int endNum, int theMid);
void ALG3(int unsortedArray[], int beginningNum, int endNum);
int Partition(int unsortedArray[], int beginningNum, int endNum);


int main()
{
	int initialRestr = 1000,
		finalRestr = 20000,
		sig = 1000,
		m = 10;

	clock_t time[10];
	clock_t avgTimes[3][20];

	int **unsortedArray = new int *[m];

	for (int i = 0; i < m; i++)
	{
		unsortedArray[i] = new int[finalRestr];
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < finalRestr; j++) //adds elements to the unsortedArray 
		{
			unsortedArray[i][j] = rand();
		}
	}

	//InsertionSort measurements and call
	int averageTimeCtnr = 0;
	for (int i = initialRestr; i <= finalRestr; i += sig)
	{
		int *newArray = new int[i];
		for (int a = 0; a < m; a++)
		{
			for (int b = 0; b < i; b++)
			{
				newArray[b] = unsortedArray[a][b];
			}
			clock_t begin = clock();
			ALG1(newArray, i);
			clock_t end = clock();
			time[a] = end - begin;
		}
		clock_t avg = 0;
		for (int i = 0; i < m; i++)
		{
			avg += time[i];
		}
		avgTimes[0][averageTimeCtnr] = avg / m;
		averageTimeCtnr++;

		delete[] newArray;
	}

	//////MergeSort Measurements 
	//averageTimeCtnr = 0;
	//for (int i = initialRestr; i <= finalRestr; i += sig)
	//{
	//	int *newArray = new int[i];
	//	for (int a = 0; a < m; a++)
	//	{
	//		for (int b = 0; b < i; b++)
	//		{
	//			newArray[b] = unsortedArray[a][b];
	//		}
	//		clock_t begin = clock();
	//		ALG2(newArray, 0, i - 1);
	//		clock_t end = clock();
	//		time[a] = end - begin;
	//	}
	//	clock_t avg = 0;
	//	for (int i = 0; i < m; i++)
	//	{
	//		avg += time[i];
	//	}
	//	avgTimes[1][averageTimeCtnr] = avg / m;
	//	averageTimeCtnr++;

	//	delete[] newArray;
	//}

	////QuickSort Measurements 
	averageTimeCtnr = 0;
	for (int i = initialRestr; i <= finalRestr; i += sig)
	{
		int *newArray = new int[i];
		for (int a = 0; a < m; a++)
		{
			for (int b = 0; b < i; b++)
			{
				newArray[b] = unsortedArray[a][b];
			}
			clock_t begin = clock();
			ALG3(newArray, 0, i - 1);
			clock_t end = clock();
			time[a] = end - begin;
		}
		clock_t avg = 0;
		for (int i = 0; i < m; i++)
		{
			avg += time[i];
		}
		avgTimes[2][averageTimeCtnr] = avg / m;
		averageTimeCtnr++;

		delete[] newArray;
	}

	for (int i = 0; i < 20; i++)
	{
		cout << "The average RT for ALG1 (Insertion Sort) with " << (i + 1) * 1000 << " inputs is " << avgTimes[0][i] << "ms" << endl << endl;
	}

	/*for (int i = 0; i < 20; i++)
	{
		cout << "The average RT for ALG2 (Merge Sort) with " << (i + 1) * 1000 << "inputs is " << avgTimes[1][i] << "ms" << endl << endl;
	}*/
	
	for (int i = 0; i < 20; i++)
	{
		cout << "The average RT for ALG3 (Quick Sort) with " << (i + 1) * 1000 << "inputs is " << avgTimes[2][i] << "ms" << endl << endl;
	}

	//	Before ending the program, it is important to manage memory efficiently by getting rid of the items one at a time.
	//
	for (int i = m - 1; i >= 0; i--)
	{
		delete unsortedArray[i];
	}

	delete[] unsortedArray;

	return 0;
}

void ALG1(int unsortedArray[], int length)
{
	int i, j, key;
	for (j = 1; j < length; j++)
	{
		key = unsortedArray[j];
		i = j-1;
		while (i >= 0 && unsortedArray[i] > key)
		{
			unsortedArray[i + 1] = unsortedArray[i];
			i--;
		}
	}

	unsortedArray[i + 1] = key;

}

//Merge Algorithm implementation
void theMerge(int unsortedArray[], int beginningNum, int endNum, int theMid)
{
	int left = theMid - beginningNum + 1;
	int right = endNum - theMid;
	int *leftArray = NULL;
	int *rightArray = NULL;

	leftArray = new int[left + 1];
	rightArray = new int[right + 1];

	for (int i = 1; i <= left; i++) //Fill the left side
	{
		leftArray[i - 1] = unsortedArray[beginningNum + i - 1];
		cout << "left side value: " << leftArray[i] << endl;
	}
	for (int j = 1; j <= right; j++) //Fill the right side
	{
		rightArray[j - 1] = unsortedArray[endNum + j];
		cout << "right side value: " << rightArray[j] << endl;
	}

	leftArray[left] = RAND_MAX;							//
	rightArray[right] = RAND_MAX;						//
	int i = 1;											// The implementation breaks somewhere in here... 
	int j = 1;											//
	for (int k = beginningNum; k <= endNum; k++)		//
	{												
		if (leftArray[i] <= rightArray[j])
		{
			unsortedArray[k] = leftArray[i];
			i++;
		}
		else
		{
			unsortedArray[k] = rightArray[j];
			j++;
		}
	}

}

//Merge Sort Algorithm implementation
void ALG2(int *unsortedArray, int beginningNum, int endNum)
{
	int theMid = 0;
	if (beginningNum < endNum)
	{
		theMid = (beginningNum + endNum) / 2;
		ALG2(unsortedArray, beginningNum, theMid);
		ALG2(unsortedArray, theMid + 1, endNum);
		theMerge(unsortedArray, beginningNum, endNum, theMid);
	}
}

//Quick Sort Algorithm implementation
void ALG3(int unsortedArray[], int beginningNum, int endNum)
{
	int middleNum = 0;
	if (beginningNum < endNum)
	{
		middleNum = Partition(unsortedArray, beginningNum, endNum);
		ALG3(unsortedArray, beginningNum, middleNum - 1);
		ALG3(unsortedArray, middleNum + 1, endNum);
	}
}

//This function does the partitioning for the above Quick Sort function.
int Partition(int unsortedArray[], int beginningNum, int endNum)
{
	int x = unsortedArray[endNum];
	int i = beginningNum - 1;
	int temp;

	for (int j = beginningNum; j < endNum - 1; j++)
	{
		if (unsortedArray[j] <= x)
		{
			i++;
			temp = unsortedArray[i];
			unsortedArray[i] = unsortedArray[j];
			unsortedArray[j] = temp;
		}
	}

	temp = unsortedArray[i + 1];
	unsortedArray[i + 1] = unsortedArray[endNum];
	unsortedArray[endNum] = temp;
	return i + 1;
}