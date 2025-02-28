//
// Created by reini on 2/28/2025.
//

#ifndef TEXTMATCHINGTEST_TOKENBASEDMATCHING_H
#define TEXTMATCHINGTEST_TOKENBASEDMATCHING_H


#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

struct Match {
    std::string sourceEntity;
    std::map<std::string, std::vector<std::string>> tokenResultEntityMap;
};

class TokenBasedMatching {

    std::vector<std::string> companyList;
    std::vector<std::string> sanctionedList;
    std::map<std::string, std::vector<int>> tokenSanctionedListMap;

    std::string cleanup(std::string input) {
        std::string result;
        for(char c : input) {
            if(std::isalnum(c) || c == ' ') {
                if(c >= 'A' && c <= 'Z') {
                    result.push_back(' ');
                }
                result.push_back(c);
            }
            // Add whitespace if letter is capital
        }

        return result;
    }

public:
    std::vector<std::string> tokenize(std::string input) {
        std::string clean = cleanup(input);
        std::vector<std::string> result;
        std::istringstream stream(clean);
        std::string literal;

        while(stream >> literal) {
            result.push_back(literal);
        }
        return result;
    }

    void loadSanctionsList(std::vector<std::string> entities) {
        for(auto entity : entities) {
            sanctionedList.push_back(entity);
            int idx = sanctionedList.size()-1;
            auto tokens = tokenize(entity);

            for(auto token : tokens) {
                if(!tokenSanctionedListMap.contains(token)) {
                    tokenSanctionedListMap.insert({token, {}});
                }
                tokenSanctionedListMap.find(token)->second.push_back(idx);
            }
        }
        std::cout << "done";
    }

    std::vector<Match*> loadTargetEntities(std::vector<std::string> entities) {
        std::vector<Match*> matches;

        for(auto entity : entities) {
            companyList.push_back(entity);
            int idx = companyList.size()-1;
            auto tokens = tokenize(entity);

            for(auto token : tokens) {
                if(token.size() == 1) {
                    continue;
                }
                if(tokenSanctionedListMap.contains(token)) {
                    auto matchedToken = *tokenSanctionedListMap.find(token);
                    Match *match = new Match();
                    match->sourceEntity = entity;
                    for(auto matchedEntity : matchedToken.second) {
                        match->tokenResultEntityMap[matchedToken.first].push_back(sanctionedList[matchedEntity]);
                    }
                    matches.push_back(match);
                }
            }
        }

        return matches;
    }

    void printMatches(std::vector<Match*> matches) {
        for(auto m : matches) {
            std::cout << m->sourceEntity << ";";
            std::string matchedEntities = "";
            for(auto token : m->tokenResultEntityMap) {
                matchedEntities.append("Token: ").append(token.first).append("\t{");
                for(auto me : token.second) {
                    matchedEntities.append(me).append(",");
                }
                matchedEntities.append("}");
            }
            std::cout << matchedEntities << std::endl;
        }
    }
};


#endif //TEXTMATCHINGTEST_TOKENBASEDMATCHING_H
