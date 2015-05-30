#include "Octree.h"

char* ten2to(int ch,int dep)
{
	char* result = new char[dep+1];
	itoa(ch,result,2);
	int leng = strlen(result);
	for(int i=0;i<leng+1;i++)
	{
		result[dep-i] = result[leng-i];
	}
	for(int i=0;i<dep-leng;i++)
	{
		result[i]='0';
	}

	return result;
}

int sgn(int t)
{
	if(t<0)return -1;
	return +1;
}

Octree::Octree(int num,bool transparent,Vector3 DR, Vector3 SR, Vector3 AR,int RSP, Vector3 DT, Vector3 ST, int TSP, Vector3 IR, Vector3 IT,Texture* tex)
	:Surface(transparent, DR, SR, AR, RSP, DT, ST, TSP, IR, IT,tex)
{
	Facenum = num;
	depth=0;
};

int Octree::CreatOct(int* &_ele,Vector3 _min,Vector3 _max,int _num,const int minnum,const int currentdepth)
{
	int newcenter[24]={
		0,0,0,
		1,0,0,
		0,1,0,
		1,1,0,
		0,0,1,
		1,0,1,
		0,1,1,
		1,1,1,
	};
	if(_num <= minnum || currentdepth > 8)
		//it'a a leaf node
	{
		delta = _max-_min;
		child = NULL;
		min = _min;
		max = _max;
		Facenum = _num;
		ele = new int[_num];
		memcpy(ele,_ele,sizeof(int)*_num);
		depth = 0;
		return depth;
	}
	else
	{
		int temp=0;
		min=_min;
		max=_max;
		Facenum = _num;

		//define vector to save the num of the face in the subnode

		typedef std::vector<int> sub;
		sub s0,s1,s2,s3,s4,s5,s6,s7;
		std::vector<sub> position;
		position.push_back(s0);
		position.push_back(s1);
		position.push_back(s2);
		position.push_back(s3);
		position.push_back(s4);
		position.push_back(s5);
		position.push_back(s6);
		position.push_back(s7);

		child = new Octree[8];

		float deltax = max.x() - min.x();
		float deltay = max.y() - min.y();
		float deltaz = max.z() - min.z();

		float deltax2 = deltax/2;
		float deltay2 = deltay/2;
		float deltaz2 = deltaz/2;

		delta=Vector3(deltax,deltay,deltaz);

		Vector3 newmin[8];
		Vector3 newmax[8];
		for(int j=0;j<8;j++)
		{
			for(int k=0;k<3;k++)
			{
				newmin[j][k] = _min[k]+newcenter[3*j+k]*delta[k]/2;
				newmax[j][k] = _max[k]-newcenter[21-3*j+k]*delta[k]/2;
				child[j].obj=obj;
			}
		}

		for(int i=0;i<_num;i++)
		{
			//test every subnode if it overlap a mesh
			for(int j=0;j<8;j++)
			{
				Vector3 v0=obj->m_pVertexList[obj->m_pTriangleList[_ele[i]].VexList[0]].position;
				Vector3 v1=obj->m_pVertexList[obj->m_pTriangleList[_ele[i]].VexList[1]].position;
				Vector3 v2=obj->m_pVertexList[obj->m_pTriangleList[_ele[i]].VexList[2]].position;
				//test if box overlap each other
				float xmin = std::min(v0.x(),v1.x());xmin = std::min(xmin,v2.x());
				float ymin = std::min(v0.y(),v1.y());ymin = std::min(ymin,v2.y());
				float zmin = std::min(v0.z(),v1.z());zmin = std::min(zmin,v2.z());
				float xmax = std::max(v0.x(),v1.x());xmax = std::max(xmax,v2.x());
				float ymax = std::max(v0.y(),v1.y());ymax = std::max(ymax,v2.y());
				float zmax = std::max(v0.z(),v1.z());zmax = std::max(zmax,v2.z());

				if(newmax[j].x()<xmin||newmin[j].x()>xmax||newmax[j].y()<ymin||newmin[j].y()>ymax||newmax[j].z()<zmin||newmin[j].z()>zmax)continue;

				//test if the plane of the mesh overlaps the box
				Vector3 p_critical(0,0,0),norm=obj->m_pTriangleList[_ele[i]].outnorm;

				if(norm.x()>0)p_critical.val[0] = deltax2;
				if(norm.y()>0)p_critical.val[1] = deltay2;
				if(norm.z()>0)p_critical.val[2] = deltaz2;
				double d1 = dot(norm,p_critical-v0);
				double d2 = dot(norm,Vector3(deltax2,deltay2,deltaz2)-p_critical-v0);
				double n_min = dot(norm,newmin[j]);
				if((n_min+d1)*(n_min+d2)>0)continue;

				//test if the mesh itself overlap the box

				Vector3 e0 = v1-v0;
				Vector3 e1 = v2-v1;
				Vector3 e2 = v0-v2;

				//XY
				Vector2 nXY_e0(-e0.y(),e0.x());
				Vector2 nXY_e1(-e1.y(),e1.x());
				Vector2 nXY_e2(-e2.y(),e2.x());
				if(norm.z()<0){
					nXY_e0 = -nXY_e0;
					nXY_e1 = -nXY_e1;
					nXY_e2 = -nXY_e2;
				}
				double dXY_e0=-dot(nXY_e0,Vector2(v0.x(),v0.y()))+std::max(0.0f,deltax2*nXY_e0.x())+std::max(0.0f,deltay2*nXY_e0.y());
				double dXY_e1=-dot(nXY_e1,Vector2(v1.x(),v1.y()))+std::max(0.0f,deltax2*nXY_e1.x())+std::max(0.0f,deltay2*nXY_e1.y());
				double dXY_e2=-dot(nXY_e2,Vector2(v2.x(),v2.y()))+std::max(0.0f,deltax2*nXY_e2.x())+std::max(0.0f,deltay2*nXY_e2.y());
				Vector2 minxy(newmin[j].x(),newmin[j].y());
				if(dot(nXY_e0,minxy)+dXY_e0<0)continue;
				if(dot(nXY_e1,minxy)+dXY_e1<0)continue;
				if(dot(nXY_e2,minxy)+dXY_e2<0)continue;

				//XZ
				Vector2 nZX_e0(-e0.x(),e0.z());
				Vector2 nZX_e1(-e1.x(),e1.z());
				Vector2 nZX_e2(-e2.x(),e2.z());
				if(norm.y()<0){
					nZX_e0 = -nZX_e0;
					nZX_e1 = -nZX_e1;
					nZX_e2 = -nZX_e2;
				}
				double dZX_e0=-dot(nZX_e0,Vector2(v0.z(),v0.x()))+std::max(0.0f,deltax2*nZX_e0.y())+std::max(0.0f,deltaz2*nZX_e0.x());
				double dZX_e1=-dot(nZX_e1,Vector2(v1.z(),v1.x()))+std::max(0.0f,deltax2*nZX_e1.y())+std::max(0.0f,deltaz2*nZX_e1.x());
				double dZX_e2=-dot(nZX_e2,Vector2(v2.z(),v2.x()))+std::max(0.0f,deltax2*nZX_e2.y())+std::max(0.0f,deltaz2*nZX_e2.x());
				Vector2 minzx(newmin[j].z(),newmin[j].x());
				if(dot(nZX_e0,minzx)+dZX_e0<0)continue;
				if(dot(nZX_e1,minzx)+dZX_e1<0)continue;
				if(dot(nZX_e2,minzx)+dZX_e2<0)continue;

				//YZ
				Vector2 nYZ_e0(-e0.z(),e0.y());
				Vector2 nYZ_e1(-e1.z(),e1.y());
				Vector2 nYZ_e2(-e2.z(),e2.y());
				if(norm.x()<0){
					nYZ_e0 = -nYZ_e0;
					nYZ_e1 = -nYZ_e1;
					nYZ_e2 = -nYZ_e2;
				}
				double dYZ_e0=-dot(nYZ_e0,Vector2(v0.y(),v0.z()))+std::max(0.0f,deltay2*nYZ_e0.x())+std::max(0.0f,deltaz2*nYZ_e0.y());
				double dYZ_e1=-dot(nYZ_e1,Vector2(v1.y(),v1.z()))+std::max(0.0f,deltay2*nYZ_e1.x())+std::max(0.0f,deltaz2*nYZ_e1.y());
				double dYZ_e2=-dot(nYZ_e2,Vector2(v2.y(),v2.z()))+std::max(0.0f,deltay2*nYZ_e2.x())+std::max(0.0f,deltaz2*nYZ_e2.y());
				Vector2 minyz(newmin[j].y(),newmin[j].z());
				if(dot(nYZ_e0,minyz)+dYZ_e0<0)continue;
				if(dot(nYZ_e1,minyz)+dYZ_e1<0)continue;
				if(dot(nYZ_e2,minyz)+dYZ_e2<0)continue;


				//the mesh overlaps the box
				position[j].push_back(_ele[i]);
			}
		}
		for(int i=0;i<8;i++)
		{
			int num = position[i].size();
			int* ele = new int[num];
			for(int n=0;n<num;n++)
			{
				ele[n] = position[i][n];
			}
			int temp1 = child[i].CreatOct(ele,newmin[i],newmax[i],num,minnum,currentdepth+1);
			if(temp1>temp)
			temp = temp1;
			delete []ele;
		}
		depth = temp+1;
		int ldelta=1;
		for(int i=0;i<depth;i++)
		{
			ldelta*=2;
		}
		delta=Vector3((deltax)/ldelta,(deltay)/ldelta,deltaz/ldelta);
		return depth;
	}
}

