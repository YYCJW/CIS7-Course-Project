/* A solar marketing specialist travels from Riverside to Moreno Valley, 
 * then to Perris and Hemet to market solar packages to homeowners. The 
 * travel route is shown below:
 * If the marketing specialist begins the trip from home in Riverside, 
 * determine the variations of the trip to the noted cities that he must take 
 * to market the solar products. 
 * 2. Determine shortest path, and the most low-cost trips for the marketing specialist.
 * 3. Create a C++ program to provide the representation of the trips, low-cost 
 * and shortest paths, including matrices, adjacencies.
 * 4. Provide documentation that explains solution and programming approaches. 
 */

/* 
 * File:   Inland Empire Solar Sales Travel.cpp
 * Author: Yan
 *
 * Created on May 23, 2022, 10:17 AM
 */

#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//Data structure to store the sites and total miles in a path
struct PossiblePaths{
    string city1, city2, city3, city4, destination;
    int range; 
};

//Data structure to store graph edges and weight
struct Edge {
    string src, dest;
    int weight;
};

//compare the first column of the 2D vector from the second row to the fourth row
bool compareInterval(string T1, string T2)
{
    return (T1 < T2);
}

//print possible paths
void printPossiblePaths(vector<PossiblePaths> &vectorOfPaths, int size){
    for(int i=0; i<vectorOfPaths.size(); i++){
        cout << vectorOfPaths[i].city1 << " -> " << vectorOfPaths[i].city2 << " -> " << vectorOfPaths[i].city3 << " -> " <<
                vectorOfPaths[i].city4 << " -> " << vectorOfPaths[i].destination << endl;
        cout << "Route " << i+1 << " mills : " << vectorOfPaths[i].range << "\n" << endl;           
    }
}

//print the shortest path
void printShortestPath(vector<PossiblePaths> &vectorOfPaths, int size){
    //check if there is the other shortest path
    int min; //index of the minimum element
    for (int i=1; i<size; i++){
        if(vectorOfPaths[0].range == vectorOfPaths[i].range)
            min = i;
    }
    
    //print the shortest path
    cout << "\nThe shortest path is: \n";
    cout << vectorOfPaths[0].city1 << " -> " << vectorOfPaths[0].city2 << " -> " << vectorOfPaths[0].city3 << " -> " <<
                vectorOfPaths[0].city4 << " -> " << vectorOfPaths[0].destination << "\nThe distance is " <<
                vectorOfPaths[0].range << endl;
    cout << "Or\n";
    cout << vectorOfPaths[min].city1 << " -> " << vectorOfPaths[min].city2 << " -> " << vectorOfPaths[min].city3 << " -> " <<
                vectorOfPaths[min].city4 << " -> " << vectorOfPaths[min].destination << "\nThe distance is " <<
                vectorOfPaths[min].range << "\n" << endl;
}

//print the lowest_cost path
void printLowestCostPath(vector<PossiblePaths> &vectorOfPaths, int size){    
    //check if there is the other shortest path
    int min; //index of the minimum element
    for (int i=1; i<size; i++){
        if(vectorOfPaths[0].range == vectorOfPaths[i].range)
            min = i;
    }
    
    //print the lowest_cost path
    cout << "\nThe Lowest_cost path is: \n";
    cout << vectorOfPaths[0].city1 << " -> " << vectorOfPaths[0].city2 << " -> " << vectorOfPaths[0].city3 << " -> " <<
                vectorOfPaths[0].city4 << " -> " << vectorOfPaths[0].destination << "\nThe distance is " <<
                vectorOfPaths[0].range << endl;
    cout << "Or\n";
    cout << vectorOfPaths[min].city1 << " -> " << vectorOfPaths[min].city2 << " -> " << vectorOfPaths[min].city3 << " -> " <<
                vectorOfPaths[min].city4 << " -> " << vectorOfPaths[min].destination << "\nThe distance is " <<
                vectorOfPaths[min].range << "\n" << endl;
}

