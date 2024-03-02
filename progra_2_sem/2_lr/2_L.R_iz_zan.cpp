
////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Element {
    int number;
    Element *next;
};

struct GroupElement {
  Element *prevElement;
  Element *findedElement;
};

void Print(Element *begin);

GroupElement * FindFirst(Element *findingBegin, int newNumber);

void Add_Beg(Element *addingPrev, int newNumber);

void Delete(Element **u, int x);

int main()
{
    Element *begin = NULL;
    begin = new Element;
    begin->number = 5;

    Element *end;
    end = begin;
    end->next = new Element;
    end = end->next;
    end->number = -1;
    end->next = NULL;
    
    end = end;
    end->next = new Element;
    end = end->next;
    end->number = 3;
    end->next = NULL;
      
    Print(begin);
    
    GroupElement * v = FindFirst(begin, -1);
    
    cout << endl << v->findedElement->number << ", ";
    cout << v->prevElement->number << endl;
    
    Add_Beg(v->prevElement, 1);
    
    Print(begin);
    
    Delete(&begin, -1);
    
    Print(begin);
    
    return 0;
}

void Print(Element *begin)
{
    Element *u = begin;
    cout << "Spisok:" << endl;
    while(u) {
        cout << u->number << endl;
        u = u->next;
    }
}

GroupElement * FindFirst(Element *findingBegin, int newNumber)
{
    GroupElement *e = new GroupElement;
    e->findedElement = findingBegin;
    e->prevElement = findingBegin;
    while(e->findedElement)
    {
      if(e->findedElement->number == newNumber)
        return e;
      e->prevElement = e->findedElement;   
      e->findedElement = e->findedElement->next;
   }
   return 0;
}

void Add_Beg(Element *addingPrev, int newNumber)
{
   Element *t = new Element;
   Element *u = addingPrev->next;
   t->number = newNumber;
   t->next = u;
   addingPrev->next = t;
   u = t;
}

void Delete(Element **u, int x)
{
   if(*u == 0) // исходный список пуст - удалять нечего!
   {
      return;
   }
   Element *t = *u;
   Element *t1 = t->next;
   while(t1)
   {
      if(t1->number == x)
      {
         t->next = t1->next;
         delete t1;
         return;
      }
      t = t1;
      t1 = t1->next;
   }
}
