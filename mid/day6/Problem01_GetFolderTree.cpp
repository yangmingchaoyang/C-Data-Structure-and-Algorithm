/*
给你一个字符串类型的数组arr，譬如：
String[] arr = { "b\\cst", "d\\", "a\\d\\e", "a\\b\\c" };
你把这些路径中蕴含的目录结构给画出来，子目录直接列在父目录下面，并比父目录
向右进两格，就像这样:
a
  b
    c
  d
    e
b
  cst
d
同一级的需要按字母顺序排列，不能乱。
*/
#include<iostream>
#include<string>
#include<map>
#include<vector>

class Node{
public:
    std::string name;
    std::map<std::string,Node*>nextMap;

    Node(std::string _name):name(_name){}
};

void releaseTreeMemory(Node* node){
    if(node==nullptr){
        return;
    }
    for(auto& pair:node->nextMap){
        releaseTreeMemory(pair.second);
    }
    delete node;
    node=nullptr;
}

std::string get2nSpace(int n){
    std::string res="";
    for(int i=1;i<n;i++){
        res+=" ";
    }
    return res;
}

void printProcess(Node* head,int level){
    if(level!=0){
        std::cout<<get2nSpace(level)<<head->name<<std::endl;
    }
    for(const auto& entry:head->nextMap){
        printProcess(entry.second,level+1);
    }
}

Node* generateFolderTree(const std::vector<std::string>& folderPaths){
    Node* head=new Node("");
    for(const std::string& fpldPath:folderPaths){
        std::vector<std::string>paths;
        int start=0;
        int end=fpldPath.find("\\");
        Node* cur=head;

        while(end!=std::string::npos){
            std::string path=fpldPath.substr(start,end-start);
            paths.push_back(path);
            start=end+1;
            end=fpldPath.find("\\",start);
        }
        std::string lastPath=fpldPath.substr(start);
        paths.push_back(lastPath);

        for(const std::string& path:paths){
            if(cur->nextMap.find(path)==cur->nextMap.end()){
                cur->nextMap[path]=new Node(path);
            }
            cur=cur->nextMap[path];
        }
    }
    return head;
}

void print(const std::vector<std::string>&folderPaths){
    if(folderPaths.empty()){
        return;
    }
    Node* head=generateFolderTree(folderPaths);
    printProcess(head,0);
    releaseTreeMemory(head);
}


int main() {
    std::vector<std::string> arr = { "b\\cst", "d\\", "a\\d\\e", "a\\b\\c" };
    print(arr);
    return 0;
}



