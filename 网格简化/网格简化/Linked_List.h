#pragma once

#include "Heap.h"

struct LListNode
{
	NHeap* heap;

	LListNode* next;
	LListNode* down;

	LListNode(){
	next = 0;
	down = 0;
	heap = 0;
	};
	LListNode(int a,int b,NHeap* h){
		if(h==0)
		heap = new NHeap;
		else heap = h;
		next = 0;
		down = 0;
		if(a>=b)
		{
			heap->vertex1 = b;heap->vertex2 = a;
		}
		else
		{
			heap->vertex1 = a;heap->vertex2 = b;
		}
	}
};

struct Listh
{
	LListNode* next;
	bool exist;
	Listh(){next=0;exist = true;}
};

class LList			//save all the edge into the vertex with smaller position
{
public:
	Listh* row;
	Listh* col;		//in order of bigger Heap.error

	LList(){};
	LList(int num)
	{
		row = new Listh[num];
		col = new Listh[num];
	}


	bool LInsert(LListNode*& N);
};

