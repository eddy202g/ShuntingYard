#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

#define size 20 //  Define the size of the stack
#define maxQueue 20 // define the size of any queues used

// Initialise stack variables
char stack[size];
int top;
char userInput;

// Function stubs
void convertInfixToPostfix();
void init(int top);
void push(char userInput);
char pop();
bool isEmptyStack();
bool isFullStack();
int prec(char symbol);

// Set up queue char arrays
char infix[30];
char output[30];

// Main function asks user if they wouold like to enter an expression.
// If yes, convertInfixToPostfix() function is called, if no 
// the program will end
int main()
{
	char option = ' '; // Store user input 

	// Get user inout and store in "option"
	cout << "\n> Would you like to enter an Expression?" << endl;
	cout << "> Enter 'y' if yes, or 'n' if no: " << endl;
	cin >> option;

	// While user wants to enter an expression, call function, else, end
	while (option == 'Y' || option == 'y')
	{
		convertInfixToPostfix();

		cout << endl << endl;

		cout << "\n> Would you like to enter another Expression?" << endl;
		cout << "> Enter 'y' if yes, or 'n' if no: " << endl;
		cin >> option;
	}



	cout << endl << endl << endl << endl << endl << endl;

	cout << "							GOODBYE";

	cin.get();
	cin.ignore();

}

// Main function initialises the top of the stack first. It then 
// prompts the user to enter in an expression, and gets the length of the 
// expression, splitting it into tokens. The tokens are then seperated between the 
// stack and the output queue, operators onto the stack and operands on the queue.
// The tokens are then sorted based on their presedence according to BODMAS, and finlly the 
// output stack is printed top the console window
void convertInfixToPostfix()
{
	// Initialise variables
	int i = 0;
	int j = 0;
	int length;
	char temp;

	init(top); // Initialise the value of the top of stack

			   // Get expression from user
	cout << "\nEnter an infix expression: ";
	cin >> infix;

	length = strlen(infix); // Get length of the expression

							// For the length of the expression, split up the characters and 
							// disperse them between stack and queue
	for (i = 0; i < length; i++)
	{
		// Add only numbers to output queue
		if (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '^' && infix[i] != ')' && infix[i] != '(')
		{
			output[j++] = infix[i];

		}
		// Anything else gets pushed onto the stack
		else
		{
			if (!isFullStack) //If there are no elements in the stack, the operator is added to it
			{
				push(infix[i]);

			}
			else
			{   //Operators or pushed or popped based on the order of precedence
				if (infix[i] != ')' && infix[i] != '(')
				{
					if (prec(infix[i]) <= prec(stack[top - 1]))
					{
						temp = pop();
						output[j++] = temp;
						push(infix[i]);

					}
					else
					{
						push(infix[i]);
					}
				}
				else
				{
					if (infix[i] == '(')
					{
						push(infix[i]);

					}
					if (infix[i] == ')')
					{
						temp = pop();
						while (temp != '(')
						{
							output[j++] = temp;
							temp = pop();
						}
					}
				}
			}
		}
	}

	// Print postfix expresssion
	while (!isEmptyStack())
	{
		output[j++] = pop();
	}
	cout << "\nthe infix expression is: " << output;
}

// Takes in user input as parameter, then pushes the data onto
// the stack, incrementing the value of the top as it goes
void push(char userInput)
{
	stack[top] = userInput;
	top++;
}

// Removes the data from the stack, decrementing the value of top
// as it goes
char pop()
{
	top--;
	return(stack[top]);
}

// Returns true if the stack is empty
bool isEmptyStack()
{
	if (top == 0)
		return 1;
	else
		return 0;
}

// Returns true if the stack is full
bool isFullStack() {

	if (top == 0)
		return 1;
	else
		return 0;
}

// Function to initialise the top of the stack
void init(int top)
{
	top = 0;
}

//Function to get the precedence of an operator based on BODMAS
int prec(char symbol)
{
	if (symbol == '(')
		return 0;
	if (symbol == ')')
		return 0;
	if (symbol == '+' || symbol == '-')
		return 1;
	if (symbol == '*' || symbol == '/')
		return 2;
	if (symbol == '^')
		return 3;
	return 0;
}