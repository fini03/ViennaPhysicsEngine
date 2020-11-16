
#define _USE_MATH_DEFINES
#include <cmath>

#include <stdio.h>
#include <array>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

#include "sat.h"
#include "GJK.h"

int main() {

	Line line{ {0.f,0.f, -1.f}, {0.f,0.0f,1.f} };

	Tetrahedron tet{ {-1.0f, 0.0f, -1.0f}, {1.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.5f} };
	Triangle tri{ {-1.0f, 0.0f, -1.0f}, {1.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f} };


	Box ground{ {0.0f, -50.0f, 0.0f}, scale( mat4(1.0f), vec3(100.0f, 100.0f, 100.0f)) };
	Box box{ {0.0f, 0.5f, 0.0f} };
	vec3 mtv(0,1,0); //minimum translation vector
	auto hit1 = gjk(&box, &ground, &mtv);

	auto hit2 = sat( (Collider*)&box, (Collider*)&ground, &mtv);

	Point point{ {0,-10,0} };
	auto hit3 = gjk(&point, &ground, &mtv);

	Triangle triangle{ {-1,0,0}, {1,0,0}, {0,1,0} };
	auto hit4 = gjk(&triangle, &ground, &mtv);

	Quad quad{ {-1,0,-1}, {1,0,-1}, {1,0,1}, {-1,0,1} };
	auto hit5 = gjk(&quad, &ground, &mtv);

	auto hit7 = gjk(&triangle, &quad, &mtv);

	//--------------------------------------------------------------------

	//get all vertex neighbors of vertex 0
	int v = 0;
	std::set<int> neighbors;
	box.get_vertex_neighbors( v, neighbors);

	//get all edges of face 0
	int f = 0;
	auto edges  = box.get_face_edges( f );
	auto &edges2 = box.get_face_edges( f );

	//get the faces that contain a given edge
	int e = 0;
	std::set<int> faces;
	box.get_edge_faces( e, faces);

	//get the neighboring faces of a given face
	std::set<int> faces2;
	box.get_face_neighbors( f, faces2);



}
