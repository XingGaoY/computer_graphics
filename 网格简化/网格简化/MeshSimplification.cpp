#include "SimpleObject.h"

int main()
{
	SimpleOBJ::CSimpleObject tst;
	tst.LoadFromObj("bunny.obj");
	tst.setVert();
	tst.initlist();
	tst.initHeap();
	tst.meshsimplify(0.01);
	tst.SaveToObj("test_res.obj");
}
