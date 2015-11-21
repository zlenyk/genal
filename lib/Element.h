#include <bits/stdc++.h>
class Element{
    public:
    virtual ~Element(){}
    virtual Element* cross(const Element& a){
        return new Element(a);
    }
    virtual void mutate(){};
    virtual int value()const{
        return 0;
    } 
};
bool compare(const Element* a,const Element* b){
    return a->value() > b->value();
}
