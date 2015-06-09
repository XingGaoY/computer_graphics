#include "Linked_List.h"


bool LList::LInsert(LListNode*& N)
{
	int rown = N->heap->vertex1;
	int coln = N->heap->vertex2;
	LListNode* rptr = row[rown].next;
	LListNode* cptr = col[coln].next;

	if(!cptr || N->heap->vertex1 <= cptr->heap->vertex1)
	{
		if(cptr && N->heap->vertex1 == cptr->heap->vertex1)return false;
		N->down = col[coln].next;
		col[coln].next = N;
	}

	else
	{
		while(cptr->down)
		{
			if(N->heap->vertex1 == cptr->down->heap->vertex1) return false;
			if(N->heap->vertex1 < cptr->down->heap->vertex1)
			{
				N->down = cptr->down;
				cptr->down = N;
				goto to;
			}
			else
			{
				cptr = cptr->down;
			}
		}
	cptr->down = N;
	}

to:if(!rptr || N->heap->vertex2 <=rptr->heap->vertex2)
	{
		if(rptr&&N->heap->vertex2 == rptr->heap->vertex2)return false;
		N->next = row[rown].next;
		row[rown].next = N;
		return true;
	}
   else
	{
		while(rptr->next)
	   {
		   if(N->heap->vertex2 == rptr->next->heap->vertex2) return false;
		   if(N->heap->vertex2 < rptr->next->heap->vertex2)
		   {
		   N->next = rptr->next;
		   rptr->next = N;
		   return true;
			}
		 else
		 {
		   rptr = rptr->next;
		   }
		}
		rptr->next = N;
		return true;
	}
}
