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

		xmax = ymax = zmax = -100000;
		xmin = ymin = zmin = 100000;
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
            m_pVertexList = new sVertice[m_nVertices];
            m_pTriangleList = new sTriangle [m_nTriangles];

            for(int i=0;i<m_nVertices;i++)
                m_pVertexList[i].position = vecVertices[i];
            for(int i=0;i<m_nTriangles;i++)
            {
                for(int j=0;j<3;j++)
                m_pTriangleList[i].VexList[j] = vecTriangles[i][j] - 1;
            }

            return true;
        }
        else
            return false;
    }

    bool CSimpleObject::CheckParse(int nVertices,std::vector<Array<int,3> > & vecTriangles)
    {
        for(int i=0;i<vecTriangles.size();i++)
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

        fprintf(fp,"# %d vertices\n",m_nVertices);
        for(int i=0;i<m_nVertices;i++)
            fprintf(fp,"v %f %f %f\n",  m_pVertexList[i].position.x(),
                                        m_pVertexList[i].position.y(),
                                        m_pVertexList[i].position.z());

        fprintf(fp,"# %d triangles\n",m_nTriangles);
        for(int i=0;i<m_nTriangles;i++)
            fprintf(fp,"f %d %d %d\n",  m_pTriangleList[i].VexList[0] + 1,
                                        m_pTriangleList[i].VexList[1] + 1,
                                        m_pTriangleList[i].VexList[2] + 1);

        fclose(fp);
        
        printf("Writing to %s successfully\n",fn);
        return true;

    }

	void CSimpleObject::setface()
	{
		Vector3 norm;
		for(int i=0;i<m_nTriangles;i++)
		{
			norm = cross(m_pVertexList[m_pTriangleList[i].VexList[1]].position-m_pVertexList[m_pTriangleList[i].VexList[0]].position,
				m_pVertexList[m_pTriangleList[i].VexList[2]].position-m_pVertexList[m_pTriangleList[i].VexList[1]].position);
			m_pTriangleList[i].sqr = norm.length();
			m_pTriangleList[i].outnorm = Getnorm(norm);
		}
	}

	void CSimpleObject::setVert()
	{
		for(int i=0;i<m_nTriangles;i++)
		{
			for(int j = 0;j<3;j++)
			{
				int indx = m_pTriangleList[i].VexList[j];
				m_pVertexList[indx].FaceList[m_pVertexList[indx].facenum] = i;
				m_pVertexList[indx].facenum++;
				if(m_pVertexList[indx].facenum>99){
					std::cerr<<"The num of "<<indx<<"'s face is out of range(100)"<<endl;
					return;
				}
			}
		}
		for(int i=0;i<m_nVertices;i++)
		{
			Vector3 sumVec(0,0,0);
			float sumSqr=0;
			for(int j=0;j<m_pVertexList[i].facenum;j++)
			{
				sumVec += m_pTriangleList[m_pVertexList[i].FaceList[j]].outnorm * m_pTriangleList[m_pVertexList[i].FaceList[j]].sqr;
				sumSqr += m_pTriangleList[m_pVertexList[i].FaceList[j]].sqr;
			}
			sumVec /= sumSqr;
			m_pVertexList[i].norm = Getnorm(sumVec);
			if(m_pVertexList[i].position.x()<xmin)xmin = m_pVertexList[i].position.x();
			else if(m_pVertexList[i].position.x()>xmax)xmax = m_pVertexList[i].position.x();
			if(m_pVertexList[i].position.y()<ymin)ymin = m_pVertexList[i].position.y();
			else if(m_pVertexList[i].position.y()>ymax)ymax = m_pVertexList[i].position.y();
			if(m_pVertexList[i].position.z()<zmin)zmin = m_pVertexList[i].position.z();
			else if(m_pVertexList[i].position.z()>zmax)zmax = m_pVertexList[i].position.z();
		}
			xmin -= 0.0001;ymin -= 0.0001;zmin -= 0.0001;
			xmax += 0.0001;ymax += 0.0001;zmax += 0.0001;
	}

}


