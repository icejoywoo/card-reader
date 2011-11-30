#ifndef _UTILS_H_
#define _UTILS_H_

#include <algorithm>
#include <vector>
#include <iostream>
#include "Constants.h"

using namespace std;

/**
 * @brief ���ɸ������ȵ��������(int)����
 * @param count ���鳤��
 * @return ����ָ��
 */
int* randStr(int count);

/**
 * @brief ��ӡ����������(int)����
 * @param array ����(int)����
 * @param count ���鳤��
 * @return None
 */
void printArray(int* array, int count);


int* randStr(int count)
{
	vector<int> orign;
	int* result = new int(count);
	int i;
	for (i = 0; i < count; i++)
	{
		orign.push_back(i);
		//cout << orign.at(i) << " ";
	}
	//cout << endl;
	
	int randNum = 0;
	random_shuffle(orign.begin(), orign.end());
	for (i = 0; i < count; i++)
	{
		result[i] = orign.at(i);
	}
	//cout << endl;
	return result;
}

void printArray(int* array, int count)
{
	int k;
	cout << "Array(int): ";
	for (k = 0; k < READER_COUNT; k++)
	{
		if (k != READER_COUNT-1)
			cout << array[k] << ", ";
		else	/* k ==  READER_COUNT-1 */
			cout << array[k] << endl;
	}
}

#endif