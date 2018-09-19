#include<bits/stdc++.h>
// #include "./libs/Vertex.cpp"
#include <armadillo>
#include <limits>
//library for matrix calculations

using namespace std;
using namespace arma;

// #define PI 3.14159265

class Three_To_Two
{
	public:

	// Graph2D projection;
	map<string, vector<Vertex2D>  > projection;
	// Graph3D model;
	map<string, list<Vertex3D>  > model;

	//mapping of label of 3d figure to projection point in 2d
	map< string, string> pointToProj;

	//mapping of projection points to the vector of vertices that are mapped to it in the order of distance from plane
	map< string, vector<Vertex3D> > projLabels ; 

	//mapping for faces to vertices
	map< string, vector<string> > faces_vertices;

	//mapping for vectices to facelabel
	map< string, vector<string> > vertices_faces;

	float x = 0.0, y = 0.0, z = 0.0;
	float a = 1.0;
	float b = 0.0;
	float c = 0.0;

	int choice=0;

	Vertex3D new_x, new_y;


	string input_file;
	string output_file;

	//map from name to vertex
	map<string, Vertex3D> vertices;

	//map from name of projection to coordinates of projection
	map<string, Vertex2D> result;

	map<pair<float,float>, vector<string>> vertices2D;
	int m=0, n_edges=0, n_faces=0;

	map<string,string> correspond;
	
	//all the edges in the 3d model
	vector<pair<string,string>> edges;

	int n = 0;
	float scale_factor = 1;

	//names of all vertices in 3d model
	vector<string> vertices_list;

	float alpha = 0.0, beta = 0.0, gamma = 0.0;

	// function to get the input file from user and populate the data structures accordingly
	void getInput(string in){

	    input_file = in;
	    int flag=0;
	    ifstream inFile;
	    int n_v;
	    int n_e;
	    int n_f;
	    string s,s1,s2;

	    Vertex3D v;
	    
	    // inFile.open("in.txt");
	    inFile.open(input_file);
	    if (!inFile) {
	        cout << "Unable to open file";
	        exit(1); // terminate with error
	    }

	    inFile >> n_v;
	    
	    while (n_v>0) {
	    	if (flag==0){
	    		inFile >> v.label;
	    		flag=1;
	    	}
	        if (flag==1){
	            inFile >> v.x;
	            flag=2;
	        }
	        if (flag==2){
	            inFile >> v.y;
	            flag=3;
	        }
	        else{
	        	inFile >> v.z;
	            // cout << "Got : " << v.label << " (" << v.x << "," << v.y << "," << v.z << ")" << endl;
	            // vertices.add(v.label,v);
	            vertices[v.label]=v;

	            vertices_list.push_back(v.label);
	            n++;
	            flag=0;
	            n_v--;
	        }
	    }

	    inFile >> n_e;
	    n_edges = n_e;
	    
	    while (n_e>0) {
	        if (flag==0){
	            inFile >> s1;
	            flag=1;
	        }
	        else{
	        	inFile >> s2;
	            // cout << "Got edge : "<< " (" << s1 << "," << s2 << ")" << endl;
	            // model.addEdge(s1,s2);
	            model[s1].push_back(vertices[s2]);
	            model[s2].push_back(vertices[s1]);

	            pair<string,string> temp_p;
	            temp_p.first=s1;
	            temp_p.second=s2;

	            edges.push_back(temp_p);

	            flag=0;
	            n_e--;
	        }
	    }

	    inFile >> n_f;
	    n_faces = n_f;
	    string flabel;

	    while(n_f>0){
	    	flabel = "f"+to_string(n_faces-n_f);
	    	// cout << flabel << " ";

	    	vector<string> vf;
	    	int nof;
	    	string vlabel;
	    	inFile >> nof;

	    	while(nof>0){
	    		inFile >> vlabel;
	    		vf.push_back(vlabel);
	    		if(vertices_faces.find(vlabel) == vertices_faces.end()){
	    			vector<string> fv;
	    			vertices_faces[vlabel]=fv;
	    		}
	    		vertices_faces[vlabel].push_back(flabel);
	    		
	    		// cout << vlabel << " ";
	    		nof--;
	    	}

	    	// cout << endl;

	    	faces_vertices[flabel]=vf;

	    	n_f--;

	    }

	    inFile.close();
	    // cout << "end";
	};

