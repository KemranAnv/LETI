#include <iostream>

using namespace std;

struct Data
{
	float number;
};
struct Element
{
	Data d;
	Element *next;
};

void Print(Element *begin);

void Push(Element **begin);

int main()
{
	Element *begin = NULL;
	
	Push(&begin);
	
	Print(begin);
	
	cout << "\n";
	return 0;
}

void Print(Element *begin)
{
	if(begin == NULL)
		return;
		
	Element *u = begin;
	cout << "List: ";
	while(u) {
		if(u -> d.number > 0) 
			cout << u -> d.number << ' ';
		u = u -> next;
	}
}

void Push(Element **begin)
{
	int q, num;
	cout << "Enter a quantity of number: ";
	cin >> q;
	
	for(int i = 1; i <= q; i++) {
		cout << "№" << i << ' ';
		cin >> num;
		cout << "\n";
		Element *u = new Element;
		u -> d.number = num;
		u -> next = *begin;
		*begin = u;
	}
}