void Octree::setOct()
{
	delta = Vector3((max.x() - min.x())/depth,(max.y()-min.y())/depth,(max.z()-min.z())/depth);
}

bool Gethitpoint(const Ray& ray, hitrecord& record,Vector3 p0,Vector3 p1,Vector3 p2,Vector3 p0n,Vector3 p1n,Vector3 p2n,float tmax,float tmin)
{
	float A, B, C, D, E, F, G, H, I, J, K, L;
	float alpha, beta, gamma, t;
	A = p0.x() - p1.x();
	B = p0.y() - p1.y();
	C = p0.z() - p1.z();
	D = p0.x() - p2.x();
	E = p0.y() - p2.y();
	F = p0.z() - p2.z();
	G = ray.direct.x();
	H = ray.direct.y();
	I = ray.direct.z();
	J = p0.x() - ray.origin.x();
	K = p0.y() - ray.origin.y();
	L = p0.z() - ray.origin.z();
	float EIHF = E * I - H * F;
	float GFDI = G * F - D * I;
	float DHEG = D * H - E * G;
	float AKJB = A * K - J * B;
	float JCAL = J * C - A * L;
	float BLKC = B * L - K * C;
	t = F * AKJB + E * JCAL + D * BLKC;
	float M = A * EIHF + B * GFDI + C * DHEG;
	t = -t / M;
	if(t<0.001)return false;
	beta = ( J * EIHF + K * GFDI + L * DHEG) / M;
	if(beta < 0 || beta > 1) return false;
	gamma = ( I * AKJB + H * JCAL + G * BLKC) / M;
	if(gamma < 0 || gamma > 1) return false;
	alpha = 1-beta-gamma;
	if(alpha < 0 || alpha > 1) return false;
	if(t>=tmin&&t<=tmax)
	{
	record.hitpoint = ray.origin + t * ray.direct;
	record.norm = Getnorm(alpha*p0n+beta*p1n+gamma*p2n);
	record.t = t;
	return true;
	}
	else return false;
}


