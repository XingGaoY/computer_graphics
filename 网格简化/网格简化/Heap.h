#pragma once

#include<iostream>
#include"Vector.h"

struct NHeap
{
	int vertex1;                       //make sure vertex1 < vertex2
	int vertex2;
	float delta;
	Vector3 vec;
};

class heap
{
public:
	NHeap** queue;
	int end;
	
	void swap(int index1,int index2);

	heap(){queue=0;end=-1;};
	heap(int num){queue = new NHeap* [num];end = -1;}

	void hdelete();
	void initheapity();
	void insert(NHeap* nnew);
	void insert_no_adj(NHeap*& nnew);

	void SiftUp(int i);
	void SiftDown(int i);
};