	// function to set the components of normal vector of the plane of projection
	void setPlane(float a1, float b1, float c1){
		a=a1;
		b=b1;
		c=c1;
	}

	// function to get normal vector of plane of projection from the user and normalise the values.
	void getPlane(){
		// cout << "1. Normal Orthographic Projections :" << endl;
		// cout << "2. Specify normal vector (new z-axis) only :" << endl;
		// cout << "3. Specify all new axes vectors :" << endl << endl;
		// cout << "Enter 1, 2 or 3 :" << endl << endl;
		// cin >> choice;

		// if(choice==1){
		// 	a = 1.0; b = 0.0; c = 0.0;
		// 	a1= 0.0; b1= 1.0; c1= 0.0;
		// 	a2= 0.0; b2= 0.0; c2= 1.0;
		// }
		// else if (choice==2){
			cout << "Enter the coefficients of normal vector of the plane :" << endl;
			cout << "Enter 'a' (coefficients of i):" << endl;
			cin >> a;
			cout << "Enter 'b' (coefficients of j):" << endl;
			cin >> b;
			cout << "Enter 'c' (coefficients of k):" << endl;
			cin >> c;

			float normal = sqrt(a*a + b*b + c*c);
			if(normal > 0){
				a /= normal;
				b /= normal;
				c /= normal;
			}
		// } else if (choice==3){
		// 	cout << "Enter the coefficients of z-axis of the plane :" << endl;
		// 	cout << "Enter 'a_z' (coefficients of i):" << endl;
		// 	cin >> a;
		// 	cout << "Enter 'b_z' (coefficients of j):" << endl;
		// 	cin >> b;
		// 	cout << "Enter 'c_z' (coefficients of k):" << endl;
		// 	cin >> c;

		// 	cout << "Enter the coefficients of y-axis of the plane :" << endl;
		// 	cout << "Enter 'a_y' (coefficients of i):" << endl;
		// 	cin >> a1;
		// 	cout << "Enter 'b_y' (coefficients of j):" << endl;
		// 	cin >> b1;
		// 	cout << "Enter 'c_y' (coefficients of k):" << endl;
		// 	cin >> c1;

		// 	cout << "Enter the coefficients of x-axis of the plane :" << endl;
		// 	cout << "Enter 'a_x' (coefficients of i):" << endl;
		// 	cin >> a2;
		// 	cout << "Enter 'b_x' (coefficients of j):" << endl;
		// 	cin >> b2;
		// 	cout << "Enter 'c_x' (coefficients of k):" << endl;
		// 	cin >> c2;

		// 	float normal = sqrt(a*a + b*b + c*c);
		// 	if(normal > 0){
		// 		a /= normal;
		// 		b /= normal;
		// 		c /= normal;
		// 	}
		// }
	};

	// function to set the new origin to the mean centroid of the input vertices.
	void shift_origin(bool calculate, bool update){
		
		float sum_x = 0.0, sum_y = 0.0, sum_z = 0.0;
		Vertex3D temp_v;

		if (calculate)
		{
			if(n==0){
				return;
			} else {

				string lbl;

				vector<string>::iterator v = vertices_list.begin();
			 	while( v != vertices_list.end()) {
				    lbl = *v;
				    temp_v = vertices[lbl];
				    sum_x += temp_v.x;
				    sum_y += temp_v.y;
				    sum_z += temp_v.z;
				    
				    v++;
				}

				x = sum_x/n;
				y = sum_y/n;
				z = sum_z/n;
			}
		}
		if (update){
			if(n==0){
				return;
			} else {

				string lbl;

				vector<string>::iterator v = vertices_list.begin();
			 	while( v != vertices_list.end()) {
				    lbl = *v;
				    temp_v = vertices[lbl];
					temp_v.x = temp_v.x - x;
					temp_v.y = temp_v.y - y;
					temp_v.z = temp_v.z - z;
				    vertices[lbl] = temp_v;
				    
				    v++;
				}
			}
		}
	}

