// COMSC-210 | Lab 25 | Arkhip Finski
// IDE used: Visual Studio
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <set>
#include <list>
#include <vector>
#include <numeric>
#include <chrono>
using namespace std;
using namespace std::chrono;


// const int SZ = 20000, COLS = 3, ROWS = 4, TESTS = 4;
const int STRUCTURES = 3;
const int ROWS = 4, COLS = 3, SUM = 15;
const int W1 = 10;

int main() {
    long long results[ROWS][COLS][SUM];
    string cd;
    vector<string> data_vector;
    list<string> data_list;
    set<string> data_set;

    // testing for READ operations
    for (int i = 0; i < STRUCTURES; i++) {
        ifstream fin("codes.txt");
        switch(i) {
            case 0: {  // read into a vector
                for(int j = 0; j < SUM; j++){
                    data_vector.clear();
                    auto start = chrono::high_resolution_clock::now();
                    while (fin >> cd){
                        data_vector.push_back(cd);
                    }    
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][i][j] = duration.count();
                }
                
                break;
            }
            case 1: {  // read into a list
                for(int j = 0; j < SUM; j++){
                    data_list.clear();
                    auto start = chrono::high_resolution_clock::now();
                    while (fin >> cd){
                        data_list.push_back(cd);
                    } 
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][i][j] = duration.count();
                }
                break;
            }
            case 2: {  // read into a set
                for(int j = 0; j < SUM; j++){
                    data_set.clear();
                    auto start = chrono::high_resolution_clock::now();
                    while (fin >> cd){
                        data_set.insert(cd);
                    }    
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][i][j] = duration.count();
                }
                break;
            }
        }
        fin.close();
    }

    // testing for SORT operations
    for (int i = 0; i < STRUCTURES; i++) {
        switch(i) {
            case 0: {  // sort a vector
                for(int j = 0; j < SUM; j++){
                    auto start = chrono::high_resolution_clock::now();
                    sort(data_vector.begin(), data_vector.end());
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[1][i][j] = duration.count();
                }
                break;
            }
            case 1: {  // sort a list
                for(int j = 0; j < SUM; j++){
                    auto start = chrono::high_resolution_clock::now();
                    data_list.sort();
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[1][i][j] = duration.count();
                }
                break;
            }
            case 2: {  // can't sort a set, so set to -1
                fill(results[1][i], results[1][i] + 15, 0);
                break;
            }
        }
    }

    // testing for INSERT operations
    for (int i = 0; i < STRUCTURES; i++) {
        int ind_v = data_vector.size() / 2;
        int ind_l = data_list.size() / 2;
        switch(i) {
            case 0: {  // insert into a vector
                for(int j = 0; j < SUM; j++){
                    auto start = chrono::high_resolution_clock::now();
                    data_vector.insert(data_vector.begin() + ind_v, "TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][i][j] = duration.count();
                }
                break;
            }
            case 1: {  // insert into a list
                for(int j = 0; j < SUM; j++){
                    auto start = chrono::high_resolution_clock::now();
                    auto it = data_list.begin();
                    advance(it, ind_l);
                    data_list.insert(it, "TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][i][j] = duration.count();
                }
                break;
            }
            case 2: {  // insert into a set
                for(int j = 0; j < SUM; j++){
                    auto start = chrono::high_resolution_clock::now();
                    data_set.insert("TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][i][j] = duration.count();
                }
                break;
            }
        }
    }

    // testing for DELETE operations
    for (int i = 0; i < STRUCTURES; i++) {
        // select a target value in the vector 
        int ind = data_vector.size() / 2;
        string target_v = data_vector[ind];

        // select a target value in the list
        auto it1 = data_list.begin();
        advance(it1, ind);
        string target_l = *it1;

        // select a target value in the set
        auto it2 = data_set.begin();
        advance(it2, ind);
        string target_s = *it2;
        
        switch(i) {
            case 0: {  // delete by value from vector
                for(int j = 0; j < SUM; j++){
                    auto start = chrono::high_resolution_clock::now();
                    data_vector.erase(remove(data_vector.begin(), data_vector.end(), target_v));
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][i][j] = duration.count();
                }
                break;
            }
            case 1: {  // delete by value from list
                for(int j = 0; j < SUM; j++){
                    auto start = chrono::high_resolution_clock::now();
                    data_list.remove(target_l);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][i][j] = duration.count();
                }
                break;
            }
            case 2: {  // delete by value from set
                for(int j = 0; j < SUM; j++){
                    auto start = chrono::high_resolution_clock::now();
                    data_set.erase(target_s);    
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][i][j] = duration.count();
                }
                break;
            }
        }
    }

    string labels[] = {"Read", "Sort", "Insert", "Delete"};
    cout << setw(W1) << "Operation" << setw(W1) << "Vector" << setw(W1) << "List"
         << setw(W1) << "Set" << endl;
    for (int i = 0; i < 4; i++) {
        cout << setw(W1) << labels[i];
        for (int j = 0; j < COLS; j++) {
            int time = accumulate(results[i][j], results[i][j] + 15, 0)/15;
            cout << setw(W1) << time;
        }
        cout << endl;
    }
    

    return 0;
}