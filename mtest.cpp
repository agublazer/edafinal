#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include <time.h>
#include "vptree2.h"
#include <stdlib.h>
using namespace std;



int main(){
	using namespace std::chrono;
	vector<point> points;
	string line;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ifstream file ("data.txt");
	std::string::size_type sz;

	while(getline(file,line)){
	    std::stringstream   linestream(line);
	    std::string         value;
		point np;
	    while(getline(linestream,value,',')){
	    
	    	np.push_back(stod(value,&sz));
        	// std::cout << "Value(" << value << ")\n";
    	}
    	//cout<<np.size()<<endl;
    	points.push_back(np);
    	np.clear();
	}
	cout<<points.size()<<endl;
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

  	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  	std::cout << "Generate points for vp tree took " << time_span.count() << " seconds.";
  	std::cout << std::endl;

  	vp_tree t(5);
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	t.create(points);
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

  	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);

  	std::cout << "Indexing for vp tree took " << time_span2.count() << " seconds.";
  	std::cout << std::endl;

  	high_resolution_clock::time_point t5 = high_resolution_clock::now();
  	srand(time(NULL));
	t.knn(6,points[rand()%points.size()]);
	high_resolution_clock::time_point t6 = high_resolution_clock::now();

  	duration<double> time_span3 = duration_cast<duration<double>>(t6 - t5);

  	std::cout << "Searching for vp tree took " << time_span3.count() << " seconds.";
  	std::cout << std::endl;

}
