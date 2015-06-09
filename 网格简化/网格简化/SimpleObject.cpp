#include <stdlib.h>
#include "SimpleObject.h"
#include <vector>

using namespace std;

namespace SimpleOBJ
{
    CSimpleObject::CSimpleObject(void)
    {
        m_nVertices = -1;
        m_nTriangles = -1;
        m_pTriangleList = NULL;
        m_pVertexList = NULL;
    }

    CSimpleObject::~CSimpleObject(void)
    {
        Destroy();
    }

    void CSimpleObject::Destroy()
    {
        if(m_pTriangleList)
            delete []m_pTriangleList;
        if(m_pVertexList)
            delete []m_pVertexList;

        m_nVertices = -1;
        m_nTriangles = -1;
        m_pVertexList = NULL;
        m_pTriangleList = NULL;
    }

    bool CSimpleObject::LoadFromObj(const char* fn)
    {
        FILE* fp = fopen(fn,"r");
        if(fp==NULL)
        {
            printf("Error: Loading %s failed.\n",fn);
            return false;
        }
        else
        {
            if(Parse(fp))
            {
                printf("Loading from %s successfully.\n",fn);
                printf("Vertex Number = %d\n",m_nVertices);
                printf("Triangle Number = %d\n",m_nTriangles);
                fclose(fp);
                return true;
            }
            else
            {
                fclose(fp);
                return false;
            }
        }
    }

