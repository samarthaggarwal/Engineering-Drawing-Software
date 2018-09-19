#include<bits/stdc++.h>
// #include "./libs/Vertex.cpp"
#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

// #define PI 3.14159265

class Two_To_Three
{
	public:

	string xy_file, yz_file, zx_file;

	// Graph2D projection;
	map<string, Vertex3D > model;

	// Set of Vertices labels
	set<string> vertices_list;

	// Map with Vertices labels as key and 3D verties values
	map<string, Vertex2D> vertices_xy;
	map<string, Vertex2D> vertices_yz;
	map<string, Vertex2D> vertices_zx;

	//Vertices map to common 2D Labels
	map<string, string> map_xy;
	map<string, string> map_yz;
	map<string, string> map_zx;

	//Edge map
	vector<pair<string,string>> edge_xy;
	vector<pair<string,string>> edge_yz;
	vector<pair<string,string>> edge_zx;

	//Expanded Edges
	vector<pair<string,string>> exp_xy;
	vector<pair<string,string>> exp_yz;
	vector<pair<string,string>> exp_zx;

	//Reverse map
	map<string, vector<string>  > rev_xy;
	map<string, vector<string>  > rev_yz;
	map<string, vector<string>  > rev_zx;

	//Complete edges
	set<pair<string,string>> edges;

	float scale_factor = 1;
	

	// Method to get input from file

	void getInput(string xy, string yz, string zx){

	    xy_file = xy;
	    yz_file = yz;
	    zx_file = zx;
	    ifstream inFile;
	    int n_v;
	    int n_e;

	    Vertex2D v;
	    
	    // Input from XY File

	    inFile.open(xy_file);
	    if (!inFile) {
	        cout << "Unable to open xy file << endl << endl";
	        exit(1); // terminate with error
	    }

	    inFile >> n_v;
	    
	    while (n_v>0) {
	    	inFile >> v.label;
	    	inFile >> v.x;
	    	inFile >> v.y;
	    	int np =0;
	    	vertices_xy[v.label] = v;
	    	inFile >> np;
	    	vector<string> vlist;
	    	// cout << v.label << " " << v.x << " " << v.y << endl;
	    	while(np>0){
	    		np--;
	    		string cur = "";
	    		inFile >> cur;
	    		vlist.push_back(cur);
	    		map_xy[cur]=v.label;
	    		// cout << cur << endl;
	    		vertices_list.insert(cur);
	    	}
	    	rev_xy[v.label] = vlist;
	    	n_v--;
	    }

	    inFile >> n_e;

	    while(n_e>0){
	    	pair<string,string> temp_p;
	    	inFile >> temp_p.first;
	    	inFile >> temp_p.second;
	    	edge_xy.push_back(temp_p);
	    	n_e--;
	    }

	    inFile.close();
	    // cout << "end_xy" << endl;


	   	n_v=0;
	   	n_e=0;




	   	// Input from YZ file

	   	inFile.open(yz_file);
	    if (!inFile) {
	        cout << "Unable to open yz file" << endl << endl << endl;
	        exit(1); // terminate with error
	    }

	    inFile >> n_v;
	    
	    while (n_v>0) {
	    	inFile >> v.label;
	    	inFile >> v.x;
	    	inFile >> v.y;
	    	int np =0;
	    	vertices_yz[v.label] = v;
	    	inFile >> np;
	    	vector<string> vlist;
	    	// cout << v.label << " " << v.x << " " << v.y << endl;
	    	while(np>0){
	    		np--;
	    		string cur = "";
	    		inFile >> cur;
	    		vlist.push_back(cur);
	    		map_yz[cur]=v.label;
	    		// cout << cur << endl;
	    		vertices_list.insert(cur);
	    	}
	    	rev_yz[v.label] = vlist;
	    	n_v--;
	    }

	    inFile >> n_e;

	    while(n_e>0){
	    	pair<string,string> temp_p;
	    	inFile >> temp_p.first;
	    	inFile >> temp_p.second;
	    	edge_yz.push_back(temp_p);
	    	n_e--;
	    }

	    inFile.close();
	    // cout << "end_yz" << endl;


	    n_v=0;
	    n_e=0;



	    // Input from ZX File

	    inFile.open(zx_file);
	    if (!inFile) {
	        cout << "Unable to open zx file << endl";
	        exit(1); // terminate with error
	    }

	    inFile >> n_v;
	    
	    while (n_v>0) {
	    	inFile >> v.label;
	    	inFile >> v.x;
	    	inFile >> v.y;
	    	int np =0;
	    	vertices_zx[v.label] = v;
	    	inFile >> np;
	    	vector<string> vlist;
	    	// cout << v.label << " " << v.x << " " << v.y << endl;
	    	while(np>0){
	    		np--;
	    		string cur = "";
	    		inFile >> cur;
	    		vlist.push_back(cur);
	    		map_zx[cur]=v.label;
	    		// cout << cur << endl;
	    		vertices_list.insert(cur);
	    	}
	    	rev_zx[v.label] = vlist;
	    	n_v--;
	    }

	    inFile >> n_e;

	    while(n_e>0){
	    	pair<string,string> temp_p;
	    	inFile >> temp_p.first;
	    	inFile >> temp_p.second;
	    	edge_zx.push_back(temp_p);
	    	n_e--;
	    }

	    inFile.close();
	    // cout << "end_zx" << endl;

	    // expand_h(edge_xy,rev_xy,exp_xy);
	};



