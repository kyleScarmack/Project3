
#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <stack>
#include <utility>

#define BLACK nullptr

// Namespace For Project.
namespace DSA
{
    // Map Class That Uses A Red-Black Tree Implementation.
    template<typename Key_T, typename Value_T>
    class Map {
    private:
        // Node Struct For Red-Black Tree.
        struct Node {
            // Colors for Red-Black Tree Node.
            enum Color {
                Black, Red
            };

            // Key Storage.
            Key_T key;
            // Value Storage.
            Value_T value;
            // Helper Storage For Iterator Class.
            std::pair<Key_T, Value_T> itHelper;
            // Pointer To The Parent Node.
            Node* parent;
            // Pointer To The Left Child.
            Node* left;
            // Pointer To The Right Child.
            Node* right;
            // Color Of The Node.
            Color color;

            // Constructor For Node.
            Node(Key_T k, Value_T v);

            // Determines If A Node Is Black.
            bool isBlack() const noexcept;
            // Determines If A Node Is Red.
            bool isRed() const noexcept;

            // Returns The Grandparent Node.
            Node* getGrandparent();
            // Returns The Uncle Node.
            Node* getUncle();
        };

    private:
        // Root Of The Red-Black Tree.
        Node* root;
        // Number Of Nodes In Red-Black Tree.
        size_t nodeCount;

    private:
        // Helper Function For Destructor; Aids In Post-Order Traversal.
        void DestructorHelper(Node *node);
        // Helper Function That Searches For And Returns The Node Of A Given Key.
        Node* FindHelper(Node*& node, const Key_T& key);
        // Helper Function For Insert Function.
        void InsertHelper(Node*& nodeRoot, Node*& node, Node* parent);
        // Performs A Left Rotation Around A Particular Node.
        void RotateLeft(Node* node);
        // Performs A Right Rotation Around A Particular Node.
        void RotateRight(Node *node);
        /*
         * Performs Necessary Rotations To Maintain Red-Black Tree Properties.
         * Takes Inspiration From Pseudocode Found In Module 5 Video:
         * "Red-Black Tree Insertions, Performance, and Use Cases" (12:12 - 13:20)
         */
        void Balance(Node* node);
        // Helper Function
        void PrintHelper(Node *node) const;

    public:
        // Constructor For Map Class.
        Map();
        // Destructor For Map Class.
        ~Map();

        // Method That Deletes All Nodes.
        void clear();
        // Method That Determines If The Red-Black Tree Is Empty.
        bool isEmpty() const noexcept;
        // Method That Returns The Number Of Nodes In The Red-Black Tree.
        size_t size() const noexcept;
        // Method That Returns The Number Of Nodes Of A Particular Key; Can Either Be 1 Or 0.
        size_t count(const Key_T& key) const;
        // Method That Inserts A Key-Value Pair Into The Map.
        void insert(const Key_T& key, const Value_T& value);
        // Method That Returns The Value Of A Particular Key In The Map. Throws An Exception If Key Does Not Exist.
        Value_T& at(const Key_T& key);
        // Method That Prints The Nodes Of The Red-Black Tree InOrder.
        void printInOrder() const;

    public:
        // Iterator Class For Iterating Over The Red-Black Tree.
        class Iterator
        {
        private:
            // Current Node That The Iterator Is At.
            Node* currentNode;
            // Helper Stack For Depth-First Search.
            std::stack<Node*> nodes;

        private:
            // Sets The Current Node To The Red-Black Tree's Leftmost Node.
            void getLeftNode(Node* node);
            // Sets The Current Node To The Red-Black Tree's Rightmost Node.
            void getRightNode();

        public:
            // Default Constructor For Iterator Class.
            Iterator();
            // Parameterized Constructor For Iterator Class.
            explicit Iterator(Node* node);

            // Operator Overload For The De-referencing Operator.
            std::pair<Key_T, Value_T>& operator*() const;
            // Operator Overload For The Arrow Operator.
            std::pair<Key_T, Value_T>* operator->() const;

            // Operator Overload For The Pre-Increment Operator.
            Iterator& operator++();

            // Operator Overload For The Equal-To Operator.
            bool operator==(const Iterator& other) const;
            // Operator Overload For Not-Equal-To Operator.
            bool operator!=(const Iterator& other) const;
        };

        // Method That Returns An Iterator To A Node With A Particular Key.
        Iterator find(const Key_T& key);
        // Method That Returns An Iterator To The Front Of The Red-Black Tree.
        Iterator begin();
        // Method That Returns An Iterator To The End Of The Red-Black Tree.
        Iterator end();
    };
}

#endif // MAP_HPP
