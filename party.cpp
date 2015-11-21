#include <bits/stdc++.h>
#include "lib/genal.h"
using namespace std;
#define PS 16
#define POPULATION_SIZE 500
#define GENERATION_COUNT 10000
#define FOR(i,n) for(int i=0;i<n;i++)

int likes[PS][PS],importance[PS];
string names[PS];
class Sequence : public Element{
    public:
    int seq[PS];
    Sequence(){}
    Sequence(int s[PS]){
        FOR(i,PS){
            seq[i] = s[i];
        }
    }
    int getIndex(int val)const{
        FOR(i,PS) if(seq[i]==val) return i;
        return -1;
    }
    void mutate(){
        FOR(i,5){
        int a = rand() % PS;
        int b;
        while((b=rand()%PS)==a);
        swap(seq[a],seq[b]);
        }
    }
    Sequence* cross(const Sequence& a) const{
        int s[PS];
        vector<vector<int> >V; 
        for(int i=0;i<PS;){
            vector<int> v;
            int j = a.getIndex(seq[i]);
            assert(j>-1);
            while(a.seq[j%PS] == seq[i%PS]){
                v.push_back(seq[i%PS]);
                i++;
                j++;
                if(v.size() == PS) break;
            }
            V.push_back(v);
            if(i>PS) V.erase(V.begin());
        }
        random_shuffle(V.begin(),V.end());
        int newInd = 0;
        set<int> S;
        FOR(i,V.size()){
            vector<int> v = V[i];
            FOR(j,v.size()){
                s[newInd++] = v[j];
                S.insert(v[j]);
            }
        }
        Sequence* newS = new Sequence(s);
        assert(S.size() == PS);
        assert(newInd == PS);
 
        return newS;
    }
    int value() const{
        int sum = 0;
        FOR(i,PS){
            int j = (i+1)%PS;
            sum += likes[seq[i]][seq[j]]*importance[seq[i]] +
                    likes[seq[j]][seq[i]]*importance[seq[j]];
        }
        return sum;
    }
    void print() const{
        FOR(i,PS){
            cout << seq[i] <<" ";
        }
        cout << endl;
    }
};
Sequence* randomSequence(){
    int s[PS];
    FOR(i,PS) s[i] = i;
    random_shuffle(s,s+PS);
    return new Sequence(s);
}

int main(){
    srand(time(NULL));
    FOR(i,PS){
        string name;
        cin >> names[i];
        FOR(j,PS)
            cin >> likes[i][j];
        cin >> importance[i];
    }
    Population<Sequence>* p = createPopulation<Sequence>();
    p->setSize(POPULATION_SIZE);
    vector<Sequence*> V;
    FOR(i,p->size)
        V.push_back(randomSequence());
    p->initPopulation(V); 
    FOR(i,GENERATION_COUNT){
        p->makeNGenerations(10);
        Sequence* best = p->getBest();
        cout << "GENERATION: " << i << " MAX VALUE: " << best->value() << endl;
    }
    FOR(i,PS){
        string name = names[p->getBest()->seq[i]];
        cout << name;
        if(i<PS-1) cout << " - ";
    }
    cout << endl;
    delete(p);
    return 0;
}
