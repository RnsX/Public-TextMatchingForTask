//
// Created by reini on 2/28/2025.
//

#ifndef TEXTMATCHINGTEST_CLASSICFUZZYMATCHING_H
#define TEXTMATCHINGTEST_CLASSICFUZZYMATCHING_H


#include <string>
#include <algorithm>
#include <iostream>

class ClassicFuzzyMatching {

public:
    int levenDistance(std::string wordA, std::string wordB) {
        int lenA = wordA.length();
        int lenB = wordB.length();

        int matrix [lenA+1][lenB+1];

        for(int i = 0; i <= lenA; i++) {
            matrix[i][0] = i;
        }

        for(int i = 0; i <= lenB; i++) {
            matrix[0][i] = i;
        }

// The problematic part O(x*y) complexity i mentioned
        for(int i = 1; i < lenA; i++) {
            for(int j = 1; j <= lenB; j++) {
                bool match = wordA[i-1] == wordB[j-1];
                int cost = match ? 0 : 1;

// Compute minimum number of operations needed
                int deletion = matrix[i-1][j]+1;
                int insertion = matrix[i][j-1] +1;
                int substitution = matrix[i-1][j-1] + cost;

                int minimum_cost = deletion;
                (insertion < minimum_cost) ? minimum_cost = insertion : minimum_cost = minimum_cost;
                (substitution < minimum_cost) ? minimum_cost = substitution : minimum_cost = minimum_cost;

                matrix[i][j] = minimum_cost;
            }
        }

// Print matrix with comma delimited values
//        for(int i = 0; i < lenA; i++) {
//            for(int j = 0; j < lenB; j++) {
//                std::cout << matrix[i][j] << ',';
//            }
//            std::cout << '\n';
//        }

        return matrix[lenA-1][lenB-1];
    }
};


#endif //TEXTMATCHINGTEST_CLASSICFUZZYMATCHING_H
