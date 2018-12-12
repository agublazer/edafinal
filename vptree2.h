#include <sstream>
#include <iterator>
#include <iostream> 
#include <cmath> 
#include <utility>
#include <vector>
#include <limits>
#include <queue>
#include <fstream>
#include <set>
#include <time.h>
#define point vector<double>
#define SAMPLE_SIZE 30
using namespace std; 


int curr_level = 0;
bool same_points(point a, point b){ 
    bool result = true;
    for(int i = 0; i< a.size();i++){
        result = result and (a[i]==b[i]);
    }
    return result;
}

bool more_than(point a, point b){ 
    bool result = true;
    for(int i = 0; i< a.size();i++){
        result = result and (a[i]>=b[i]);
    }
    return result;
}

double euclidean_distance(point a, point b){
    double acc = 0;
    for(int i = 0; i<a.size();i++){
        acc += pow(a[i]-b[i],2);
    }
    return sqrt(acc);
}

bool greater_distance(point start, point end1, point end2){
    double distance1 = euclidean_distance(start, end1);
    double distance2 = euclidean_distance(start, end2);
    return distance1 < distance2;
}
    
point get_top_right_point(vector<point> points){
    int n = points.size();
    point max_p = points[0];

    for(int i = 1; i < n; i++){
        if (more_than(points[i],max_p)){
            max_p = points[i];
        }

    }
    return max_p;
}


class node 
{ 
public:
    node *inside;
    node *outside;

    vector<point> points; 
    point vp;
    double mu;
    bool is_leaf;

    node(vector<point> new_points){
        is_leaf = true;
        inside = nullptr;
        outside = nullptr;
        points = new_points;
        mu = 0;
    }
    node(){
        is_leaf = true;
        inside = nullptr;
        outside = nullptr;
        mu = 0;
    }
    void no_leaf(){
        points.clear();
        is_leaf = false;
    }
    bool in_region(point p){
        return (euclidean_distance(vp,p)<=mu);
    }

    bool in_node(point p){
        for(int i = 0; i<points.size();i++){
            if(same_points(p,points[i]))
                return true;
        }
        return false; 
    }

    void choose_vp(){
        
        vector<point> sample;
        sample.resize(SAMPLE_SIZE);
        int total_size = points.size();
        srand(time(NULL));
        for(int i = 0; i < SAMPLE_SIZE; i++){
            sample[i] = points[rand()%total_size];
        }

        vp = get_top_right_point(sample);

    }

    void calc_mu(){

        int n = points.size();
        double distances[n];

        for(int i = 0; i < n; i++){
            distances[i] = euclidean_distance(vp, points[i]);
        }
        mu = distances[n/2];
    }
    void create_tree(){
        if(points.size() <= 10){
            return;
        }
            int g = 0;
            choose_vp();
            calc_mu();
            int n = points.size();

            vector<point> inside_points;
            vector<point> outside_points;

            for(int i = 0; i < n; i++){
                double distance = euclidean_distance(vp, points[i]);
                if (distance < mu){
                    inside_points.push_back(points[i]);
                }
                else{
                    outside_points.push_back(points[i]);
                }
            }

            no_leaf();
            
            inside = new node(inside_points);
            outside = new node(outside_points);
            
            inside->create_tree();
            
            outside->create_tree();
        

    }
}; 

point start;

struct my_comparator
{
    // queue elements are vectors so we need to compare those
    // point start;
    bool operator()(point end1, point end2){
        double distance1 = euclidean_distance(start, end1);
        double distance2 = euclidean_distance(start, end2);
        return (distance1 < distance2);
    }
};

class vp_tree{
public:
    node *root;
    int max_p;

    vp_tree(int m){
        root = nullptr;
        max_p = m;
    }

    void create(vector<point> points){
        root = new node(points);
        root -> create_tree(points.size()/2);
    }

    void inorder(node *curr, int level){
        cout<<"level: "<<level<<endl;
        cout<<"size: "<<curr->points.size()<<endl;
        if (curr->inside){
            cout<<"###############################inside###################################"<<endl;
            inorder(curr->inside, level+1);
        }
        if (curr->outside){
            cout<<"##############################333outside##############################"<<endl;
            inorder(curr->inside, level+1);
        }
    }
    void print(){
        inorder(root, 0);
    }
    void knn (int k, point query) {
        node *curr = root;
        start = query;
        //point new_area_a,new_area_b;
        ofstream output_file ("knn.txt");
        set<point, my_comparator> results;
        while ( curr and  curr->is_leaf == false){
            if (euclidean_distance(curr->vp,query) < curr->mu){
                curr = curr->inside;
            }
            else{
                curr = curr->outside;
            }
        }
        for(int i = 0; i<curr->points.size();i++){
            results.insert(curr->points[i]);
        }
        output_file <<"query: \n";
        for(int j = 0; j<query.size(); j++){
            std::ostringstream strs;
            strs << query[j];
            string str = strs.str();
            output_file<<str;
            output_file<<" , ";
        }
        output_file << "\n";
        output_file <<"knn: \n";
        for (std::set<point, my_comparator>::iterator it=results.begin(); it!=results.end(); ++it){
            point pa = *it;
            vector<string> values;
            for(int j = 0; j<pa.size(); j++){
                std::ostringstream strs;
                strs << pa[j];
                string str = strs.str();
                output_file<<str;
                output_file<<" , ";
            }
            output_file << "\n";
            cout<<endl;
            cout<<"distance: "<<euclidean_distance(start,pa)<<endl;
        }
        output_file.close();
    }

};