	// function to scale the coordinates of the input vertices to reduce the complexity of calculations in future operations.
	void scale(float factor, bool autoscale, bool update){
		
		float min_x = 0.0, min_y = 0.0, min_z = 0.0;
		float max_x = 0.0, max_y = 0.0, max_z = 0.0;
		Vertex3D temp_v;

		if(!autoscale){
			if(factor==0.0){
				cout << "Enter non-zero scale factor !";
			} else {
				scale_factor = factor;
			}
		} else {
			if(n==0){
				factor=1;
			} else {

				string lbl;

				vector<string>::iterator v = vertices_list.begin();
			 	while( v != vertices_list.end()) {
				    lbl = *v;
				    temp_v = vertices[lbl];
					min_x = min(min_x,temp_v.x);
					min_y = min(min_y,temp_v.y);
					min_z = min(min_z,temp_v.z);

					max_x = max(max_x,temp_v.x);
					max_y = max(max_y,temp_v.y);
					max_z = max(max_z,temp_v.z);				    
				    v++;
				}

				factor = max( (max_x - min_x)/100 , (max_y - min_y)/100 );
				factor = max( (max_z - min_z)/100 , factor );
			}
		}

		if(update && factor!=0){
			if(n==0){
				return;
			} else {

				string lbl;

				vector<string>::iterator v = vertices_list.begin();
			 	while( v != vertices_list.end()) {
				    lbl = *v;
				    temp_v = vertices[lbl];
					temp_v.x = temp_v.x / factor;
					temp_v.y = temp_v.y / factor;
					temp_v.z = temp_v.z / factor;

					vertices[lbl] = temp_v;				    
				    v++;
				}
			}
		}
	}

	// function to modify all the coordinates when the axis are rotated by a specified amount.
	void rotate_axis(){

		mat Rx, Ry, Rz;

		Vertex3D temp_v;

		// alpha = alpha*PI/180;
		// beta = beta*PI/180;
		// gamma = gamma*PI/180;

		Rx 	<< 		1.0 	<< 		0.0 	<< 		0.0 	<< endr
			<<		0.0		<<	cos(alpha)	<<-1*sin(alpha)	<< endr
			<<		0.0		<<	sin(alpha)	<<	cos(alpha)	<< endr;

		Ry 	<< 	cos(beta) 	<< 		0.0 	<< 	sin(beta)	<< endr
			<<		0.0		<<	cos(alpha)	<<		0.0		<< endr
			<<-1*sin(beta)	<<		0.0		<<	cos(beta)	<< endr;

		Rz 	<< 	cos(gamma) 	<<-1*sin(gamma)	<< 		0.0 	<< endr
			<<	sin(gamma)	<<	cos(gamma)	<<		0.0		<< endr
			<<		0.0		<<	0.0			<<		1.0		<< endr;


		if(n==0){
				return;
			} else {

				string lbl;

				vector<string>::iterator v = vertices_list.begin();
			 	while( v != vertices_list.end()) {
				    lbl = *v;
				    temp_v = vertices[lbl];
					mat temp1, temp2;

					temp1 << temp_v.x << endr << temp_v.y << endr << temp_v.z << endr;

					temp2 = Rz*Ry*Rx*temp1;

					temp_v.x = temp2(0,0);
					temp_v.y = temp2(1,0);
					temp_v.z = temp2(2,0);

					vertices[lbl] = temp_v;				    
				    v++;
				}
			}

	}

	// function to calculate the angle by which the axis need to be rotated to obtain projection.
	void calc_angle(){
		// Let in x,y,z ->  z be the normal to the plane
		alpha = acos( b/sqrt( 1 - (c*c) ) );
		beta = acos( c );
		// Let Y be rotated such that Y falls completely on the original Z-N plane so gamma=PI
		// gamma = acos( Y3/sqrt( 1 - (c*c) ) );
		gamma = PI;
	}

