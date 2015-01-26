/** benchtree.cpp created by Mingxuan Wang
 */

#include "BST.hpp"
#include "RST.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>
#include "countint.hpp"

using namespace std;

int main(int argc, char* argv[]){
	srand((unsigned)time(NULL));               //used for random priority
	
	//check for valid input
	if (argc != 5){
		printf("Invalid command line input. Please follow the instructions and restart!\n");
		printf("1st: bst, rst or set; 2nd: sorted or shuffled; 3rd: maximum size; 4th: rum times.\n");
		return -1;
	}
	
	string treeType = argv[1];
	string orderType = argv[2];
	int max = atoi(argv[3]);
	int times = atoi(argv[4]);
	
	if (treeType != "bst" && treeType != "rst" && treeType != "set"){
		printf("Invalid command line input. Please follow the instructions and restart!\n");
		printf("1st: bst, rst or set.\n");
		return -1;
	}
	
	bool sort;
	if (orderType == "sorted"){
		sort = true;
	}else if (orderType == "shuffled"){
		sort = false;
	}else{
		printf("Invalid command line input. Please follow the instructions and restart!\n");
		printf("2nd: sorted or shuffled.\n");
		return -1;
	}
	
	//print head information
	cout << "# Benchmarking average number of comparisons for successful find"<< endl;
    cout << "# Data structure: " << treeType << endl;
    cout << "# Data: " << orderType << endl;
    cout << "# N is powers of 2, minus 1, from 1 to " << max << endl;
    cout << "# Averaging over " << times << " runs for each N" << endl;
    cout << "#" << endl;
    cout << "#" << " N" << "\t\t" << "avgcomps" << "\t\t" << "stdev" << endl;
	
	//iterate for 1 up to N
	int currentSize = 1;
	while (currentSize <= max){
		//create a vector with max # of continent keys
		std::vector<countint> v;
		v.clear();
		for(int i = 0; i < currentSize; ++i) {
			v.push_back(i);
		}
		
		//if not sorted, shuffle the vector
		if (!sort){
			std::random_shuffle(v.begin(),v.end());
		}
		
		vector<countint>::iterator vit = v.begin();       //create iterator through the vector -- for insert and find
    vector<countint>::iterator ven = v.end();
		
		double avgcomps = 0.0;                            
		double t = 0.0;
		double s = 0.0;
		double stdev = 0.0;
		
		//iterate for times of a certain max 
		for (int i = 0; i < times; ++i){
			
			if (treeType == "bst"){
				
				BST<countint> *bst = new BST<countint>();
				for (vit = v.begin(); vit != ven; ++vit){
					bst->insert(*vit);
				}
				
				countint::clearcount();
				for(vit = v.begin(); vit != ven; ++vit) {
					bst->find(*vit);
				}
				
        delete bst;
        			
      }else if (treeType == "rst"){
				
				RST<countint> *rst = new RST<countint>();
				for (vit = v.begin(); vit != ven; ++vit){
					rst->insert(*vit);
				}
				
				countint::clearcount();
				for(vit = v.begin(); vit != ven; ++vit) {
					rst->find(*vit);
				}
				
        delete rst;
        
			}else if (treeType == "set"){
				
				std::set<countint> rbt;
				rbt.clear();
				for (vit = v.begin(); vit != ven; ++vit){
					rbt.insert(*vit);
				}
				
				countint::clearcount();
				for(vit = v.begin(); vit != ven; ++vit) {
					rbt.find(*vit);
				}
			}
		  avgcomps = countint::getcount()/(double)currentSize;
			t += avgcomps;
			s += (avgcomps * avgcomps);
		}
		t = t / (double)times;
		s = s / (double)times;
		stdev = sqrt(fabs(s - t * t));
    if (stdev < 0.00001){
      stdev = 0;
    }
		
		cout << currentSize << "\t\t" << t <<  "\t\t" << stdev << endl;
		currentSize = (currentSize << 1) + 1;
	}
	
	
}