bool Octree::findsub(Vector3 _p,Vector3 _d,Octree* &ptr)
{
	if(_p.x()<min.x()||_p.x()>max.x()||_p.y()<min.y()||_p.y()>max.y()||_p.z()<min.z()||_p.z()>max.z())return false;
	if(depth == 0)
	{
		ptr = this;
		return true;
	}
	Vector3 d = _p - min;	
	//Vector3 d0=d;
	d /= delta;

	//float tx=abs(d.x()-(int)d.x());
	//if(tx<0.0001||abs(tx-1)<0.0001)d0.val[0] += sgn(_d.x())*delta.x()/50;
	//float ty=abs(d.y()-(int)d.y());
	//if(ty<0.0001||abs(ty-1)<0.0001)d0.val[1] += sgn(_d.y())*delta.y()/50;
	//float tz=abs(d.z()-(int)d.z());
	//if(tz<0.0001||abs(tz-1)<0.0001)d0.val[2] += sgn(_d.z())*delta.z()/50;

	//d0 /=delta;


	char* x = ten2to((int)d.x(),depth);
	char* y = ten2to((int)d.y(),depth);
	char* z = ten2to((int)d.z(),depth);
	char* p = x;
	for(int i=0;i<depth;i++)
	{
		p[i] = x[i] + y[i]*2 + z[i]*4-288;
	}
	if(p[0]<'0'||p[0]>'7')return false;
	ptr = NULL;
	int pos =p[0]-48;
	if(this->child!=NULL)
		ptr=&this->child[pos];
	for(int i=1;i<depth;i++)
	{
		pos = p[i]-48;
		if(ptr->child!=NULL)
		{
			ptr = &ptr->child[pos];
		}
		else break;
	}
	return true;
}

