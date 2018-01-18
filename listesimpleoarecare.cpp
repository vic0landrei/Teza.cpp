#include<iostream>
using namespace std;
typedef struct element {
                         int info;
                         struct element *next;
                       } termen;
 
typedef struct {
                int length;
                termen *start,*current,*finalist;
                } lista;
 
lista *L;
 
lista *initlist() {
    lista *result=new lista;
    result->length=0;
    result->start=result->current=result->finalist=NULL;
    return result;
}
 
int isempty(lista *L) {
    return  (L->length==0);
}
 
lista *addright(lista *L,int value) {
    if (isempty(L)) {
        termen *newone=new element;
        newone->info=value;
        L->current=L->finalist=L->start=newone;
        L->length++;
        return L;
    }
    if (L->current==L->finalist) {
        termen *newone = new element;
        newone->info = value;
        L->current->next = newone;
        L->current = L->finalist = newone;
        L->length++;
        return L;
    }
    termen *newone=new element;
    newone->info=value;
    newone->next=L->current->next;
    L->current->next=newone;
    L->current=newone;
    L->length++;
    return L;
}
 
int searchvalue(lista **L,int value) {
    termen *carrier;
    carrier=(*L)->start;
    while ((carrier!=(*L)->finalist)&&(carrier->info!=value)) {
        carrier=carrier->next;
    }
    if ((carrier==(*L)->finalist)&&(carrier->info!=value)) {
        return 0;
    }
    (*L)->current=carrier;
    return 1;
}
 
lista *delright(lista *L) {
    if(isempty(L) || L->current == L->finalist) return L;
    if(L->current->next == L->finalist) {
        L->current->next = NULL;
        delete L->finalist;
        L->finalist = L->current;
        L->length--;
        return L;
    }
    termen *aux;
    aux = L->current->next;
    L->current->next = L->current->next->next;
    delete aux;
    L->length--;
    return L;
}
 
lista * addleft(lista *L, int value) {
    if(isempty(L)) {
        termen *newone=new element;
        newone->info=value;
        L->current=L->finalist=L->start=newone;
        L->length++;
        return L;
    }
    if(L->current == L->start) {
        termen *newone=new element;
        newone->info=value;
        newone->next = L->start;
        L->current = L->start = newone;
        L->length++;
        return L;
    }
    termen *newone=new element;
    newone->info=value;
    newone->next = L->current;
    termen *carrier;
    carrier = L->start;
    while(carrier->next->info != L->current->info) carrier = carrier->next;
    carrier->next = newone;
    L->current = newone;
    L->length++;
    return L;
}
 
lista *delleft(lista *L) {
    if(isempty(L) || L->current == L->start) return L;
    if(L->start->next == L->current) {
        delete L->start;
        L->start = L->current;
        L->length--;
        return L;
    }
    termen *aux;
    aux = L->start;
    while(aux->next->next->info != L->current->info) aux = aux->next;
    delete aux->next;
    aux->next = L->current;
    L->length--;
    return L;
}
 
int show(lista *L) {
    cout<<endl;
    termen *carrier;
    carrier=L->start;
    int counter=L->length;
    while (counter>0) {
        cout<<carrier->info<<" ";
        carrier=carrier->next;
        counter--;
    }
}
 
int main() {
    L=initlist();
    for(int i=1;i<=3;i++) L=addright(L,i);
    show(L); // 1 2 3
    searchvalue(&L,2);
    L=addright(L,0);
    show(L); // 1 2 0 3
    searchvalue(&L,1);
    L=delright(L);
    show(L); // 1 0 3
    searchvalue(&L,456);
    L=addright(L,-1);
    show(L); // 1 -1 0 3
    return 0;
}
