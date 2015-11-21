#include <bits/stdc++.h>
#include "Element.h"
template <class T> class Population{
    public:
    int size;
    int mutation_size;
    std::vector<T*> elements;
    Population(){
        mutation_size = 5;
        srand(time(NULL));
    }
    ~Population(){
        for(int i=0;i<elements.size();i++){
            delete(elements[i]);
        }
    }
    void initPopulation(std::vector<T*>& _e){
        elements = std::vector<T*>(_e); 
    }
    void setSize(int s){
        size = s;
    }
    void sortElements(){
        std::sort(elements.begin(),elements.end(),compare);
    }
    T* getBest(){
        return elements[0];
    }
    void populate(){
        for(int i=0;i<size;i++){
            int a = rand() % size;
            int b;
            while((b=rand()%size)==a);
            elements.push_back(elements[a]->cross(*elements[b]));
        }
    }
    void eliminateWeakest(){
        typename std::vector<T*>::iterator it = elements.begin();
        for(int i=0;i<size;i++) it++;
        while(it != elements.end()){
            delete * it;
            elements.erase(it);
        }
    }
    void mutatePopulation(){
        for(int i=0;i<(size/100)*mutation_size;i++){
            int a = rand() % size;
            elements[a]->mutate();
        }
    }
    void makeNGenerations(int n){
        for(int i=0;i<n;i++)
            makeGeneration();
    }
    void makeGeneration(){
        populate();
        sortElements();
        eliminateWeakest();
        mutatePopulation();
    }
};
