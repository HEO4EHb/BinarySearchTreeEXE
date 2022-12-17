#include <iostream>
#include <fstream>
#include <string>
#include <stack>

struct Elem {
    int data;
    int level;
    Elem* left;
    Elem* right;
    Elem* parent;
};



//создание элемента
Elem* MAKE(int data, Elem* p) {
    Elem* q = new Elem;
    q->data = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}


//вставка элемента в дерево
void ADD(int data, Elem*& root) {
    if (root == nullptr) {
        root = MAKE(data, nullptr);
        return;
    }
    Elem* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr)) {
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    }
    if (data == v->data)
        return;
    Elem* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else if (data > v->data)
        v->right = u;
}

void PASS(Elem* v) {
    if (v == nullptr)
        return;
    PASS(v->left);
    std::cout << v->data << " ";
    PASS(v->right);
}


//поиск в дереве элемента
Elem* SEARCH(int data, Elem* v) {
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else  if (data > v->data)
        return SEARCH(data, v->right);
}

//удаление определенного элемента в дереве
void DELETE(int data, Elem*& root) {
    Elem* u = SEARCH(data, root);
    if (u == nullptr)
        return;
    if (u->left == nullptr && u->right == nullptr && u == root) {
        delete root;
        root = nullptr;
        return;
    }
    if (u->left == nullptr && u->right != nullptr && u == root) {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    if (u->left != nullptr && u->right == nullptr && u == root) {
        Elem* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }
    if (u->left != nullptr && u->right != nullptr) {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    Elem* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;
    delete u;
}
//Добавление скобочной записи в виде БДП
void ADD_BY_PARENTHESIS(int data, Elem*& root, bool inLeft)
{
    Elem* v = root;
    Elem* u = MAKE(data, v);
    if (inLeft)
        v->left = u;
    else
        v->right = u;
}

//Заполнение дереве скобочной записью
void FILL_TREE(std::string& bracketEntry, int& i, Elem*& root)
{
    int value = 0;
    while (bracketEntry[i] != '\0')
    {
        switch (bracketEntry[i])
        {
        case '(':
        {
            i++;
            value = 0;
            while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
            {
                value = value * 10 + bracketEntry[i] - '0';
                i++;
            }

            if (value != 0)
            {
                ADD_BY_PARENTHESIS(value, root, true);
                if (bracketEntry[i] == '(')
                    FILL_TREE(bracketEntry, i, root->left);
            }
            value = 0;
            break;
        }
        case ',':
        {
            i++;
            value = 0;
            while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
            {
                value = value * 10 + bracketEntry[i] - '0';
                i++;
            }

            if (value != 0)
            {
                ADD_BY_PARENTHESIS(value, root, false);
                if (bracketEntry[i] == '(')
                    FILL_TREE(bracketEntry, i, root->right);
            }
            value = 0;
            break;
        }
        case ')':
            i++;
            return;
        default:
            break;
        }
    }
}


//определение глубины элемента в дереве
int DEPTH(int data, Elem* v, int k) {
    if (v == nullptr) {
        return -15;
    }
    if (v->data == data) {
        return k;
    }
    if (data < v->data)
        return DEPTH(data, v->left, k + 1);
    if (data > v->data)
        return DEPTH(data, v->right, k + 1);
}


void CLEAR(Elem*& v) {
    if (v == nullptr)
        return;
    CLEAR(v->left);
    CLEAR(v->right);
    delete v;
    v = nullptr;
}


/*Рекурсивные обходы (прямой, центральный, концевой)*/
void straightOrder(Elem* root)
{
    if (root == nullptr)
        return;
    std::cout << root->data << std::endl;

    straightOrder(root->left);
    straightOrder(root->right);
}

void centralOrder(Elem* root)
{
    if (root == nullptr)
        return;
    centralOrder(root->left);
    std::cout << root->data << std::endl;
    centralOrder(root->right);
}

void endOrder(Elem* root)
{
    if (root == nullptr)
        return;
    endOrder(root->left);
    endOrder(root->right);
    std::cout << root->data << std::endl;

}
/*Нерекурсивные обходы*/
void nonRecursiveOrder(Elem* root)
{
    if (root == nullptr)
        return;
    std::stack<Elem*> stack;
    stack.push(root);

    while (!stack.empty())
    {
        Elem* node = stack.top();
        stack.pop();
        std::cout << node->data << std::endl;

        if (node->left != nullptr)
        {
            stack.push(node->left);
        }
        if (node->right != nullptr)
        {
            stack.push(node->right);
        }
    }
}

void PRINT(Elem* root)
{
    if (root == nullptr)
    {
        std::cout << std::endl;
        return;
    }


    PRINT(root->right);

    for (int i = root->level; i > 0; i--)
    {
        std::cout << '\t';
    }
    std::cout << root->data << std::endl;

    PRINT(root->left);
}

void menu(Elem* root)
{
    std::cout << "Main menu:" << std::endl;
    bool work = false;
    int action;
    while (!work)
    {
        std::cout << "Choose operation: " << std::endl;
        std::cout << "Adding(1)\nDeleting(2)\nSearch(3)\nExit(4)" << std::endl;
        std::cin >> action;
        switch (action)
        {
        case 1:
        {
            int value;
            std::cout << "Enter value to add: ";
            std::cin >> value;
            ADD(value, root);
            break;
        }
        case 2:
        {
            int value;
            std::cout << "Enter value to erase: ";
            std::cin >> value;
            DELETE(value, root);
            break;
        }
        case 3:
        {
            int value;
            std::cout << "Enter value,you need to find: ";
            std::cin >> value;

            Elem* e = nullptr;
            e = SEARCH(value, root);
            if (e == nullptr)
                std::cout << "Value not found" << std::endl;
            else
                std::cout << "Value found" << std::endl;
            break;
        }
        case 4:
            work = true;
            break;
        default:
            break;
        }
    }
    PRINT(root);
}

int main() {


    Elem* root = nullptr;//начальное значение корня
    std::string bracketEntry;//создание скобочной записи
    std::cout << "Enter linear bracket notation:" << std::endl;
    std::cin >> bracketEntry;



    int digit = 0;
    int i = 0;
    while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
    {
        digit += digit * 10 + bracketEntry[i] - '0';
        i++;
    }

    ADD(digit, root);
    FILL_TREE(bracketEntry, i, root);

    PASS(root);
    std::cout << std::endl << "----------" << std::endl;
    menu(root);

    CLEAR(root);
    return 0;
}


//8(3(1,6(4,7)),10(,14(13,)))
