//
//  main.cpp
//  LevenshteinDistance
//
//  Created by adeeb mohammed on 01/03/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
// program for

// time complexity of o(m*n)
// space complexoty is o(m*n)

#include <iostream>
#include <vector>


void printVector(std::vector<std::vector<int>> &vec,
                 int m,
                 int n){
    std::cout<<std::endl;
    for (int i= 0; i < m; i++) {
        for (int j = 0 ; j < n; j++) {
            std::cout <<  vec[i][j] <<  "  ";
        }
        std::cout<< std::endl;
    }
    std::cout<<std::endl;
}


int levenshteinDistanceOld(std::string str1, std::string str2) {
    std::vector< std::vector<int> > edits(str2.length()+1,
                                        std::vector<int>(str1.length()+1,0));
    for (int i = 0; i < str2.length()+1; i++) {
        for (int j = 0; j < str1.length()+1; j++) {
            edits[i][j] = j;
        }
        edits[i][0] = i;
    }
    
    for (int i = 1; i < str2.length()+1; i++) {
        for (int j = 1; j < str1.length()+1; j++) {
            if (str2[i-1] == str1[j-1]) {
                edits[i][j] = edits[i-1][j-1];
            }else{
                edits[i][j] = 1 + std::min(edits[i-1][j-1],std::min(edits[i-1][j],edits[i][j-1]));
            }
        }
    }
    
    return edits[str2.length()][str1.length()];
}


int levenshteinDistance(std::string str1, std::string str2){
    
    std::string big = str1.length() >= str2.length()? str1 : str2;
    std::string small = str2.length() > str1.length()? str1: str2;
    
    
    
    std::vector<int> evenEdits(small.length()+1);
    std::vector<int> oddEdits(small.length()+1);
    
    for (int i = 0; i < small.length() + 1;  i++) {
        evenEdits[i] = i;
    }
    
    std::vector<int> *currentEdits;
    std::vector<int> *previousEdits;
    
    for (int i = 1;i <  big.length()+1; i++) {
        if (i % 2 == 1) {
            currentEdits = &oddEdits;
            previousEdits = &evenEdits;
        }else{
            currentEdits = &evenEdits;
            previousEdits = &oddEdits;
        }
        (*currentEdits)[0] = i;
        // filling the no of edits
        for(int j = 1; j < small.length() + 1; j++ ){
            if(big[i-1] == small[j-1]){
                
              (*currentEdits)[j] = previousEdits->at(j-1);
          //      std::cout << big[i-1] << " ";
            }else{
                (*currentEdits)[j] = 1 + std::min(
                                previousEdits->at(j-1),
                                std::min(previousEdits->at(j),currentEdits->at(j-1))
                                );
            }
           // std::cout << currentEdits->at(j) << " ";
        }
        //std::cout << std::endl;
    }
    return (big.length() % 2 == 0)?evenEdits.at(small.length()) : oddEdits.at(small.length());
}

int main(int argc, const char * argv[]) {
    std::cout << "Function for obtaining minimum no of edit operations to get the second string" << std::endl;
    auto result = levenshteinDistance("abc", "abcx");
    std::cout << "Result=" << result << std::endl;
    return 0;
}
