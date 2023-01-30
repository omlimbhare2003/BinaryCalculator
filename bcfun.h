
typedef struct node {
    int data;
    struct node *prev, *next;
}node;

typedef node* number;

void init(number* p);
number createnode(int d);
void append(number* l, int d);
void destroy(number *l);
void insert_beg(number* l, int d);
void traverse(number l);
int compare(number p, number q);
int length_num(number l);
number copy_num(number l);

number add_num(number p, number q);
number sub_num(number p, number q);
number mul_num(number p, number q);
number div_num(number p, number q);
number power_num(number p, number pow);
number modulus_num(number p, number q);

//istack is for number (operand) stack

typedef struct istack {
    int top, size, count;
    node** nodearr;
}istack;

void initstack(istack *st, int size);
void push(istack *st, node *n);
node* pop(istack *st);
int isFull(istack st);
int isEmpty(istack st);
node* peek(istack st);


typedef struct oprstack {
    int top, size, count;
    int *arr;
}oprstack;

void init_oprstack(oprstack *st, int size);
void push_oprstack(oprstack *st, int d);
int pop_oprstack(oprstack *st);
int isFull_oprstack(oprstack st);
int isEmpty_oprstack(oprstack st);
int peek_oprstack(oprstack st);

void process(oprstack *oprptr, istack *opndptr);
int precedence(char c);
