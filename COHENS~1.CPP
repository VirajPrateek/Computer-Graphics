/*
/************ Cohen Sutherland Line Clipping Algorithm **************/
/*@Author : Kumar Prateek Viraj
* @DOSbox 0.74
* @FirstComplete : 06/02/2018
*
*/
/*We here are supposing that we're in 1970's */
#include<iostream.h>
#include<conio.h>
#include<graphics.h>

typedef struct point{
	int x;
	int y;
	int outcode[4];
}* p1, *p2;

		int x0, y0, x1, y1, x2, y2;
		int temp = 0;
		int accept = 0;
		/*  Because this dumb, century-old software
		   dont have fc**king boolean type!! */
		int left, top, right, bottom;

		struct point computeOutcode(struct point);
		/*Computes outcodes*/

		int acceptReject(struct point, struct point);
		/*Checks whether accept or reject*/

		int isInside(struct point);
		/*returns 0 if outcode passed is inside*/

		void computeIt(struct point, struct point);
		/*Computes the new coordinates*/

struct point computeOutcode(struct point p){
	/*This whole fuction can be shortened down to just 4 LOC */
   if(top>p.y)
		p.outcode[0] = 0 ;
   else p.outcode[0] = 1 ;
   if(bottom>p.y)
		p.outcode[1] = 1 ;
   else p.outcode[1] = 0 ;
   if(right>p.x)
		p.outcode[2] = 0 ;
   else p.outcode[2] = 1 ;
   if(left>p.x )
		p.outcode[3] = 1 ;
   else p.outcode[3] = 0 ;
return p;

}
int acceptReject(struct point p1, struct point p2){
temp = 0;
 for(int i=0; i<4; i++){
	if( (p1.outcode[i] & p2.outcode[i]) == 0)
		temp++;
  }
return temp;
}

int isInside(struct point p){
temp = 0;
	for(int i=0; i<4; i++)
		temp += p.outcode[i];
	if(temp == 0)
		return 0;
	else
		 return 1;
}

void check(int x, int y){
	/*Can be shortened by atleast 1 LOC */
	if((left <= x <= right) &&
		(bottom <= y <= top)){
			accept = 1 ;
	}
}

void computeIt(struct point p1, struct point p2){
do{
	if (p1.outcode[0] == 1){
		x0 = p1.x +((p2.x - p1.x)*(top - p1.y)/(p2.y - p1.y));
		y0 = top;

	}
	if (p1.outcode[1] == 1){
		x0 = p1.x + ((p2.x - p1.x)*(bottom - p1.x)/(p2.y - p1.y));
		y0 = bottom;
	}
	if (p1.outcode[2] == 1){
		x0 = right;
		y0 = p1.y+ ((p2.y - p1.y)*(right - p1.x)/(p2.x - p1.x));
	}
	if (p1.outcode[3] == 1){
		x0 = top;
		y0 = p1.y + ((p2.y - p1.y)*(top - p1.x)/(p2.x - p1.x));
	}
	 check(x0, y0); //This and next line can be merged.
  }while(!accept);
}

int main(){
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
	struct point p1, p2;

	cout<<"left-top-right-bottom";
	cin>>left>>top>>right>>bottom;

	cout<<"\nCoordinate1:";
	cin>>p1.x>>p1.y;
	p1 = computeOutcode(p1);
	cout<<"\nCoordinate2:";
	cin>>p2.x>>p2.y;
	p2 = computeOutcode(p2);

	cout<<"Press any key to see the UNclipped figure: ";
	getch();
	clrscr();
	rectangle(left, top, right, bottom);
	line(p1.x, p1.y, p2.x, p2.y);

	cout<<"Press any key to run algorithm -";
	getch();
	clrscr();
	cout<<"Outcode for p1:	";
	for(int i=0; i<4; i++)
		cout<<p1.outcode[i];
	cout<<"\nOutcode for p2:	";
	for (i=0; i<4; i++)
		cout<<p2.outcode[i];

	x1 = p1.x;	//these I guess, are redundant.
	y1 = p1.y;	//But I'm afraid it won't work without 'em.
	x2 = p2.x;
	y2 = p2.y;

	if(acceptReject(p1, p2) < 4){
		cout<<"\n\n Trivially Rejected ";
		goto reject;
	}
	else if(!((isInside(p1)) && (isInside(p2)))){
									//both returned 0; inside
		cout<<"\n\nTrivially Accepted";
		goto accept;
	}
	else if(((isInside(p1)) || (isInside(p2)))){ //can be compacted
									// any one of them returned 1; outside
		cout<<"\nNeeds relocation";
		if(isInside(p1)){ //whether p1 needs relocation?
			computeIt(p1, p2);
			p1.x = x0 ;
			p1.y = y0;

		}
		if(isInside(p2)){//p2 needs relocation
			computeIt(p2, p1);
			p2.x = x0;
			p2.y = y0;

		}
	}

	cout<<"\nClipped point 1  "<<p1.x<<" and "<<p1.y;
	cout<<"\nClipped Point2 " <<p2.x<<" and "<<p2.y;
   /*get the canvas ready*/
	cout<<"\n\n\tPress any key for CLIPPED figure- ";
	getch();
	clrscr();

 /*It's SHOW-TIME*/
accept:
	line(p1.x, p1.y, p2.x, p2.y);
 reject:
	rectangle(left, top, right, bottom);

 getch();
return 0;
}
