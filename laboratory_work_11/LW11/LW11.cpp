#include <iostream>//libraries
#include <iomanip>
using namespace std;
//
struct Node {
    int key;
    char value[10];
    Node* left;
    Node* right;
};
//prototypes
Node* CreateNode(int key, char* value);
Node* Insert_Element(Node*& root, int key, char* value);
void print_tree(Node* node, int indent);
Node* search(Node* root, int key);
Node* DelNode(Node* root, int key);
void FreeTree(Node* root);
int count_even(Node* node);

void main()
{
    Node* root = nullptr;
    int indent = 0;
    Node* search_result;
    char choise;
    setlocale(LC_CTYPE, "Rus");
    do {
        cout << "1-Добавить элемент" << endl;
        cout << "2-Поиск по ключу" << endl;
        cout << "3-Вывод дерева" << endl;
        cout << "4-Удалить определенный элемент" << endl;
        cout << "5-Очистка всего дерева" << endl;
        cout << "6-Посчитать четные узлы" << endl;
        cout << "7-Выход" << endl;
        cin >> choise;
        while (!(choise >= '1' && choise <= '6')) {
            cout << "Неправильный вариант! Попробуйте еще раз: ";
            cin >> choise;
        }
        int choise_sw = choise - '0';//convert char to int
        switch (choise_sw) {
        case 1:int amm_of_elements;
            cout << "Введите колличетсво элементов: ";
            cin >> amm_of_elements;
            for (int i = 0; i < amm_of_elements; i++) {//cycle to insert all the required elements
                int key_temp;
                cout << "Введите ключ: ";
                cin >> key_temp;
                char value_temp[10];
                cout << "Введите значение: ";
                cin >> value_temp;
                root = Insert_Element(root, key_temp, value_temp);
            }
            break;
        case 2:int search_key;
            cout << "Введите ключ элемента, который вы хотите найти: ";
            cin >> search_key;
            search_result = search(root, search_key);//create a node for a result only
            if (search_result != nullptr) {
                cout << "Элемент найден! Это " << search_result->key << " " << search_result->value << endl;
            }
            else {
                cout << "Нет такого элемента" << endl;
            }
            break;
        case 3:
            print_tree(root, indent); break;
        case 4:int del_key;
            cout << "Введите ключ элемента, который нужно удалить:";
            cin >> del_key;
            DelNode(root, del_key); break;
        case 5:FreeTree(root); cout << "Дерево удалено" << endl;
            break;
        case 6:cout << "Количество узлов с четными ключами равно " << count_even(root) << endl;
            break;
        }


    } while (choise != '7');
}

Node* CreateNode(int key, char* value)//function that creates a node 
{
    Node* NewNode = new Node();//get memory for a new node
    if (!NewNode) {//if there is a memoy failure
        cout << "Memory Error!" << endl;
        return nullptr;
    }
    NewNode->key = key;
    for (int i = 0; i < 10; i++) {//cycle to insert an array of chars in a new node
        *((NewNode->value) + i) = *(value + i);
    }
    NewNode->left = NewNode->right = nullptr;//set all the branches to null
    return NewNode;
}
//Node* Insert_Element(Node*& root, int key, char* value)//function to insert previousl created element in the tree
//{
//    if (root == nullptr) {//if the tree is empty
//        root = CreateNode(key, value);
//    }
//    else {
//        if (key < root->key) {//sort values in two branches of BST based on the key value
//            Insert_Element(root->left, key, value);
//        }
//        else {
//            Insert_Element(root->right, key, value);
//        }
//    }
//    return root;
//}

Node* Insert_Element(Node*& root, int key, char* value) {
    if (root == nullptr) { // If the tree is empty
        root = CreateNode(key, value); // Create a new node and set it as the root
    }
    else {
        if (key < root->key) { // If the key is less than the root's key, go to the left subtree
            root->left = Insert_Element(root->left, key, value); // Assign result back to the left child
        }
        else { // If the key is greater than or equal to the root's key, go to the right subtree
            root->right = Insert_Element(root->right, key, value); // Assign result back to the right child
        }
    }
    return root;
}

