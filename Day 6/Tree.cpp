#include <iostream>
#include <vector>
#include "../general.h"
#include "Tree.h"

template <class Type> class Node{
public:
    Type data;
    std::vector<Node<Type>> children;

    Node(Type data);
};

template <class Type> class Tree{
public:
    Tree();

    Tree(Type data);

    void addNode(Type data, Type parent);

    Node<Type> getParent(Type search);

    std::vector<Node<Type>> getChildren(Type search);

    Node<Type> search(Type item);

    void setRoot(Type data);

    Node<Type> root;
};

template<class Type>
Node<Type>::Node(Type data){
    this->data=data;
}

template<class Type>
void Tree<Type>::setRoot(Type data){
    Node rootNode(data);
    root = rootNode;
}

template<class Type>
Tree<Type>::Tree(Type data){
    setRoot(data);
}

int main(){
    std::string name = "COM";
    Tree<int> tree(name);
    

    return 0;
}