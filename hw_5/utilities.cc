#include<math.h>
#include<iostream>
#include<vector>
#include<stdexcept>
#include<cstdlib>
#include <algorithm>
#include <map>
#include "typed_matrix.h"
#include "utilities.h"
using std::vector;
using namespace std;

vector<double> sort_by_magnitude(vector<double> &v){
    std::sort(v.begin(), v.end(), [](double x, double y) { 
        return abs(x) < abs(y);
    });
    return v;
}

TypedMatrix<double> read_matrix_csv(const string path){
    
    vector<vector<double>> k;
    vector<double> v;
    std::ifstream file;
    file.open(path);
    std::string line,val;
    int i,j =0;
    int col_nm = 0;

    while(std::getline(file,line)){
        std::istringstream ss(line);
        v.clear();
        int col_nm = 0;
        while (getline(ss,val,',')){
            val.erase(0,val.find_first_not_of(" \t"));
            val.erase(val.find_last_not_of(" \t")+1,val.size()-val.find_last_not_of(" \t"));
            string::size_type p = val.find(" ");
            string::size_type t = val.find("\t");
            if (p!=val.npos || t!=val.npos){
                throw std::range_error("unoffice matrix element error");
            }
            double nm = 0;
            nm = std::stod(val);
            //m.set(i,j,nm);
            v.push_back(nm);
            col_nm++;
            //std::cout<<"v size ="<<v.size()<<"\n";
        }
        k.push_back(v);
        if (j==0){
            i = col_nm;
        }
        j++;
        if (col_nm != i){
            throw std::range_error("matric size error");
        }
        //std::cout<<"k size ="<<k.size()<<"\n";
    }
    TypedMatrix<double> m(k[0].size(), k.size());
    for(i=0 ; i<k.size();i++ ){
        for(j =0 ; j<k[0].size(); j++){
            m.set(i,j,k[i][j]);
        }
    }
    //std::cout<<"m size ="<<m.matrix.size()<<"\n";
    return m;
}

void write_matrix_csv(const TypedMatrix<double> &matrix, const string path){
    std::ofstream outfile;
    outfile.open(path);
    int i,j;
    std::string s;
    for(i=0;i< matrix.size_row();i++)
	{
        s = std::to_string(matrix.get(i,0));
        outfile << matrix.get(i,0);
		for(j=1;j<matrix.size_col();j++)
		{
            s = std::to_string(matrix.get(i,j));
			outfile<<","<<s;
		}
        outfile << endl;
	}
	outfile.close();
}

map<string, int> occurence_map(const string path){
    map<string, int> result;
    bool can_do = true;
    int front = 0,good=0,end=0;

    std::ifstream file;
    file.open(path);
    std::string line,val;
    while(std::getline(file,line)){
        std::istringstream ss(line);
        while(std::getline(ss,val,' ')){
            int front = 0,good=0,end=val.size();
            can_do = true;
            for(int j = 0; j<val.length();j++) {
                //std::cout<<val<<"\n";
                if ((val[j]>='0' && val[j]<='9') || (val[j]>='a' && val[j]<='z') || (val[j]>='A' && val[j]<='Z') || (val[j] == '\'')){
                    good = good+1;
                    if (val[j]>='A' && val[j]<='Z'){
                        val[j]+=32;
                    }
                    if (end !=val.size() ){
                        can_do = false;
                    }
                }else{
                    if (good == 0){
                        front = front+1;
                    }else{
                        if (end == val.size()){
                            end = j;
                        }
                    }
                }
            }
            if (can_do == true){
                //std::cout<<"I can do ";
                std::cout<<"good = "<<good<<"front = "<<front<<"end"<<end<<"\n";
                val.erase(val.begin()+end,val.end());
                val.erase(val.begin(),val.begin()+front);

                std::cout<<"n:"<<val<<"\n";
                //val.erase(0,front);
                //val.erase(end,val.length()-end);
                //std::cout<<"I erase ";

                if(result.count(val)==1){
                    result.insert(pair<string,int>(val,result[val]+1));
                }else{
                    result[val] = 1;
                }
                //std::cout<<"I push ";
            }
        }  
    }
    return result;
}