void print_tree(Node* node, int indent)//function to print the whole BST
{
    if (node != nullptr) {//if there is something to print
        print_tree(node->right, indent + 4);
        cout << setw(indent) << node->key << " " << node->value << endl;
        print_tree(node->left, indent + 4);
    }
}
Node* search(Node* root, int key)//function to find a specific element by key
{
    if (root == nullptr || root->key == key) {//if the root is null or the required element is the root
        return root;
    }
    if (root->key < key) {//if the required key is greater than the root key
        return search(root->right, key);
    }
    else {
        return search(root->left, key);//if not
    }
}

//Node* DelNode(Node* root, int key)//function to delete a specific node from a BST
//{
//    if (root == nullptr) {//if the tree is empty
//        return root;
//    }
//    if (key < root->key) {//if the required key is smaller than the root one. It means that it's located in the left subtree
//        root->left = DelNode(root->left, key);
//    }
//    else if (key > root->key) {
//        root->right = DelNode(root->right, key);
//    }
//    //if the node is same as the root one
//    else {
//        if (root->left == nullptr) {
//            Node* temp = root->right;
//            delete root;
//            return temp;
//        }
//        else if (root->right == nullptr) {
//            Node* temp = root->right;
//            delete root;
//            return temp;
//        }
//        Node* temp = root;
//        temp->key = 100;
//        char temp_val[10] = "deleted";
//        *(temp->value) = *temp_val;
//        root->key = temp->key;
//        *(root->value) = *(temp->value);
//        root->right = DelNode(root->right, temp->key);
//    }
//    return root;
//}

Node* DelNode(Node* root, int key) {
    if (root == nullptr) {// If the tree is empty or the node is not found
        return root;
    }

    if (key < root->key) {// If the key to be deleted is smaller than the root's key
        root->left = DelNode(root->left, key);
    }
    else if (key > root->key) {// If the key to be deleted is greater than the root's key
        root->right = DelNode(root->right, key);
    }
    else {// If the key is found
        if (root->left == nullptr) {// If the node has no left child or only a right child
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {// If the node has only a left child
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // If the node has two children
        Node* successor = root->right;
        while (successor->left != nullptr) {// Find the inorder successor
            successor = successor->left;
        }

        // Copy the successor's data to the current node
        root->key = successor->key;
        for (int i = 0; i < 10; i++) {
            root->value[i] = successor->value[i];
        }

        root->right = DelNode(root->right, successor->key);// Delete the inorder successor
    }
    return root;
}


void FreeTree(Node* root)//function to delete the whole BST
{
    if (root == nullptr) {//if the tree is already empty
        return;
    }
    FreeTree(root->left);//recursively implement the function
    FreeTree(root->right);
    delete root;//delete the node
}

//int count_even(Node* node)//function to count all the nodes with even keys
//{
//    int count = 0;//var to store the amount of required nodes
//    if (node != nullptr) {
//        if (node->key % 2 == 0) {//if the node's key is even
//            count = 1;
//        }
//    }
//    else {
//        return 0;
//    }
//    return count + count_even(node->left) + count_even(node->right);
//}

int count_even(Node* node) {
    if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {// Если узел является листом или nullptr, то возвращается 0
        return 0;
    }
    int count = 0;
    if (node->left && (node->left->left != nullptr || node->left->right != nullptr)) {// Если у узла есть левый узел и у него есть хотя бы один потомок
        if (node->left->key % 2 == 0) {// Если ключ левого узла четный, увеличиваем count
            count += 1;
        }
    }
    if (node->right && (node->right->left != nullptr || node->right->right != nullptr)) {// Если у узла есть правый узел и у него есть хотя бы один потомок
        if (node->right->key % 2 == 0) {// Если ключ правого узла четный, увеличиваем count
            count += 1;
        }
    }
    return count + count_even(node->left) + count_even(node->right);// Рекурсивный вызов для левого и правого поддеревьев
}