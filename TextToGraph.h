#ifndef TEXTTOGRAPH_H
#define TEXTTOGRAPH_H

#include <string>
#include <vector>
#include <map>
#include "Graph.h"

class TextToGraph {
private:
    std::string text;
    std::map<std::string, int> wordToId;
    std::vector<std::string> idToWord; 
    Graph* graph;

public:
    TextToGraph(const std::string& inputText);
    ~TextToGraph();

    void constructGraph();
    void printGraph();

    
    //  QUESTIONS
    void customBFS(const std::string& startNode);
    bool isReachableWithMaxVersion(const std::string& source, const std::string& destination, int maxVersion);
    void printConnectedComponentsWithMaxVersion(int maxVersion);
};

#endif