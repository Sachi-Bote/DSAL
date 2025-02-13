#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    char k[20];
    char m[20];
    Node *left, *right;
};

class Dict {
public:
    Node *root;
    
    Dict() { root = NULL; }
    ~Dict() { destroyTree(root); }

    void create();
    void display(Node *root);
    void insert(Node *root, Node *temp);
    int search(Node *root, char []);
    int update(Node *root, char []);
    Node* del(Node *root, char []);
    Node* min(Node *root);
    void destroyTree(Node *root);
};

void Dict::create() {
    Node *temp;
    int ch;
    do {
        temp = new Node;
        cout << "\nEnter Keyword: ";
        cin >> temp->k;
        cout << "Enter Meaning: ";
        cin >> temp->m;

        temp->left = temp->right = NULL;

        if (root == NULL)
            root = temp;
        else
            insert(root, temp);

        cout << "\nDo you want to add more (y=1/n=0): ";
        cin >> ch;
    } while (ch == 1);
}

void Dict::insert(Node *root, Node *temp) {
    if (strcmp(temp->k, root->k) < 0) {
        if (root->left == NULL)
            root->left = temp;
        else
            insert(root->left, temp);
    } else {
        if (root->right == NULL)
            root->right = temp;
        else
            insert(root->right, temp);
    }
}

void Dict::display(Node *root) {
    if (root != NULL) {
        display(root->left);
        cout << "\nKeyword: " << root->k << "\tMeaning: " << root->m;
        display(root->right);
    }
}

int Dict::search(Node *root, char k[20]) {
    int c = 0;
    while (root != NULL) {
        c++;
        if (strcmp(k, root->k) == 0) {
            cout << "\nNumber of Comparisons: " << c;
            return 1;
        }
        root = (strcmp(k, root->k) < 0) ? root->left : root->right;
    }
    return -1;
}

int Dict::update(Node *root, char k[20]) {
    while (root != NULL) {
        if (strcmp(k, root->k) == 0) {
            cout << "\nEnter New Meaning for " << root->k << ": ";
            cin >> root->m;
            return 1;
        }
        root = (strcmp(k, root->k) < 0) ? root->left : root->right;
    }
    return -1;
}

Node* Dict::del(Node *root, char k[20]) {
    if (root == NULL) {
        cout << "\nElement Not Found";
        return root;
    }

    if (strcmp(k, root->k) < 0) {
        root->left = del(root->left, k);
    } else if (strcmp(k, root->k) > 0) {
        root->right = del(root->right, k);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = min(root->right);
        strcpy(root->k, temp->k);
        root->right = del(root->right, temp->k);
    }
    return root;
}

Node* Dict::min(Node *q) {
    while (q->left != NULL)
        q = q->left;
    return q;
}

void Dict::destroyTree(Node *root) {
    if (root) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}

int main() {
    int ch;
    Dict d;

    do {
        cout << "\nMenu\n1. Create\n2. Display\n3. Search\n4. Update\n5. Delete\n0. Exit\nEnter Your Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                d.create();
                break;
            case 2:
                if (d.root == NULL)
                    cout << "\nNo Keywords Found!";
                else
                    d.display(d.root);
                break;
            case 3:
                if (d.root == NULL) {
                    cout << "\nDictionary is Empty. Add Keywords First!";
                } else {
                    char k[20];
                    cout << "\nEnter Keyword to Search: ";
                    cin >> k;
                    if (d.search(d.root, k) == 1)
                        cout << "\nKeyword Found";
                    else
                        cout << "\nKeyword Not Found";
                }
                break;
            case 4:
                if (d.root == NULL) {
                    cout << "\nDictionary is Empty. Add Keywords First!";
                } else {
                    char k[20];
                    cout << "\nEnter Keyword to Update Meaning: ";
                    cin >> k;
                    if (d.update(d.root, k) == 1)
                        cout << "\nMeaning Updated";
                    else
                        cout << "\nKeyword Not Found";
                }
                break;
            case 5:
                if (d.root == NULL) {
                    cout << "\nDictionary is Empty. Add Keywords First!";
                } else {
                    char k[20];
                    cout << "\nEnter Keyword to Delete: ";
                    cin >> k;
                    d.root = d.del(d.root, k);
                }
                break;
            case 0:
                cout << "\nExiting...";
                break;
            default:
                cout << "\nInvalid Choice! Try Again.";
        }
    } while (ch != 0);

    return 0;
}
