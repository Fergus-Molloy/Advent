#ifndef ORBIT_D
#define ORBIT_D

template <class Type> class Node{
public:
    Type data;
    std::vector<Node<Type>> children;
};

template <class Type> class Tree{
public:
    Tree();

    void addNode(Type data, Type parent);

    Node<Type> getParent(Type search);

    std::vector<Node<Type>> getChildren(Type search);

    Node<Type> search(Type item);


private:
    Node<Type> root;
}
#endif