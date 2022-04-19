#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define M 100

int stack[M];
char infix[M];
char postfix[M];
int top=-1;

void push(int ch){
	if(top < M-1){
		top=top+1;
		stack[top]=ch;
	}
	else
	printf("Stack is full");
}

int pop(){
	int c;
	if(top < 0){
		printf("Stack is empty");
	}
	else{
		c=stack[top];
		top=top-1;
	}
	return c;
}

int isEmpty(){
	if(top < 0)
    	return 1;
	else
	    return 0;
}

int isFull(){
	if(top == M-1)
	   return 1;
	else 
	   return 0;
}

int precedence(char symbol){
	switch(symbol){
		case'^':
			   return 3;
		case'*':
		case'/':
				return 2;
		case'+':
		case'-':
			   return 1;
		default:
			   return 0;
	}
}

void postfixconverter(){
	int i,j=0;
	char symbol,next;
	for(i=0; i<strlen(infix); i++){
		symbol=infix[i];
		
		switch(symbol){
			case'(':
				push(symbol);
				break;
			case')':
				while((next=pop() )!= '(')
				postfix[j++] = next;
				break;
			case'+':
			case'-':
			case'*':
			case'/':
			case'^':
			while(!isEmpty() && precedence(stack[top]) >= precedence(symbol))
		    postfix[j++] = pop();
			push(symbol);
			break;	
			default:
				postfix[j++]=symbol;
		}
	}

	while(!isEmpty()){
		postfix[j++]=pop();
	}
	postfix[j]='\0';
	
}

void print(){
	int i=0;
	printf("Postfix of infix expression : ");
	while(postfix[i]){
		printf("%c",postfix[i++]);
	}
	printf("\n");
}
int post_eval(){
	int i;
	int a,b;
	for(i=0;i<strlen(postfix);i++){
		if(postfix[i] >='0' && postfix[i] <='9')
		push(postfix[i] - '0');
		else{
			a=pop();
			b=pop();
			switch(postfix[i]){
				case'+':
					push(b+a);
					break;
				case'-':
					push(b-a);
					break;
				case'*':
					push(b*a);
					break;
				case'/':
					push(b/a);
					break;
				case'^':
					push(pow(b,a));
					break;
			}
		}
	}
	return pop();
}

int main(){
	int result;
	printf("Enter the inflix expression : ");
	gets(infix);
	postfixconverter();
	result=post_eval();
	print();
	printf("The result of the expression is : %d\n",result);
}