    bool CSimpleObject::Parse(FILE* fp)
    {
        
        char buf[256];
        int nVertices,nTriangles;
        std::vector<Vector3>        vecVertices;
        std::vector<Array<int,3> >  vecTriangles;

        nVertices = 0;
        nTriangles = 0;
        vecVertices.clear();
        vecTriangles.clear();
        int lineNumber = 0; 

        while(fscanf(fp, "%s", buf) != EOF)
        {
            lineNumber ++;
            switch(buf[0])
            {
            case '#':				/* comment */
                /* eat up rest of line */
                fgets(buf, sizeof(buf), fp);
                break;
            case 'v':				/* v, vn, vt */
                switch(buf[1])
                {
                case '\0':			    /* vertex */
                    {
                        Vector3 vP;
                        if(fscanf(fp, "%f %f %f", 
							&vP[0], 
                            &vP[1], 
                            &vP[2])==3)
                        {
                            nVertices++;
                            vecVertices.push_back(vP);
                        }
                        else 
                        {
                            printf("Error: Wrong Number of Values(Should be 3). at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    break;
                default:
                    /* eat up rest of line */
	                fgets(buf, sizeof(buf), fp);
                    break;
                }
                break;

            case 'f':				/* face */
                {
                    int v,n,t;
                    Array<int,3> vIndices;
                    if(fscanf(fp, "%s", buf)!=1)
                    {
                        printf("Error: Wrong Face at Line %d\n",lineNumber);
                        return false;
                    }
                    
                    /* can be one of %d, %d//%d, %d/%d, %d/%d/%d %d//%d */
                    if (strstr(buf, "//"))
                    {
                        /* v//n */
                        if( sscanf(buf, "%d//%d", &vIndices[0],&n) ==2  &&
                            fscanf(fp, "%d//%d", &vIndices[1], &n) ==2  &&
                            fscanf(fp, "%d//%d", &vIndices[2], &n) ==2)
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }

                    }
                    else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3)
                    {
                        /* v/t/n */
                        vIndices[0] = v;
                        if( fscanf(fp, "%d/%d/%d", &vIndices[1], &t, &n) ==3 &&
                            fscanf(fp, "%d/%d/%d", &vIndices[2], &t, &n) ==3 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    else if (sscanf(buf, "%d/%d", &v, &t) == 2)
                    {
                        /* v/t */
                        vIndices[0] = v;
                        if( fscanf(fp, "%d/%d", &vIndices[1], &t) ==2 &&
                            fscanf(fp, "%d/%d", &vIndices[2], &t) ==2 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    else
                    {
                        /* v */
                        if( sscanf(buf, "%d", &vIndices[0]) ==1 && 
                            fscanf(fp, "%d", &vIndices[1])  ==1 &&
                            fscanf(fp, "%d", &vIndices[2])  ==1 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }

                }

                break;

            default:
                /* eat up rest of line */
                fgets(buf, sizeof(buf), fp);
                break;
            }
        }
        
        if(CheckParse(vecVertices.size(),vecTriangles))
        {
            Destroy();
            
            m_nVertices = vecVertices.size();
            m_nTriangles = vecTriangles.size();            
            m_pVertexList = new Vertex[m_nVertices];
            m_pTriangleList = new Face[m_nTriangles];

            for(int i=0;i<m_nVertices;i++)
                m_pVertexList[i].position = vecVertices[i];
            for(int i=0;i<m_nTriangles;i++)
            {
                for(int j=0;j<3;j++)
                m_pTriangleList[i].vertex[j] = vecTriangles[i][j] - 1;
            }

            return true;
        }
        else
            return false;
    }

    bool CSimpleObject::CheckParse(int nVertices,std::vector<Array<int,3> > & vecTriangles)
    {
        for(unsigned int i=0;i<vecTriangles.size();i++)
        {
            Array<int,3> & vIndices = vecTriangles[i];
            for(int j=0;j<vIndices._len;j++)
                if(vIndices[j]<=0||vIndices[j]>nVertices)
                {
                    printf("Error: The vertex index of Face %d has exceeded vertex number %d\n",i,nVertices);
                    return false;
                }
        }

        return true;
    }

    bool CSimpleObject::SaveToObj(const char* fn)
    {
		int* d = new int[m_nVertices];
		d[0]=0;
        if(!IsLoaded())
        {
            printf("Error: Object is not initialized.\n",fn);
            return false;
        }
        
        FILE* fp = fopen(fn,"w");
        if(fp==NULL)
        {
            printf("Error: Failed opening %s to write\n",fn);
            return false;
        }

        //fprintf(fp,"# %d vertices\n",m_nVertices);
        for(int i=0;i<m_nVertices;i++)
		{
			if(m_pVertexList[i].exist)
			{
				fprintf(fp,"v %f %f %f\n",  m_pVertexList[i].position.val[0],
                                        m_pVertexList[i].position.val[1],
                                        m_pVertexList[i].position.val[2]);
				d[i+1]=d[i];
			}
			else
			{
				d[i+1]=d[i]+1;
			}
		}

        //fprintf(fp,"# %d triangles\n",m_nTriangles);
        for(int i=0;i<m_nTriangles;i++)
		{

			if(!m_pTriangleList[i].del)
			{
				for(int k=0;k<3;k++)
				{
				if(!m_pVertexList[m_pTriangleList[i].vertex[k]].exist)
					continue;
				}
            fprintf(fp,"f %d %d %d\n",  m_pTriangleList[i].vertex[0] -d[m_pTriangleList[i].vertex[0]]+ 1,
                                        m_pTriangleList[i].vertex[1] -d[m_pTriangleList[i].vertex[1]]+ 1,
                                        m_pTriangleList[i].vertex[2] -d[m_pTriangleList[i].vertex[2]]+ 1);
			}
		}

        fclose(fp);
        
        printf("Writing to %s successfully\n",fn);
        return true;

    }

	void CSimpleObject::setVert()
	{
		for(int i=0;i<m_nTriangles;i++)
		{
			seterror(i);
			for(int j = 0;j<3;j++)
			{
				int indx = m_pTriangleList[i].vertex[j];
				m_pVertexList[indx].Facelist[m_pVertexList[indx].facenum] = i;
				m_pVertexList[indx].q += m_pTriangleList[i].error;
				m_pVertexList[indx].facenum++;
				if(m_pVertexList[indx].facenum>99){
					std::cerr<<"The num of "<<indx<<"'s face is out of range(100)"<<endl;
					return;
				}
			}
		}
	}

	void CSimpleObject::initlist()
	{
		list = LList(m_nVertices);
		Matrix error;
		int v[3];
		float delta=0.0;
		Vector3 vec=Vector3(0,0,0);
		for(int i=0;i<m_nVertices;i++)
		{
			for(int j=0;j<m_pVertexList[i].facenum;j++)
			{
				v[0] = m_pTriangleList[m_pVertexList[i].Facelist[j]].vertex[0];
				v[1] = m_pTriangleList[m_pVertexList[i].Facelist[j]].vertex[1];
				v[2] = m_pTriangleList[m_pVertexList[i].Facelist[j]].vertex[2];

				for(int k=0;k<3;k++)
				{
					if(v[k]!=i && !m_pVertexList[v[k]].exist)
					{
						LListNode* a = new LListNode(i,v[k],0);
						if(!list.LInsert(a))
						{
							delete a;
							continue;
						}

						error = m_pVertexList[i].q + m_pVertexList[v[k]].q;
						if(!Getmin(error,vec,delta))
						{
							vec = (m_pVertexList[i].position+m_pVertexList[v[k]].position);
							vec /= 2;
							delta = error.matrix[0][0]*vec.x()*vec.x() + error.matrix[1][1]*vec.y()*vec.y() + error.matrix[2][2]*vec.z()*vec.z() + 2*error.matrix[0][1]*vec.x()*vec.y() + 
							2*error.matrix[0][2]*vec.x()*vec.z() + 2*error.matrix[1][2]*vec.y()*vec.z() + 2*error.matrix[0][3]*vec.x() + 2*error.matrix[1][3]*vec.y() + 2*error.matrix[2][3]*vec.z() + error.matrix[3][3];
						}
						
						a->heap->delta = delta;
						a->heap->vec = vec;
						
					}
				}
			}
			m_pVertexList[i].exist = true;
		}
	}

	void CSimpleObject::initHeap()
	{

		hsimple = heap(m_nVertices*3);
		int num=0;
		LListNode* ptr;
		for(int i=0;i<m_nVertices;i++)
		{
			ptr = list.col[i].next;
			while(ptr)
			{
				hsimple.insert_no_adj(ptr->heap);
				ptr = ptr->down;
				num++;
				if(num>m_nVertices*3)
				{
					std::cerr<<"the heap needs to be enlarged"<<endl;
				}

			}
		}
		hsimple.initheapity();

	}

	bool CSimpleObject::findshare(Face f,int vertex1,int vertex2,int&v1,int&v2,int& v3)
	{
		bool res = false;
		for(int i=0;i<3;i++)
		{
			if(f.vertex[i]==vertex2)
			{
				v2=i;
				continue;
			}
			if(f.vertex[i]==vertex1)
			{
				v1=i;
				res=true;
				continue;
			}
		}
		if(!res)
		{
			v1=3-v2;
		}
		v3 = 3-v1-v2;
		return res;
	}

	void  CSimpleObject::seterror(int fn)
	{		
		float* p;
		Matrix kp;
		p=Plane_Eq(fn);
		kp.matrix[0][0]=p[0]*p[0];kp.matrix[1][0]=kp.matrix[0][1]=p[0]*p[1];kp.matrix[2][0]=kp.matrix[0][2]=p[0]*p[2];kp.matrix[3][0]=kp.matrix[0][3]=p[0]*p[3];
		kp.matrix[1][1]=p[1]*p[1];kp.matrix[2][1]=kp.matrix[1][2]=p[1]*p[2];kp.matrix[3][1]=kp.matrix[1][3]=p[1]*p[3];
		kp.matrix[2][2]=p[2]*p[2];kp.matrix[3][2]=kp.matrix[2][3]=p[2]*p[3];
		kp.matrix[3][3]=p[3]*p[3];
		m_pTriangleList[fn].error = kp;
	}

	void CSimpleObject::meshsimplify(float ratio)
	{

		int diminish=0;
		int total = m_nTriangles * (1 - ratio);
		while(diminish<total)
		{
			if(diminish%1000==0)
				cout<<diminish<<endl;
			int t=0;
			int a1=-1,a2=-1;

			if(hsimple.queue[0]->delta==-1)
			{
				hsimple.hdelete();
				continue;
			}

			int vertex1 = hsimple.queue[0]->vertex1;
			int vertex2 = hsimple.queue[0]->vertex2;

			if(!list.row[vertex1].exist || !list.row[vertex2].exist)
			{
				hsimple.hdelete();
				continue;
			}


			m_pVertexList[vertex1].position = hsimple.queue[0]->vec;

			hsimple.hdelete();

			m_pVertexList[vertex2].exist=false;
			int i = m_pVertexList[vertex2].facenum;
			int* newlist = new int[100];
			int num=0;
			m_pVertexList[vertex1].q = Matrix(); 
			
			for(int n=0;n<i;n++)
			{
				int v1=-1,v2=-1,v3=-1;
				Face* f = &m_pTriangleList[m_pVertexList[vertex2].Facelist[n]];
				if(findshare(*f,vertex1,vertex2,v1,v2,v3))
				{
					if(a1!=-1)
						a2=f->vertex[v3];
					else a1 = f->vertex[v3];

					for(int j=0;j<m_pVertexList[f->vertex[v3]].facenum;j++)
					{
						if(m_pVertexList[f->vertex[v3]].Facelist[j] == m_pVertexList[vertex2].Facelist[n])
						{
							m_pVertexList[f->vertex[v3]].Facelist[j] = m_pVertexList[f->vertex[v3]].Facelist[m_pVertexList[f->vertex[v3]].facenum-1];
							m_pVertexList[f->vertex[v3]].facenum--;
						}
					}
					f->del = true;
					t++;
				}
				else
				{
					newlist[num]=m_pVertexList[vertex2].Facelist[n];
					num++;
					f->vertex[v2]=vertex1;
					seterror(m_pVertexList[vertex2].Facelist[n]);
					m_pVertexList[vertex1].q += m_pTriangleList[m_pVertexList[vertex2].Facelist[n]].error;
				}
			}

			for(int j=0;j<m_pVertexList[vertex1].facenum;j++)
			{
				if(m_pTriangleList[m_pVertexList[vertex1].Facelist[j]].del)continue;
				newlist[num] = m_pVertexList[vertex1].Facelist[j];
				seterror(newlist[num]);
				m_pVertexList[vertex1].q += m_pTriangleList[newlist[num]].error;
				num++;
			}
			delete []m_pVertexList[vertex1].Facelist;
			m_pVertexList[vertex1].Facelist = newlist;
			m_pVertexList[vertex1].facenum = num;
			list.row[vertex2].exist = false;
			list.col[vertex2].exist = false;
			
			LListNode* ptr = list.col[vertex1].next;
			while(ptr)
			{
				if(ptr->heap->vertex1 != vertex2 && list.row[ptr->heap->vertex1].exist)
				{
					m_pVertexList[ptr->heap->vertex1].q = Matrix();
					for(int j=0;j<m_pVertexList[ptr->heap->vertex1].facenum;j++)
					{
						m_pVertexList[ptr->heap->vertex1].q += m_pTriangleList[m_pVertexList[ptr->heap->vertex1].Facelist[j]].error;
					}
				}
				ptr = ptr->down;
			}
			ptr = list.row[vertex1].next;
			while(ptr)
			{
				if(ptr->heap->vertex2 != vertex2 && list.row[ptr->heap->vertex2].exist)
				{
					m_pVertexList[ptr->heap->vertex2].q = Matrix();
					for(int j=0;j<m_pVertexList[ptr->heap->vertex2].facenum;j++)
					{
						m_pVertexList[ptr->heap->vertex2].q += m_pTriangleList[m_pVertexList[ptr->heap->vertex2].Facelist[j]].error;
					}
				}
				ptr = ptr->next;
			}

			ptr = list.col[vertex2].next;
			while(ptr)
			{
				if(list.row[ptr->heap->vertex1].exist)
				{
					if(vertex1==ptr->heap->vertex1)goto down1;

					if(ptr->heap->vertex1 == a1 || ptr->heap->vertex1 == a2)
					{
						ptr->heap->delta = -1;
						goto down1;
					}

					m_pVertexList[ptr->heap->vertex1].q = Matrix();
					for(int j=0;j<m_pVertexList[ptr->heap->vertex1].facenum;j++)
					{
						m_pVertexList[ptr->heap->vertex1].q += m_pTriangleList[m_pVertexList[ptr->heap->vertex1].Facelist[j]].error;
					}

					LListNode* newnode = new LListNode(vertex1,ptr->heap->vertex1,ptr->heap);
					list.LInsert(newnode);
				}
				down1:ptr = ptr ->down;
			}

			ptr = list.row[vertex2].next;
			while(ptr)
			{
				if(vertex1==ptr->heap->vertex2)goto down2;
				if(list.col[ptr->heap->vertex2].exist)
				{
					if(ptr->heap->vertex2 == a1 || ptr->heap->vertex2 == a2)
					{
						ptr->heap->delta = -1;
						goto down2;
					}

					m_pVertexList[ptr->heap->vertex2].q = Matrix();
					for(int j=0;j<m_pVertexList[ptr->heap->vertex2].facenum;j++)
					{
						m_pVertexList[ptr->heap->vertex2].q += m_pTriangleList[m_pVertexList[ptr->heap->vertex2].Facelist[j]].error;
					}

					LListNode* newnode = new LListNode(vertex1,ptr->heap->vertex2,ptr->heap);
					list.LInsert(newnode);
				}
				down2:ptr = ptr->next;
			}

			ptr = list.col[vertex1].next;
			Vector3 nvec;
			float d;
			while(ptr)
			{
				if(list.col[ptr->heap->vertex1].exist)
				{
					Matrix a = m_pVertexList[ptr->heap->vertex1].q + m_pVertexList[ptr->heap->vertex2].q;
					if(!Getmin(a,nvec,d))
					{
						nvec = (m_pVertexList[vertex1].position+m_pVertexList[ptr->heap->vertex1].position);
						nvec /= 2;
						d = a.matrix[0][0]*nvec.x()*nvec.x() + a.matrix[1][1]*nvec.y()*nvec.y() + a.matrix[2][2]*nvec.z()*nvec.z() + 2*a.matrix[0][1]*nvec.x()*nvec.y() + 
							2*a.matrix[0][2]*nvec.x()*nvec.z() + 2*a.matrix[1][2]*nvec.y()*nvec.z() + 2*a.matrix[0][3]*nvec.x() + 2*a.matrix[1][3]*nvec.y() + 2*a.matrix[2][3]*nvec.z() + a.matrix[3][3];
					}
					ptr->heap->vec = nvec;
					ptr->heap->delta = d;
				}
				ptr = ptr->down;
			}

			ptr = list.row[vertex1].next;
			while(ptr)
			{
				if(list.row[ptr->heap->vertex2].exist)
				{
					Matrix a = m_pVertexList[ptr->heap->vertex1].q + m_pVertexList[ptr->heap->vertex2].q;
					if(!Getmin(a,nvec,d))
					{
						nvec = (m_pVertexList[vertex1].position+m_pVertexList[ptr->heap->vertex2].position);
						nvec /= 2;
						d = a.matrix[0][0]*nvec.x()*nvec.x() + a.matrix[1][1]*nvec.y()*nvec.y() + a.matrix[2][2]*nvec.z()*nvec.z() + 2*a.matrix[0][1]*nvec.x()*nvec.y() + 
							2*a.matrix[0][2]*nvec.x()*nvec.z() + 2*a.matrix[1][2]*nvec.y()*nvec.z() + 2*a.matrix[0][3]*nvec.x() + 2*a.matrix[1][3]*nvec.y() + 2*a.matrix[2][3]*nvec.z() + a.matrix[3][3];
					}
					ptr->heap->vec = nvec;
					ptr->heap->delta = d;
				}
				ptr = ptr->next;
			}

			hsimple.initheapity();
			diminish += t;
		}

	}

	float* CSimpleObject:: Plane_Eq(int n_Face)
	{
		Vector3 p0,p1,p2;
		p0 = m_pVertexList[m_pTriangleList[n_Face].vertex[0]].position;
		p1 = m_pVertexList[m_pTriangleList[n_Face].vertex[1]].position;
		p2 = m_pVertexList[m_pTriangleList[n_Face].vertex[2]].position;
	
		Vector3 norm = cross(p1-p0,p2-p0);
		float D = dot(norm,p0);

		float Length = norm.x()*norm.x() + norm.y()*norm.y() + norm.z()*norm.z();
		Length = sqrtf(Length);

		float plane[4];
		plane[0] = norm.x()/Length;
		plane[1] = norm.y()/Length;
		plane[2] = norm.z()/Length;
		plane[3] = -D/Length;

		return plane;
	}

	float* CSimpleObject:: Plane_Eq(Face f)
	{	
		Vector3 p0,p1,p2;
		p0 = m_pVertexList[f.vertex[0]].position;
		p1 = m_pVertexList[f.vertex[1]].position;
		p2 = m_pVertexList[f.vertex[2]].position;

		Vector3 norm = cross(p1-p0,p2-p0);
		float D = dot(norm,p0);

		float Length = norm.x()*norm.x() + norm.y()*norm.y() + norm.z()*norm.z();
		Length = sqrtf(Length);

		float plane[4];
		plane[0] = norm.x()/Length;
		plane[1] = norm.y()/Length;
		plane[2] = norm.z()/Length;
		plane[3] = -D/Length;

		return plane;
	}
}


