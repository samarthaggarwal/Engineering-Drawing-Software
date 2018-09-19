#include<bits/stdc++.h>
using namespace std;

struct Vertex2D
{
	string label;
    float x;
    float y;
};

struct Point2D
{
    float x;
    float y;
};


struct Vertex3D
{
	string label;
    float x;
    float y;
    float z;
    float distance;
};

bool sortfunc(const Vertex3D& lhs , const Vertex3D& rhs){
	return lhs.distance < rhs.distance ;
}