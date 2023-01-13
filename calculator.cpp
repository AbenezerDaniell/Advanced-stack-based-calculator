#include <iostream>
//we use cstdlib library to convert string into number
#include <cstdlib>
#include <vector>
#include <string>
//we use unordered map to store the presedence values of operators
#include <unordered_map>
using namespace std;
//================================================================
    // Implementation of stack using linked list
class Node { 
    public: 
        int value;
        Node* next;
    
        Node(int value) {
            this->value = value;
            next = nullptr;
        }
};


class Stack {
    private:
        Node* top;
        int length;

    public:
        Stack(int value) {
            Node* newNode = new Node(value);
            top = newNode;
            length = 1;
        }
       

        void printStack() {
            Node* temp = top;
            while (temp) {
                cout << temp->value;
                temp = temp->next;
            }
        }

        void getTop() {
            cout << "Top: " << top->value << endl;
        }

        void getlength() {
            cout << "length: " << length << endl;
        }

        void push(int value) {
            Node* newNode = new Node(value);
            newNode->next = top;
            top = newNode;
            length++;
        }

        Node* pop() {
            if(length == 0) return nullptr;

            Node* temp = top;
            top = top->next;
            temp->next = nullptr;

            length--;
            return temp;
        }
        
};
//==================================================================

// toknize the user input
vector<string> Tokenize(string & expression, unordered_map<string, int> & opMap)
{
    vector<string> tokens = {};
    string temp = "";
    for(char c : expression)
    {
        if( c == ' ') continue;
        else if( opMap.find(string(1, c)) != opMap.end())
        {
            if(temp != "")
                tokens.push_back(temp);
            temp = "";
            tokens.push_back(string(1, c));
        }
        else temp += c;
    }
    if(temp != "")
        tokens.push_back(temp);

    return tokens;
}
//change the Infix form of the toknized user input into Postfix
vector<string> InfixToPostfix(vector<string> & infix, unordered_map <string, int> & opMap)
{
    vector<string> postfix = {};
    vector<string> stack = { "("};
    infix.push_back(")");
    for(string token : infix)
    {
        //cout << token << endl;
        if(opMap.find(token) == opMap.end()) // oparand
            postfix.push_back(token);
        else if( token == "(")
            stack.push_back(token);
        else if (token == ")")
        {
            while(stack.back() != "(")
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            stack.pop_back();
        }
        else // operator
        {
            while(stack.size() > 0 && opMap[token] <= opMap[stack.back()])
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(token);
        }
    }
    
    return postfix;
}
// Calculate the Postfix form of expression and return the result
float CalculatePostfix(vector<string> & postfix, unordered_map<string, int> &opMap)
{
    vector<float> evaluationStack = {};
    for(string token : postfix)
    {
        if(opMap.find(token) != opMap.end())
        {
            float n1 = evaluationStack[evaluationStack.size() - 1]; 
            float n2 = evaluationStack[evaluationStack.size() - 2];

            switch(token[0])
            {
                case '+':
                    n2 = n2 + n1;
                    break;
                case '-':
                    n2 = n2 - n1;
                    break;
                case '*':
                    n2 = n2 * n1;
                    break;
                case '/':
                    n2 = n2 / n1;
                    break;
            }
            evaluationStack.pop_back();
            evaluationStack.pop_back();
            evaluationStack.push_back(n2);
        }
        else
        {
            evaluationStack.push_back(atof(token.c_str()));//convert string into number
            
        }
    }
    return evaluationStack[0];
}
//convert user decimal input into binary and return it
void DecimalToBinary(int value) {
    Stack *myStack = new Stack(value%2);
    value /= 2;
    //convert decimal into binary
    while(value != 0) {
        myStack->push(value % 2);
        value /= 2;
    }
    cout << endl
         << "Result: ";
    myStack->printStack();
   
}

int main()
{

    unordered_map<string, int> opMap = {
        { "*", 2},
        { "/", 2},
        { "+", 1},
        { "-", 1},
        { "(", -1},
        { ")", -1},
    };
    bool on = true;
    int choice;
    while(on) {
        
        cout <<endl<<endl<< "STACK CALCULATOR" << endl;
        cout << "**********************" << endl;
        cout << "CHOOSE CALCULATOR MODE:" << endl;
        cout<<"     1=> FOR STANDARD MODE"<<endl;
        cout<<"     2=> FOR PROGRAMMAR MODE"<<endl;
        cout << "     0=> TO EXIT" << endl;
        cout << ">>:";
        cin >> choice;
        switch (choice)
        {
        case 1:{ 
            string expression;
            cin.ignore(1, '\n');
            cout << "Enter Expression: ";
            getline(cin, expression);
            vector<string> tokens = Tokenize(expression, opMap); //infix : a * b
            tokens = InfixToPostfix(tokens, opMap); // postfix : a b *
            float result = CalculatePostfix(tokens, opMap);
            cout <<endl<<"Result:"<< result << endl;
            break;
        }
        case 2:{
            cout << "Decimal to Binary coverter"<<endl;
            cout << "Enter decimal value: ";
            int value;
            cin >> value;
            DecimalToBinary(value);
            break;
        }
        case 0:
        default:{
            on = false;
            break;
        }
        }
            }
            return 0;
}
