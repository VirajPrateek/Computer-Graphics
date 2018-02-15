/*
*
************Sutherland-Hodgman Polygon Clipping Algorithm***************
*@Author : Kumar Prateek Viraj
*@First Complete : February 11, 2018
*
*"Clipping area must be a rectangle
*coordinates of polygon to be clipped should be in Anti-Clockwise direction.
* However, I've tested it on clockwise data as well, 
*and that worked fine so far for me."
*/
#include<iostream>
#include<conio.h>
#include<stdio.h>
using namespace std;
	
	int X_MIN, Y_MIN, X_MAX, Y_MAX;
	int numberOfVertices;
	int *polygon;

struct vertex{
	int x;
	int y;
	vertex *next;
}*head, *tail, *temp; 
class outputList{
public: 
	outputList(){
		head = tail = NULL;
	}

	void insert(int, int);
	int new_y(int, int, int);
	int new_x(int, int, int);
	int count_and_renew();
	void clear_outputList();
	void test_display();
};

void outputList::insert(int x, int y){
	 temp = new vertex;
	 temp->x = x;
	 temp->y = y;
	 temp->next = NULL;
	if(head == NULL){
		head = tail = temp;
	}
	else{
		tail->next = temp;
		tail = temp;
	}
}

int outputList::new_y(int firstPos, int secondPos, int boundary){
	int x1 = polygon[firstPos];
	int y1 = polygon[firstPos + 1];
	int x2 = polygon[secondPos];
	int y2 = polygon[secondPos + 1];
	int dx = (x2 - x1);
	int dy = (y2 - y1);
	if(dx == 0)
		return y1;
	else{
		int new_y = (((dy * (boundary - x1))/ dx) + y1);
		return new_y;
	}
}

int outputList::new_x(int firstPos, int secondPos, int boundary){
	int x1 = polygon[firstPos];
	int y1 = polygon[firstPos + 1];
	int x2 = polygon[secondPos];
	int y2 = polygon[secondPos + 1];
	int dx = (x2 - x1);
	int dy = (y2 - y1);
	if(dy == 0){
		return x1;
	}else{
		int new_x = ((((boundary - y1) * dx)/dy) + x1);
		return new_x;
	}
}

int outputList::count_and_renew(){
	temp = head;
	int count = 0;
	while(temp->next != NULL){
		polygon[count++] = temp->x;
		polygon[count++] = temp->y;
		temp = temp->next;
	}
	polygon[count++] = temp->x;
	polygon[count] = temp->y;
	/*again, for closing the figure*/
	polygon[count+1] = head->x;
	polygon[count+2] = head->y;
return count;
}
void outputList::clear_outputList(){
	temp = head;
	while(temp){
		head = temp->next;
		delete temp;
		temp = head;
	}
}
void outputList::test_display(){
	/*debug purpose*/
	cout<<"\ntest_display: ";
	temp = head;
	while(temp->next != NULL){
		cout<<"("<<temp->x<<","<<temp->y<<")";
		temp = temp->next;
	}
	cout<<"("<<temp->x<<","<<temp->y<<")";
}