	// Helper function for making all possible edges using any one plane

	void expand_h(vector<pair<string,string>>& edge_xy1, map<string, vector<string> >& rev_xy1, vector<pair<string,string>>& exp_xy1){
		//Expanding
		for (std::vector<pair<string,string>>::iterator it = edge_xy1.begin() ; it != edge_xy1.end(); ++it){
			pair<string,string> temp_p = *it;
			string p1 = temp_p.first;
			string p2 = temp_p.second;
			// cout << p1 << endl;

			for (std::vector<string>::iterator it1 = rev_xy1[p1].begin() ; it1 != rev_xy1[p1].end(); ++it1){
				string temp_s1 = *it1;
				// cout << temp_s1 << endl;
				for (std::vector<string>::iterator it2 = rev_xy1[p2].begin() ; it2 != rev_xy1[p2].end(); ++it2){
					string temp_s2 = *it2;
					// cout << temp_s1 << endl;
					pair<string,string> temp_pp;
					temp_pp.first = min(temp_s1,temp_s2);
					temp_pp.second = max(temp_s1,temp_s2);
					exp_xy1.push_back(temp_pp);
					// cout << exp_xy1.size() << endl;
				}
			}
		}
		// cout << exp_xy1.size() << endl;
	}


	// Building all possible edges using all the planes

	void expand(){
		expand_h(edge_xy,rev_xy,exp_xy);
		// cout << exp_xy.size() << endl;
		expand_h(edge_yz,rev_yz,exp_yz);
		expand_h(edge_zx,rev_zx,exp_zx);
	}


	// Helper function for Eliminating edges

	void eliminate_h(vector<pair<string,string>>& exp_xy1, vector<pair<string,string>>& exp_xy2, map<string, string> map_xy2){

		// int rem=0;
		for (std::vector<pair<string,string>>::iterator it = exp_xy1.begin() ; it != exp_xy1.end();){
			pair<string,string> temp_p1 = *it;
			string p11 = temp_p1.first;
			string p12 = temp_p1.second;
			// cout << p11 << endl;
			bool res = false;
			
			for (std::vector<pair<string,string>>::iterator it1 = exp_xy2.begin() ; it1 != exp_xy2.end(); ++it1){
				pair<string,string> temp_p2 = *it1;
				string p21 = temp_p2.first;
				string p22 = temp_p2.second;	

				if( (p11.compare(p21)==0) && (p12.compare(p22)==0) ){
					res=true;
					break;
				}
				if( (p11.compare(p22)==0) && (p12.compare(p21)==0) ){
					res=true;
					break;
				}
				if( map_xy2[p11].compare(map_xy2[p12])==0 ){
					res=true;
					break;
				}
			}

			if(res==false){
				it = exp_xy1.erase(it);
			} else {
				++it;
			}

		}

	}

	// Eliminating Edges

	void eliminate(){
		eliminate_h(exp_xy,exp_yz, map_yz);
		eliminate_h(exp_yz,exp_xy, map_xy);
		eliminate_h(exp_yz,exp_zx, map_zx);
		eliminate_h(exp_zx,exp_yz, map_yz);
		eliminate_h(exp_xy,exp_zx, map_zx);
		eliminate_h(exp_zx,exp_xy, map_xy);
	}



