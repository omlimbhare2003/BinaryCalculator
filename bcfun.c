#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<ctype.h>
#include "bcfun.h"



void initstack(istack *st, int size) {
    st->top = -1;
    st->count = 0;
    st->size = size;
    st->nodearr = (node**)malloc(sizeof(istack)*size);
    return;
}

int isEmpty(istack st) {
    if(st.top == -1)
        return 1;
    return 0;
}

int isFull(istack st) {
    if(st.top == st.size-1)
        return 1;
    return 0;
}

void push(istack *st, node *n) {
    if(!isFull(*st)) {
        st->top++;
        st->nodearr[st->top] = n;
        st->count++;
    }
    else
        printf("Stack Overflow\n");
    return;
}

node* pop(istack *st) {
    node* item = NULL;
    if(!isEmpty(*st)) {
        item = st->nodearr[st->top];
        st->top--;
        st->count--;
    }
    else printf("Stack Underflow\n");
    return item;
}

node* peek(istack st) {
    node* p = NULL;
    if(!isEmpty(st)) {
        p = st.nodearr[st.top];
        return p;
    }
    else
        return p;
}

void init_oprstack(oprstack *st, int size) {
    st->top = -1;
    st->count = 0;
    st->size = size;
    st->arr = (int*)malloc(sizeof(oprstack)*size);
    return;
}

int isEmpty_oprstack(oprstack st) {
    if(st.top == -1)
        return 1;
    return 0;
}

int isFull_oprstack(oprstack st) {
    if(st.top == st.size-1)
        return 1;
    return 0;
}

void push_oprstack(oprstack *st, int d) {
    if(!isFull_oprstack(*st)) {
        st->top++;
        st->arr[st->top] = d;
        st->count++;
    }
    else
        printf("Stack Overflow\n");
    return;
}

int pop_oprstack(oprstack *st) {
    int item = INT_MIN;
    if(!isEmpty_oprstack(*st)) {
        item = st->arr[st->top];
        st->top--;
        st->count--;
    }
    else printf("Stack Underflow\n");
    return item;
}

int peek_oprstack(oprstack st) {
    if(!isEmpty_oprstack(st))
        return st.arr[st.top];
    else
        return INT_MIN;
}



void process(oprstack *oprptr, istack *opndptr) {
    node* B = pop(opndptr);
    node* A = pop(opndptr);
    char op = pop_oprstack(oprptr);
    node *res;
    init(&res);
    switch(op) {
        case '+':
            res = add_num(A ,B);
            break;
        case '-':
            res = sub_num(A ,B);
            break;
        case '*':
            res = mul_num(A ,B);
            break;
        case '/':
            res = div_num(A ,B);
            break;
        case '%':
            res = modulus_num(A ,B);
            break;
        case '^':
            res = power_num(A ,B);
            break;
        default:
            printf("Undefined Operator\n");
            res = NULL;
            break;
    }
    push(opndptr, res);
    return;
}

int precedence(char c){
    if(c == '+')
        return 10;
    else if(c == '-')
        return 10;
    else if(c == '*')
        return 20;
    else if(c == '/')
        return 20;
    else if(c == '%')
        return 20;
    else if(c == '^')
        return 30;
    else if(c == '(')
        return 5;
    return 0;
}

void init(number* p) {
    *p = NULL;
}

number createnode(int d) {
    node* nn = (node*)malloc(sizeof(node));
    if(!nn) return NULL;
    nn->data = d;
    nn->next = NULL;
    nn->prev = NULL;
    return nn;
}

void append(number* l, int d) {
    node *nn = createnode(d);
    if(nn) {
        if(*l == NULL)
            *l = nn;
        else {
            node* p = *l;
            while(p->next != NULL)
                p = p->next;
            p->next = nn;
            nn->prev = p;
        }
    }
    return;
}

void insert_beg(number* l, int d) {
    node* nn = createnode(d);
    if(nn) {
        if(*l == NULL)
            *l = nn;
        else {
            node *p = *l;
            *l = nn;
            nn->next = p;
            p->prev = nn;
        }
    }
    return;
}

void destroy(number *l) {
    if(*l) {
        node *p = *l;
        while(p->next) {
            p = p->next;
            free(p->prev);
        }
        free(p);
    }
    *l = NULL;
    return;
}

void traverse(number l) {
    int flag = 0;
    if(l == NULL)
        return;
    else {
        node *p = l;
        while(p != NULL) {
            if(p->data == 0 && !flag);
            else {
                flag = 1;
                printf("%d", p->data);
            }
            p = p->next;
        }
        if(flag == 0) printf("0");
        printf("\n");
    }
    return;
}

int compare(number p, number q) {
    while(p && !p->data)
        p = p->next;
    while(q && !q->data)
        q = q->next;
    if(p && !q) return 1;
    if(!p && q) return -1;
    if(p == NULL && q == NULL)
        return 0;
    int len1 = length_num(p);
    int len2 = length_num(q);
    if(len1 > len2)
        return 1;
    else if(len1 < len2)
        return -1;
    else {
        while(p && q) {
            if(p->data > q->data)
                return 1;
            else if(p->data < q->data)
                return -1;
            p = p->next;
            q = q->next;
        }
        if(!p && !q)
            return 0;
    }

}

int length_num(number l) {
    int len = 0;
    if(l) {
        node* p = l;
        while(p->data == 0)
            p = p->next;
        while(p != NULL) {
            p = p->next;
            len++;
        }
    }
    return len;
}