Vector3 Octree::crossBox(Ray _ray,Octree* ptr,Vector3 point)
{
	float dx,dy,dz;
	float x,y,z;
	if(_ray.direct.x()>0) dx = ptr->max.x() - point.x();
	else dx = ptr->min.x() - point.x();
	if(_ray.direct.y()>0) dy = ptr->max.y() - point.y();
	else dy = ptr->min.y()-point.y();
	if(_ray.direct.z()>0) dz = ptr->max.z()-point.z();
	else dz = ptr->min.z()-point.z();
	x=dx / _ray.direct.x()+delta.x()/100;
	y=dy / _ray.direct.y()+delta.y()/100;
	z=dz / _ray.direct.z()+delta.z()/100;
	float t = std::min(x,y);
	t=std::min(t,z);
	return point+_ray.direct*t;
}

bool Octree::hitOct(Ray _ray,Octree* ptr,hitrecord& rec,float tmax,float tmin)
{
	bool hit = false;
	float itmax = tmax;
	if(ptr==NULL)return false;
	for(int i=0;i<ptr->Facenum;i++)
	{
		Vector3 a,b,c;
		Vector3 an,bn,cn;
		a = obj->m_pVertexList[obj->m_pTriangleList[ptr->ele[i]].VexList[0]].position;
		an = obj->m_pVertexList[obj->m_pTriangleList[ptr->ele[i]].VexList[0]].norm;
		b = obj->m_pVertexList[obj->m_pTriangleList[ptr->ele[i]].VexList[1]].position;
		bn = obj->m_pVertexList[obj->m_pTriangleList[ptr->ele[i]].VexList[1]].norm;	
		c = obj->m_pVertexList[obj->m_pTriangleList[ptr->ele[i]].VexList[2]].position;
		cn = obj->m_pVertexList[obj->m_pTriangleList[ptr->ele[i]].VexList[2]].norm;	
		if(Gethitpoint(_ray,rec,a,b,c,an,bn,cn,itmax,tmin))
		{
			itmax = rec.t;
			hit=true;
		}
	}
	if(hit)return true;
	return false;
}

bool Octree::BoundHit(Ray _ray,hitrecord& rec,float tmin,float tmax)
{
	double x0=_ray.origin.x(),y0 = _ray.origin.y(),z0=_ray.origin.z();
	double dx=_ray.direct.x(),dy = _ray.direct.y(),dz=_ray.direct.z();

	double txmin,tymin,tzmin,txmax,tymax,tzmax;
	
	double a = 1/dx;
	if(a>=0)
	{
		txmin = (min.x()-x0)*a;
		txmax = (max.x()-x0)*a;
	}
	else{
		txmin = (max.x()-x0)*a;
		txmax = (min.x()-x0)*a;
	}

	double b=1/dy;
	if(b>=0)
	{
		tymin = (min.y()-y0)*b;
		tymax = (max.y()-y0)*b;
	}
	else
	{
		tymin = (max.y()-y0)*b;
		tymax = (min.y()-y0)*b;
	}

	double c= 1/dz;
	if(c>=0)
	{
		tzmin = (min.z()-z0)*c;
		tzmax = (max.z()-z0)*c;
	}
	else
	{
		tzmin = (max.z()-z0)*c;
		tzmax = (min.z()-z0)*c;
	}	

	double t0,t1;
	t0=std::min(txmax,tymax);
	t0=std::min(t0,tzmax);
	t1=std::max(txmin,tymin);
	t1=std::max(t1,tzmin)+0.00001;

	if(t0>t1&&t1>tmin&&abs(t1-tmin)>0.00001&&t1<=tmax)
	{
		rec.t=t1;
		rec.hitpoint = _ray.origin+t1*_ray.direct;
		return true;
	}
	else return false;
}


bool findhit(Ray ray,std::vector<Octree*> objlist,float &tmin,float &tmax,hitrecord& rec,bool& inoct,Octree* &obj,Octree* &ptr,bool& outscene)
{
	if(inoct)
	{
		if(obj->hitOct(ray,ptr,rec,tmax,tmin))
		{
			rec.hit = true;
			obj->findsub(rec.hitpoint,ray.direct,ptr);
			return true;
		}
		else
		{
			rec.hitpoint=obj->crossBox(ray,ptr,rec.hitpoint);
			if(obj->findsub(rec.hitpoint,ray.direct,ptr))inoct=true;
			else inoct=false;
			return false;
		}
	}
	else
	{
		int num=objlist.size();
		float itmax=tmax;
		for(int i=0;i<num;i++)
		{
			if(objlist[i]->BoundHit(ray,rec,tmin,itmax))
			{
				if(itmax > rec.t)
					itmax=rec.t;
				obj = objlist[i];
				obj->findsub(rec.hitpoint,ray.direct,ptr);
				inoct = true;
			}
		}
		tmin = itmax;
		if(!inoct)
		{
			obj=NULL;
			ptr = NULL;
			outscene = true;
		}
			return false;

	}
}