int main(){
	freopen("input.txt", "r", stdin);
	cin>>X_MIN>>Y_MAX>>X_MAX>>Y_MIN;
	cin>>numberOfVertices;
	outputList ol;
	polygon = new int[(2*numberOfVertices)+2];
	/*Anticlockwise polygon direction*/
	for(int i = 0; i<(2*numberOfVertices); i++)
		cin>>polygon[i];

	/*to close the figure*/
	polygon[2*numberOfVertices] = polygon[0];
	polygon[(2*numberOfVertices)+1] = polygon[1];
cout<<"Original: ";
for (int i = 0; i<(2*numberOfVertices); i = i+2)
		cout<<"("<<polygon[i]<<","<<polygon[i+1]<<")";
/*LEFT EDGE*/
	for (int i = 0; i <(2*numberOfVertices); i = i + 2 )
	{
		if((polygon[i] >= X_MIN) && (polygon[i+2] >= X_MIN)){
			//inside-inside = save second vertex only
			ol.insert(polygon[i+2], polygon[i+3]);
		}
		else if((polygon[i] >= X_MIN) && (polygon[i+2] < X_MIN)){
			//inside-outside = save only new vertex
			int new_y = ol.new_y(i, i+2, X_MIN);
			ol.insert(X_MIN, new_y);
		}
		else if((polygon[i] < X_MIN) && (polygon[i+2] >= X_MIN)){
			//outside-inside = save new vertex and second vertex
			int new_y = ol.new_y(i, i+2, X_MIN);
			ol.insert(X_MIN, new_y);
			ol.insert(polygon[i+2], polygon[i+3]);
		}	
	}
	//ol.test_display();
	int count = ol.count_and_renew();
	ol.clear_outputList();
/*BOTTOM EDGE*/
	for (int i = 1; i <= count; i = i+2)
	{
		if((polygon[i] >= Y_MIN) && (polygon[i+2] >= Y_MIN)){
			//inside-inside = save only second vertex;
			ol.insert(polygon[i+1], polygon[i+2]);
		}
		else if((polygon[i] >= Y_MIN) && (polygon[i+2] <Y_MIN)){
			//inside-outside = save only new vertex;
			int new_x = ol.new_x(i-1, i+1, Y_MIN);
			ol.insert(new_x, Y_MIN);
		}
		else if((polygon[i] < Y_MIN) && (polygon[i+2] >= Y_MIN)){
			//outside-inside = save new vertex and second vertex;
			int new_x = ol.new_x(i-1, i+1, Y_MIN);
			ol.insert(new_x, Y_MIN);
			ol.insert(polygon[i+1], polygon[i+2]);
		}
	}

	count = ol.count_and_renew();
	ol.clear_outputList();
/*RIGHT EDGE*/
	for (int i = 0; i <= count; i = i+2)
	{
		if((polygon[i] <= X_MAX) && (polygon[i+2] <= X_MAX)){
			//inside-inside = save only second vertex;
			ol.insert(polygon[i+2], polygon[i+3]);
		}
		else if((polygon[i] <= X_MAX) && (polygon[i+2] > X_MAX)){
			//inside-outside = save only new vertex;
			int new_y = ol.new_y(i, i+2, X_MAX);
			ol.insert(X_MAX, new_y);
		}
		else if((polygon[i] > X_MAX) && (polygon[i+2] <= X_MAX)){
			//outside-inside = save new vertex and second vertex;
			int new_y = ol.new_y(i, i+2, X_MAX);
			ol.insert(X_MAX, new_y);
			ol.insert(polygon[i+2], polygon[i+3]);
		}
	}

	count = ol.count_and_renew();
	ol.clear_outputList();
/*TOP EDGE*/
	for (int i = 1; i <= count; i = i+2)
	{
		if((polygon[i] <= Y_MAX) && (polygon[i+2] <= Y_MAX)){
			//inside-inside = save only second vertex;
			ol.insert(polygon[i+1], polygon[i+2]);
		}
		else if((polygon[i] <= Y_MAX) && (polygon[i+2] > Y_MAX)){
			//inside-outside = save only new vertex;
			int new_x = ol.new_x(i-1, i+1, Y_MAX);
			ol.insert(new_x, Y_MAX);
		}
		else if((polygon[i] > Y_MAX) && (polygon[i+2] <= Y_MAX)){
			//outside-inside = save new vertex and second vertex;
			int new_x = ol.new_x(i-1, i+1, Y_MAX);
			ol.insert(new_x, Y_MAX);
			ol.insert(polygon[i+1], polygon[i+2]);
		}
	}


		for (int i = 0; i <=ol.count_and_renew(); i = i+2)
			cout<<"\n("<<polygon[i]<<","<<polygon[i+1]<<")";

	/*now just plot the polygon coordinates*/
	getch();
	return 0;
}