number copy_num(number l) {
    node *m;
    init(&m);
    while(l != NULL) {
        append(&m, l->data);
        l = l->next;
    }
    return m;
}

number add_num(number p, number q) {
    node *n3;
    init(&n3);
    int carry = 0;
    while(p->next != NULL)
        p = p->next;
    while(q->next != NULL)
        q = q->next;
    while(p != NULL && q != NULL) {
        insert_beg(&n3, (p->data + q->data + carry) % 10);
        carry = (p->data + q->data + carry) / 10;
        p = p->prev;
        q = q->prev;
    }
    while(p) {
        insert_beg(&n3, (p->data + carry) % 10);
        carry = (p->data + carry) / 10;
        p = p->prev;
    }
    while(q) {
        insert_beg(&n3, (q->data + carry) % 10);
        carry = (q->data + carry) / 10;
        q = q->prev;
    }
    if(carry)
        insert_beg(&n3, carry);
    return n3;
}

number sub_num(number p, number q) {
    node *n3;
    init(&n3);
    node *a  = p, *b = q;
    if(compare(p, q) == -1) {
        node* temp = p;
        p = q;
        q = temp;
    }
    int borrow = 0;
    while(p->next != NULL)
        p = p->next;
    while(q->next != NULL)
        q = q->next;
    while(p != NULL && q != NULL) {
        if(p->data - q->data - borrow >= 0) {
            insert_beg(&n3, p->data - q->data - borrow);
            borrow = 0;
        }
        else {
            insert_beg(&n3, 10 + p->data - q->data - borrow);
            borrow = 1;
        }
        p = p->prev;
        q = q->prev;
    }
    while(p) {
        if(p->data - borrow >= 0) {
            insert_beg(&n3, p->data - borrow);
            borrow = 0;
        }
        else {
            insert_beg(&n3, 10 + p->data - borrow);
            borrow = 1;
        }
        p = p->prev;
    }
    if(compare(a, b) == -1) {
        node *m = n3;
        while(!m->data)
            m = m->next;
        m->data = -(m->data);
    }
    //while(!n3->data)
      //   n3 = n3->next;
    return n3;
}

number mul_num(number p, number q) {
    node *n3, *n4;
    node *m = p;
    init(&n4);
    append(&n4, 0);
    int carry, count = 0, i;
    while(q->next != NULL)
        q = q->next;
    while(q != NULL) {
        p = m;
        while(p->next != NULL)
            p = p->next;
        init(&n3);
        carry = 0;
        while(p != NULL) {
            insert_beg(&n3, (q->data * p->data + carry) % 10);
            carry = (q->data * p->data + carry) / 10;
            p = p->prev;
        }
        if(carry)
            insert_beg(&n3, carry);
        for(i = 0; i < count; i++)
            append(&n3, 0);
        n4 = add_num(n3, n4);
        destroy(&n3);
        q = q->prev;
        count++;
    }
    return n4;
}

number div_num(number dividend, number divisor) {
    node *buffer, *res, *count, *m, *num_zero;
    init(&buffer);
    init(&res);
    init(&count);
    init(&num_zero);
    append(&num_zero, 0);
    append(&count, 0);
    if(compare(divisor, num_zero) == 0) {
        printf("Can't divided by zero\n");
        return res;
    }
    append(&buffer, dividend->data);
    dividend = dividend->next;
    if(dividend == NULL) {
        if(length_num(divisor) == 1 && divisor->data != 0)
            append(&res, buffer->data / divisor->data);
        if(length_num(divisor) > 1)
            append(&res, 0);
    }
    int flag1 = 0, flag2 = 0;
    while(dividend != NULL) {
            flag2 = 0;
        while(compare(buffer, divisor) != 1 && compare(buffer, divisor) != 0) {
            if(dividend == NULL)
                break;
            if(compare(buffer, num_zero) == 0 && dividend->data == 0) {
                append(&res, 0);
                dividend = dividend->next;
            }
            else if(flag1 && flag2 && compare(buffer, divisor) == -1) {
                if(compare(buffer, num_zero) != 0) append(&res, 0);
                append(&buffer, dividend->data);
                dividend = dividend->next;
            }
            else {
                append(&buffer, dividend->data);
                dividend = dividend->next;
            }
            flag2 = 1;
        }
        flag1 = 1;
        //flag = 0;
        /*do {
            if(dividend == NULL)
                break;
            append(&buffer, dividend->data);
            if(flag) append(&res, 0);
            dividend = dividend->next;
            flag = 1;
        }while(compare(buffer, divisor) != 1 && compare(buffer, divisor) != 0);*/
        init(&m);
        m = copy_num(divisor);
        count->data = 0;
        while(compare(m, buffer) == -1 || compare(m, buffer) == -0) {
            m = add_num(m, divisor);
            count->data++;
        }
        if(compare(buffer, num_zero) != 0) append(&res, count->data);
        node *prod = mul_num(count, divisor);
        buffer = sub_num(buffer, prod);
        destroy(&m);
    }
    return res;
}

number power_num(number p, number pow) {
    node *num_one, *num_zero, *res;
    init(&num_one);
    init(&num_zero);
    append(&num_one, 1);
    append(&num_zero, 0);
    res = num_one;
    if(compare(pow, num_zero) == 0)
        return res;
    while(!pow->data)
        pow = pow->next;
    while(compare(pow, num_zero)) {
        res = mul_num(p, res);
        pow = sub_num(pow, num_one);
    }
    return res;
}

number modulus_num(number p, number q) {
    node *n3 = div_num(p, q);
    node *n4 = sub_num(p, mul_num(n3, q));
    return n4;
}
