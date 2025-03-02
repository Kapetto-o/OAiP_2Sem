struct Stack {
    double data;
    Stack* next;
};

using namespace std;

void push(Stack*& st, double data);
void formUniqueStack(Stack*& st1, Stack*& st2, Stack*& result);
void clear(Stack*& st);
void toFile(Stack*& st);
void fromFile(Stack*& st);
void show(Stack*& st);
bool contains(Stack* st, double data);
double pop(Stack*& st);
void mergeStacks(Stack*& st1, Stack*& st2, Stack*& result);