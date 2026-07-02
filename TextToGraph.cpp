#include "TextToGraph.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

TextToGraph::TextToGraph(const std::string& inputText) {
    text = inputText;
    graph = NULL;
}

TextToGraph::~TextToGraph() {
    delete graph;
}


void TextToGraph::constructGraph() {
    int level = 0; 
    std::string current_word = "";

    std::vector< std::vector< std::string> > words;
    std::vector<std::string> empty_vector;
    words.push_back(empty_vector);

    for(int i = 0; i < (int) text.size(); i++)
    {
        char ch = text[i];

        if( (ch == ' ' || ch == '.')  && current_word.size() != 0)
        {
            if(wordToId.find(current_word) == wordToId.end())
            {
                idToWord.push_back(current_word);
                wordToId[current_word] = (int)idToWord.size() - 1;

            }
            words.back().push_back(current_word);
            current_word = "";
        }

        if(ch == '.')
        {
            level++;
            words.push_back(empty_vector);
        }

        if(ch != '.' && ch != ' ')
        {
            current_word.push_back(text[i]);
        }
    }

    graph = new Graph((int)idToWord.size());

    for(int i = 0; i < level; i++)
    {
        for(int j = 0; j < (int)words[i].size(); j++)
        {
            for(int k = 0; k < (int)words[i].size(); k++)
            {
                if(j == k)
                    continue;
                int dst = j-k;
                if(dst < 0)
                    dst *= -1;
                if (wordToId[words[i][j]] != wordToId[words[i][k]])
                {
                    graph -> addEdge(wordToId[words[i][j]],wordToId[words[i][k]],i,dst);
                }
            }
        }
    }

}

void TextToGraph::printGraph()
{
    for(std::map<std::string, int>::iterator it = wordToId.begin(); it != wordToId.end(); it++)
    {
        std::string word = it -> first;
        int id = it -> second;
        std::cout<<word<<": ";
        std::vector<Edge> neighbors = graph -> getNeighbors(id);
        std::vector<std::pair< std::string, Edge> > helperEdge;
        for(std::vector<Edge>::iterator itEdge = neighbors.begin(); itEdge != neighbors.end(); itEdge++)
            helperEdge.push_back(std::make_pair(idToWord[itEdge->toNodeId],*itEdge));
        std::sort(helperEdge.begin(), helperEdge.end());
        for(std::vector<std::pair<std::string, Edge> >::iterator itEdge = helperEdge.begin(); itEdge != helperEdge.end(); itEdge++)
        {
            std::cout<< idToWord[itEdge -> second.toNodeId];
            std::cout<<"(v:"<<(itEdge ->second. version)<<",";
            std::cout<<"d:"<<(itEdge -> second.distance)<<") ";
        }
        std::cout<<std::endl;
    }
}




void TextToGraph::customBFS(const std::string& startNode) {
    if (wordToId.find(startNode)==wordToId.end()) return;
    int start=wordToId.find(startNode)->second;
    std::vector<bool> visited(graph->getNumNodes(),false);
    std::queue<int> q;
    q.push(start);
    visited[start]=true;
    while (!q.empty()){
        int curr=q.front();
        q.pop();
        std::cout<<idToWord[curr]<<" ";
        std::vector<Edge> neighbors=graph->getNeighbors(curr);
        std::vector<std::pair<Edge,std::string>> items;
        for (size_t j=0;j<neighbors.size();j++){
            items.push_back(std::make_pair(neighbors[j],idToWord[neighbors[j].toNodeId]));
        }
        std::sort(items.begin(),items.end());
        for (size_t i=0;i<items.size();i++){
            if (!visited[wordToId[items[i].second]]){
                q.push(wordToId[items[i].second]);
                visited[wordToId[items[i].second]]=true;
            }
        }
    }
    std::cout<<std::endl;
}


void TextToGraph::printConnectedComponentsWithMaxVersion(int maxVersion) {
    std::vector<std::vector<std::string>> components;
    std::vector<std::string> current_component;
    std::vector<bool> visited(graph->getNumNodes(),false);
    for (int i=0;i<graph->getNumNodes();i++){
        if (!visited[i]){
            std::queue<int> q;
            q.push(i);
            visited[i]=true;
                while (!q.empty()){
                    int curr=q.front();
                    q.pop();
                    current_component.push_back(idToWord[curr]);
                    std::vector<Edge> neighbors=graph->getNeighbors(curr);
                    for (size_t i=0;i<neighbors.size();i++){
                        if (!visited[neighbors[i].toNodeId] && neighbors[i].version<maxVersion){
                            q.push(neighbors[i].toNodeId);
                            visited[neighbors[i].toNodeId]=true;
                    }
                }
            }
            std::sort(current_component.begin(),current_component.end());
            components.push_back(current_component);
            current_component.clear();
        }
    }
    std::sort(components.begin(),components.end());
    for (size_t i=0;i<components.size();i++){
        std::cout<<"Component "<<i+1<<": ";
        for (size_t j=0;j<components[i].size();j++){
            std::cout<<components[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

// Q3
bool TextToGraph::isReachableWithMaxVersion(const std::string& source, const std::string& destination,int maxVersion) {
    if (wordToId.find(source)==wordToId.end() || wordToId.find(destination)==wordToId.end()) return false;
    if (wordToId.find(source)->second==wordToId.find(destination)->second) return true;
    int start=wordToId.find(source)->second;
    int last=wordToId.find(destination)->second;
    std::vector<bool> visited(graph->getNumNodes(),false);
    std::queue<int> q;
    q.push(start);
    visited[start]=true;
    while (!q.empty()){
        int curr=q.front();
        q.pop();
        if (curr==last) return true;
        std::vector<Edge> neighbors=graph->getNeighbors(curr);
        for (size_t i=0;i<neighbors.size();i++){
            if (!visited[neighbors[i].toNodeId] && neighbors[i].version<maxVersion){
                q.push(neighbors[i].toNodeId);
                visited[neighbors[i].toNodeId]=true;
            }
        }
    }
    
    
    
    
    
    return false;
                                        
    
}