	// function to find projection of all the point on the plane, join the projected points through appropriate edges
	// and order the point according to their distance from the plane.
	void project(){
		new_x.x = 0;
		new_x.y = c;
		new_x.z = -1 * b;

		new_y.x = -1 * ( (b*b) + (c*c) );
		new_y.y = a * b;
		new_y.z = a * c;

		if(b==0 && c==0){
			new_x.x = 0;
			new_x.y = 1;
			new_x.z = 0;

			new_y.x = 0;
			new_y.y = 0;
			new_y.z = 1;
		}


		// cout<<"new x = "<<new_x.x<<" "<<new_x.y<<" "<<new_x.z<<endl;
		// cout<<"new y = "<<new_y.x<<" "<<new_y.y<<" "<<new_y.z<<endl;

		float normal = sqrt(new_x.x * new_x.x + new_x.y * new_x.y + new_x.z * new_x.z);
		if(normal > 0){
			new_x.x /= normal;
			new_x.y /= normal;
			new_x.z /= normal;
		}

		normal = sqrt(new_y.x * new_y.x + new_y.y * new_y.y + new_y.z * new_y.z);
		if(normal > 0){
			new_y.x /= normal;
			new_y.y /= normal;
			new_y.z /= normal;
		}

		Vertex3D temp_v;
		Vertex2D temp_vv;

		Vertex3D v3;
		Vertex2D v2;

		float lam=0;
		float px,py,pz;
		int proj_count =1;

		if(n==0){
			return;
		} else{
			string lbl, lbl2;

			for(vector<string>::iterator v = vertices_list.begin(); v != vertices_list.end() ; v++){
				lbl = *v;
				v3 = vertices[lbl];
				v2.label = v3.label;

				lam = -1 * (a*v3.x + b*v3.y + c*v3.z) ;
				v3.distance = lam;
				vertices[lbl] = v3;
				px = a*lam + v3.x;	//coordinates of projection on plane in original axis system
				py = b*lam + v3.y;
				pz = c*lam + v3.z;

				v2.x = new_x.x * px + new_x.y * py + new_x.z * pz ;
				v2.y = new_y.x * px + new_y.y * py + new_y.z * pz ;

				// cout<<v2.label<<" x="<<v2.x<<" y="<<v2.y<<endl;

				map<string, Vertex2D>::iterator it = result.begin();
				for( ; it != result.end(); it++){

					// it->first //key
					// it->second //value

					if(abs( v2.x - (it->second).x) < 0.0001 && abs( v2.y - (it->second).y) < 0.0001 ){
						pointToProj[lbl] = (it->first);
						break;
					}
				}

				if ( result.size()==0 || it == result.end()){
					lbl2 = "p" + to_string(proj_count);
					proj_count++;

					v2.label = lbl2;
					result[lbl2] = v2;
					pointToProj[lbl] = lbl2;
				}
			}
		}

		for( vector< pair<string,string> >::iterator it = edges.begin(); it != edges.end(); it++){	//adding edges between projections
			
			string s1, s2, p1, p2;
			s1 = it->first;
			s2 = it->second;
			p1 = pointToProj[s1];
			p2 = pointToProj[s2];
			
			if(p1.compare(p2)!=0){
				if ( !findInVector(projection[p1], result[p2]) ){
					projection[p1].push_back(result[p2]);
				}
				if ( !findInVector(projection[p2], result[p1]) ){
					projection[p2].push_back(result[p1]);
				}
			}
		}

		for( map< string,string >::iterator it = pointToProj.begin(); it != pointToProj.end(); it++ ) {
			projLabels[it->second].push_back(vertices[it->first]);
		}

		for( map< string,vector<Vertex3D> >::iterator it = projLabels.begin(); it != projLabels.end(); it++){
			sort((it->second).begin() , (it->second).end() , sortfunc);
		}
	}

	// bool operator < ( const Vertex3D& lhs, const Vertex3D& rhs ){
	// 	return lhs.distance < rhs.distance ;
	// 	// return lhs.sortfunc( lhs, rhs );
	// }

	// function to find a Vertex2D in a vector of Vertex2D
	bool findInVector( vector<Vertex2D> vec, Vertex2D v){
		for(vector<Vertex2D>::iterator it = vec.begin(); it!=vec.end(); it++){
			if(it->x == v.x && it->y==v.y)
				return true;
		}

		return false;
	}

	// function to write output in a file
	void writeOutput(string out){
	    output_file = out;
	    ofstream outFile;
	    
	    outFile.open(output_file);
	    if (!outFile) {
	        cout << "Unable to open file";
	        exit(1); // terminate with error
	    }

	    // outFile << "Checking";

	    outFile << result.size() << endl;
	    for (map<string,Vertex2D>::iterator i = result.begin(); i != result.end(); ++i) {
	    	outFile <<(i->second).label<<" "<<(i->second).x<<" "<<(i->second).y<<" ";
	    	outFile<<projLabels[i->first].size();

	    	for( vector<Vertex3D>::iterator it = projLabels[i->first].begin() ; it != projLabels[i->first].end() ; ++it){
	    		outFile<<" "<<it->label;
	    	}
	    	outFile<<endl;
	    }

	    string str = "";
	    int num =0 ;
	    // outFile<<projection.size()<<endl;
	    for (map<string,vector<Vertex2D> >::iterator i = projection.begin(); i != projection.end(); ++i)
	    {
	    	num += (i->second).size();
	    	// cout<<i->first<<"\tsize = "<<(i->second).size()<<"\t";
	    	for (vector<Vertex2D>::iterator it = (i->second).begin(); it != (i->second).end(); ++it)
	    	{

	    		str += i->first + " " + it->label + "\n";
	    		// outFile<<i->first<<" "<<it->label<<endl;
	    	}
	    }
	    outFile<<num<<endl<<str;
	};

