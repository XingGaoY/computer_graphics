#include "Triangle.h"

bool Triangle::Gethitpoint(const Ray& ray,	hitrecord& record) const
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
	if(abs(t)<0.00001)return false;
	float M = A * EIHF + B * GFDI + C * DHEG;
	t = -t / M;
	beta = ( J * EIHF + K * GFDI + L * DHEG) / M;
	if(beta < 0 || beta > 1) return false;
	gamma = ( I * AKJB + H * JCAL + G * BLKC) / M;
	if(gamma < 0 || gamma > 1) return false;
	alpha = 1 - beta - gamma;
	if(alpha < 0 || alpha > 1)return false;
	record.hitpoint = ray.origin + t * ray.direct;
	record.norm = Getnorm(cross( p1 - p0, p2 - p0));
	record.t = t;
	return true;
}
