#pragma once
#include "Vector.h"
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

	struct sTriangle
	{
		Array<int,3> VexList;
		Vector3 outnorm;
		float sqr;
	};

	struct sVertice
	{
		Vector3 position;
		int FaceList[100];
		int facenum;
		Vector3 norm;
		sVertice(){
			facenum = 0;
			memset(FaceList,-1,15*sizeof(int));
		};
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
		void setface();
        
    protected:
        bool Parse(FILE* fp);
        bool CheckParse(int nVertices,std::vector<Array<int,3> > & vecTriangles);

	public:

        int               m_nVertices;
        int               m_nTriangles;
        sVertice*          m_pVertexList;
        sTriangle*        m_pTriangleList;

		float xmin;
		float ymin;
		float zmin;
		float xmax;
		float ymax;
		float zmax;
    };

}
