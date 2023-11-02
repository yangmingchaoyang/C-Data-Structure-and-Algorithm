#include <iostream>
using namespace std;
class CBase
{
public:
    CBase(){
        p=this;
        cout<<"construct!!!"<<endl;
    }
    ~CBase(){
        if(p!=nullptr){
            delete p;
            p=nullptr;
        }
        cout<<"destruction!!!"<<endl;
    }

    CBase* p;
};


int main(){
    CBase* p=new CBase;
    delete p;
}