//print the lowest cost path
void printLongestPath(vector<PossiblePaths> &vectorOfPaths, int size){   
    int k=size-1;
    //check if there is the other longest path
    int max; //index of the maximum element
    for (int i=0; i<k; i++){
        if(vectorOfPaths[k].range == vectorOfPaths[i].range)
            max = i;
    }
    
    //print the longest path
    cout << "\nThe Lowest_cost path is: \n";
    cout << vectorOfPaths[k].city1 << " -> " << vectorOfPaths[k].city2 << " -> " << vectorOfPaths[k].city3 << " -> " <<
                vectorOfPaths[k].city4 << " -> " << vectorOfPaths[k].destination << "\nThe distance is " <<
                vectorOfPaths[k].range << endl;
    cout << "Or\n";
    cout << vectorOfPaths[max].city1 << " -> " << vectorOfPaths[max].city2 << " -> " << vectorOfPaths[max].city3 << " -> " <<
                vectorOfPaths[max].city4 << " -> " << vectorOfPaths[max].destination << "\nThe distance is " <<
                vectorOfPaths[max].range << "\n" << endl;
}

int main()
{
    vector<string> trips = {"Moreno Valley", "Perris", "Hemet" }; //cities will be visited
   
    Edge edges[] = {
        {"Riverside", "Hemet", 33},
        {"Riverside", "Perris", 24},
        {"Riverside", "Moreno Valley", 16},
        {"Hemet", "Moreno Valley", 26},
        {"Perris", "Hemet", 30},
        {"Perris", "Moreno Valley", 18}        
    };
    
    int n = trips.size(); //number of vertices that will be visited except for the start city and destination
    int m = sizeof(edges) / sizeof(edges[0]); //number of edges
    
    int j=0; //index 
    PossiblePaths path; //create structure
    vector<string> cityTrips; //vector of passing cities
    vector<PossiblePaths> vectorOfPaths; //vector of structure(PossiblePaths)

    sort(trips.begin(), trips.end(), compareInterval); //sort the string vector in an ascending order

    //permute paths
    do{
        int distance=0; //total mill in a route            
        for(int i=0; i<n; i++){
            cityTrips.push_back(trips[i]); //adding the passing cities in the vector        

        }
        cout << "Riverside ";
        path.city1 = "Riverside"; //initialize the first element of the structure
        path.destination = "Riverside";
        path.city2 = cityTrips[0]; 
        path.city3 = cityTrips[1];
        path.city4 = cityTrips[2];
        
        //calculate the total mills in the path
        for(int k=0; k<m; k++){
            if(edges[k].src == "Riverside" && path.city2==edges[k].dest){
                distance += edges[k].weight;
            }
        
            if((path.city2 == edges[k].src && path.city3==edges[k].dest)
                    || (path.city3==edges[k].src && path.city2==edges[k].dest)){
                distance += edges[k].weight;
            }

            if((path.city3==edges[k].src && path.city4==edges[k].dest)
                    || (path.city4==edges[k].src && path.city3==edges[k].dest)){
                distance += edges[k].weight;   
            }

            if(edges[k].src == "Riverside" && path.city4 ==edges[k].dest ){
                distance += edges[k].weight;
            }
        }       
        
        path.range=distance;       
        vectorOfPaths.push_back(path);
        cityTrips.clear();
        path={};
        j++;          
    }while(next_permutation(trips.begin(), trips.end()));
    
    //sort the vector of structure PossiblePaths by comparing the range in an ascending order
    sort(vectorOfPaths.begin(), vectorOfPaths.end(), [](PossiblePaths path1, PossiblePaths path2){
        return path1.range < path2.range;
    }
    );
    
    while(true){
        int choice; // user choice
        cout << "Inland Empire Search market maps:" << endl;
        cout << "1. Possible paths: " << endl;
        cout << "2. Shortest path: " << endl;
        cout << "3. Lowest_cost path: " << endl;
        cout << "4. Longest path: " << endl;
        cout << "5. exit" << endl;
        cin >> choice;
    
        if(choice == 1)
            printPossiblePaths(vectorOfPaths, j);
        
        else if(choice == 2)
            printShortestPath(vectorOfPaths, j);
            
        else if(choice == 3)
            printLowestCostPath(vectorOfPaths, j);
            
        else if(choice == 4)
            printLongestPath(vectorOfPaths, j);
    
        else if(choice == 5)
            exit(0);
    
        else{
            cout << "The option you have chosen does not exist, please select another option 1-5." << endl;
            cin >> choice;
        }
    }
    return 0;
}