	// function to plot the output
	void plotOutput(string out){
	    ofstream outFile;
	    
	    outFile.open(out);
	    if (!outFile) {
	        cout << "Unable to open file";
	        exit(1); // terminate with error
	    }
	    
		int total = 0;
		vector<string> top_v2;

		string max_v1;
		float max_z1= -1.0*(std::numeric_limits<float>::infinity());

		for (map<string,Vertex3D >::iterator i = vertices.begin(); i != vertices.end(); ++i)
	    {
	    	Vertex3D temp_v3 = i->second;
	    	if( (a*temp_v3.x + b*temp_v3.y + c*temp_v3.z) > max_z1){
	    	// if( temp_v3.z < max_z1){
	    		max_z1 = (a*temp_v3.x + b*temp_v3.y + c*temp_v3.z);
	    		max_v1 = i->first;
	    	}
	    }

		// max_v1="g";

	    // cout << max_v1 << endl;

	    // for (map<string,Vertex3D >::iterator i = model.begin(); i != model.end(); ++i)
	    // {
	    // 	Vertex3D temp_v3 = i->second;
	    // 	if( (temp_v3.z > max_z2) && ( (i->first).compare(max_z1)!=0 )  ){
	    // 		max_z2 = temp_v3.z;
	    // 		max_v2 = i->first;
	    // 	}
	    // }


	    vector<string> top_face = vertices_faces[max_v1];

		// string top_face1="f1";
		// string top_face2="f2";


		vector<string> top_v;

		// top_v=faces_vertices[top_face1];

		for(vector<string>::iterator i = top_face.begin(); i != top_face.end(); ++i){

			top_v=faces_vertices[*i];

			for(vector<string>::iterator it = top_v.begin(); it != top_v.end(); ++it){
				string current = *it;
				// cout << current << " " << pointToProj[current] << endl;
				top_v2.push_back(pointToProj[current]);
			}

		}
		// cout << endl << endl << endl << endl;

		// top_v=faces_vertices[top_face2];
		// for(vector<string>::iterator it = top_v.begin(); it != top_v.end(); ++it){
		// 	string current = *it;
		// 	// cout << current << " " << pointToProj[current] << endl;
		// 	top_v2.push_back(pointToProj[current]);
		// }


		for (map<string,vector<Vertex2D> >::iterator i = projection.begin(); i != projection.end(); ++i)
		{
			// cout<<i->first<<"\tsize = "<<(i->second).size()<<"\t";
			for (vector<Vertex2D>::iterator it = (i->second).begin(); it != (i->second).end(); ++it)
			{
				total++;
			}
		}

		outFile << total << endl;

		for (map<string,vector<Vertex2D> >::iterator i = projection.begin(); i != projection.end(); ++i)
		{
			// cout<<i->first<<"\tsize = "<<(i->second).size()<<"\t";
			for (vector<Vertex2D>::iterator it = (i->second).begin(); it != (i->second).end(); ++it)
			{
				if(find(top_v2.begin(), top_v2.end(),result[i->first].label) != top_v2.end()){

					if(find(top_v2.begin(), top_v2.end(),it->label) != top_v2.end()){
						outFile<<result[i->first].x<<" "<<result[i->first].y<<endl;
						outFile<<it->x<<" "<<it->y<<" "<<"0"<<endl;
					} else {
						outFile<<result[i->first].x<<" "<<result[i->first].y<<endl;
						outFile<<it->x<<" "<<it->y<<" "<<"1"<<endl;
					}

				} else {
					outFile<<result[i->first].x<<" "<<result[i->first].y<<endl;
					outFile<<it->x<<" "<<it->y<<" "<<"1"<<endl;
					// cout << result[i->first].label << " " << it->label << endl;
				}
			}
		}

		outFile.close();
	};

};
