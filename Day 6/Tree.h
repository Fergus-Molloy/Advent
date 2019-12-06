#ifndef ORBIT_D
#define ORBIT_D

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
}
#endif