	// Method to map each vertices to Vertex3D with all it's co-ordinates
	// and also scale then on a scale of 100 units

	void find_all(){
		Vertex3D temp_v3;
		Vertex2D temp_v2;

		float min_x = 0.0, min_y = 0.0, min_z = 0.0;
		float max_x = 0.0, max_y = 0.0, max_z = 0.0;


		for (std::set<string>::iterator it=vertices_list.begin(); it!=vertices_list.end(); ++it){
			string temps = *it;

			// cout << temps << " : ";

			//From xy diagram
			temp_v2 = vertices_xy[map_xy[temps]];
			temp_v3.label = temps;
			// cout << temp_v2.x << endl;
			// cout << temp_v2.y << endl;
			temp_v3.x = temp_v2.x;
			temp_v3.y = temp_v2.y;

			//From yz diagram
			temp_v2 = vertices_yz[map_yz[temps]];
			// cout << temp_v2.y << endl;
			temp_v3.z = temp_v2.y;

			min_x = min(min_x,temp_v3.x);
			min_y = min(min_y,temp_v3.y);
			min_z = min(min_z,temp_v3.z);

			max_x = max(max_x,temp_v3.x);
			max_y = max(max_y,temp_v3.y);
			max_z = max(max_z,temp_v3.z);

			model[temps]=temp_v3;
		    // cout << model[temps].label << " : " << model[temps].x << ", " << model[temps].y << ", " << model[temps].z << endl;
		}

		scale_factor = max( (max_x - min_x)/100 , (max_y - min_y)/100 );
		scale_factor = max( (max_z - min_z)/100 , scale_factor );


		// Scaling in a scale of 100 units

		for (std::set<string>::iterator it=vertices_list.begin(); it!=vertices_list.end(); ++it){
			string temps = *it;

			temp_v3 = model[temps];
			temp_v3.x = temp_v3.x / scale_factor;
			temp_v3.y = temp_v3.y / scale_factor;
			temp_v3.z = temp_v3.z / scale_factor;

			model[temps]=temp_v3;
		    // cout << model[temps].label << " : " << model[temps].x << ", " << model[temps].y << ", " << model[temps].z << endl;
		}
	}



	// Helper for finding Pair of edges <string,string> in single plane

	void edges_one(vector<pair<string,string>>& exp_xy1){
		for (std::vector<pair<string,string>>::iterator it=exp_xy1.begin(); it!=exp_xy1.end(); ++it){
			pair<string,string> temps = *it;
			edges.insert(temps);
		}
	}


	// All the Pair of edges <string,string>

	void edges_all(){
		edges_one(exp_xy);
		edges_one(exp_yz);
		edges_one(exp_zx);
	}


	// Writing output to a file (this can be used as an input for ThreeToTwo)

	void writeOutput(string out){
	    // output_file = out;
	    ofstream outFile;
	    
	    outFile.open(out);
	    if (!outFile) {
	        cout << "Unable to open file";
	        exit(1); // terminate with error
	    }

	    // outFile << "Checking";

		outFile << vertices_list.size() << endl;

		for (std::set<string>::iterator it=vertices_list.begin(); it!=vertices_list.end(); ++it){
			string temps = *it;
			outFile << temps << " " << model[temps].x << " " << model[temps].y << " " << model[temps].z << endl;
			// cout << temps.first << " <->" << temps.second << endl;
		}

	    outFile << edges.size() << endl;


		for (std::set<pair<string,string>>::iterator it=edges.begin(); it!=edges.end(); ++it){
			pair<string,string> temps = *it;
			outFile << temps.first << " " << temps.second << endl;
		}


	    outFile.close();
	    // cout << "end";
	};


	// Writing plot output to a file based of plotting algorithm

	void plotOutput(string out){
	    // output_file = out;
	    ofstream outFile;
	    
	    outFile.open(out);
	    if (!outFile) {
	        cout << "Unable to open file";
	        exit(1); // terminate with error
	    }

	    outFile << edges.size() << endl;


		for (std::set<pair<string,string>>::iterator it=edges.begin(); it!=edges.end(); ++it){
			pair<string,string> temps = *it;
			outFile << model[temps.first].x << " " << model[temps.first].y << " " << model[temps.first].z << endl;
			outFile << model[temps.second].x << " " << model[temps.second].y << " " << model[temps.second].z << endl;
		}


	    outFile.close();
	    // cout << "end";
	};

};
