#include "palloc.h"
#include<stdio.h>

int main(){
	//*********************
	init_list();
	printf("Empty Heap:\n");
	walk();
	//*********************
	void *p = palloc(10);
	printf("One item:\n");
	printf("\tp = palloc(10)\n");
	walk();
	//*********************
	free(p);
	printf("-1 Item:\n");
	printf("\tfree(p)\n");
	walk();
	//*********************
	void *a = palloc(10);
	void *b = palloc(10);
	printf("2 Items:\n");
	printf("\ta = palloc(10)\n");
	printf("\tb = palloc(10)\n");
	walk();
	//*********************
	free(a);
	printf("Free/Alloc/Free:\n");
	printf("\tfree(a)\n");
	walk();
	//*********************
	void *c = palloc(5);
	printf("Worst Fit\n");
	printf("\tc = palloc(5)\n");
	walk();
	//*********************
	void *d = palloc(1000);
	printf("Big chunk\n");
	printf("\td = palloc(1000)\n");
	walk();
	//*********************
	void *e = palloc(2400);
	free(d);
	printf("Big gap\n");
	printf("\te = palloc(2400)\n");
	printf("\tfree(d)\n");
	walk();
	//*********************
	free(b);
	printf("Back Coalesce\n");
	printf("\tfree(b)\n");
	walk();
	//*********************
	void *f = palloc(800);
	printf("Slot in between\n");
	printf("\tf = palloc(800)\n");
	walk();
	//*********************
	void *g = palloc(10);
	printf("Worst fit 2\n");
	printf("\tg = palloc(10)\n");
	walk();
	//*********************
	void *h = palloc(500);
	void *i = palloc(180);
	printf("Alloc to Alloc\n");
	printf("\th = palloc(500)\n");
	printf("\ti = palloc(180)\n");
	walk();
	//*********************
	/*
	void *j = palloc(45);
	printf("All the way to the end\n");
	printf("\tj = palloc(45)\n");
	walk();*/
	//*********************
	void *k = palloc(72);
	printf("No more room\n");
	printf("\tk = palloc(7200)\n");
	walk();
	//*********************
	//a,b,d
	/*	
	printf("C:%p\n",c);
	printf("E:%p\n",e);
	printf("F:%p\n",f);
	printf("G:%p\n",g);
	printf("H:%p\n",h);
	printf("I:%p\n",i);
	printf("J:%p\n",j);*/
	printf("Spotty\n");
	printf("\tfree(f)\n");
	printf("\tfree(e)\n");
	printf("\tfree(h)\n");
	free(f);
	free(e);
	free(h);
	walk();
	return 0;
}	
