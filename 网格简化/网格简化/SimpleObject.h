#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Linked_List.h"
#include "Heap.h"
#include <vector>
#include <iostream>

namespace SimpleOBJ
{
    template <typename T, int N> class Array 
    {
    public:
        enum {_len = N};
        typedef T t_Val; 
    public:
        T& operator[] (int i)
        {
            assert(i>=0&&i<N);
            return val[i];
        }
        const T& operator[] (int i) const 
        {
            assert(i>=0&&i<N);
            return val[i];
        }

    protected:
        T val[N];
    };

	struct Vertex
	{
		int facenum;
		Vector3 position;
		int* Facelist;
		Matrix q;
		LList edge;
		bool exist;

		Vertex(){facenum=0;exist=false;Facelist=new int[100];}
	};

	struct Face
	{
		Array<int,3> vertex;
		Matrix error;
		bool del;
		Face(){del=false;}
	};

    class CSimpleObject
    {
    public:
        CSimpleObject(void);
        ~CSimpleObject(void);
        
    public:
        bool IsLoaded() { return m_pVertexList!=NULL;}

        void Destroy();
        bool LoadFromObj(const char* fn);
        bool SaveToObj(const char* fn);

		void setVert();
		void meshsimplify(float ratio);
		void initlist();
		void initHeap();
		bool findshare(Face f,int vertex1,int vertex2,int& v1,int& v2,int& v3);
		float* Plane_Eq(int n_Face);
		float* Plane_Eq(Face f);
		void seterror(int fn);
        
    protected:
        bool Parse(FILE* fp);
        bool CheckParse(int nVertices,std::vector<Array<int,3> > & vecTriangles);

	public:

        int               m_nVertices;
        int               m_nTriangles;
        Vertex*           m_pVertexList;
        Face*			  m_pTriangleList;

		LList			  list;
		heap			  hsimple;
    };


}
