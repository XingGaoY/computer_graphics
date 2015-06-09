#include "Heap.h"

void heap::swap(int index1,int index2)
{
	NHeap* temp = queue[index1];
	queue[index1] = queue[index2];
	queue[index2] = temp;
	return;
}

void heap::SiftUp(int index)
{
	NHeap* temp = queue[index];
	int i = index;
	while(i!=0)
	{
		int j = (i-1)/2;
		if(temp->delta<=queue[j]->delta)break;
		queue[i]=queue[j];
		i=j;
	}
	queue[i]=temp;
}

void heap::SiftDown(int index)
{
	int a = index;
	NHeap* temp = queue[a];
	int i = 2*a + 1;
	while(i <= end)
	{
		if(i <end && queue[i]->delta >= queue[i+1]->delta)i++;
		if(temp->delta <= queue[i]->delta)break;
		queue[a]=queue[i];
		a=i;
		i = 2*a+1;
	}
	queue[a] = temp;
}


void heap::hdelete()
{
	if(end==-1){
		std::cerr<<"ERROR:The heap is empty."<<std::endl;
		return;
	}
	NHeap* temp = queue[end];
	end--;
	if(end == -1)return;
	int i=0, j=1;
	while(j <= end)
	{
		if(j < end && queue[j]->delta > queue[j+1]->delta)j++;
		if(temp->delta <= queue[j]->delta)break;
		queue[i]=queue[j];
		i = j;
		j = 2*i+1;
	}
	queue[i] = temp;
	return;
}

void heap::initheapity()
{
	int p = (end + 1)/2-1;
	for(int i=p;i>=0;i--)
	{
		SiftDown(i);
	}
	return;
}

void heap::insert(NHeap* nnew)
{
	end++;
	queue[end] = nnew;
	SiftUp(end);
	return;
}

void heap::insert_no_adj(NHeap*& nnew)
{
	end++;
	queue[end] = nnew;
	return;
}



