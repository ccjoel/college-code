#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <cctype>
using namespace std;

#include <ctype.h>

//function declarations
string postfix (string);
int    posteval(string);

//start main
int main()
{
   char again;
   cout << "Este programa acepta una expresion en infijo "
        << "y devuelve equivalente en posfijo\n" << endl;

      string infixExp; // expresion infijo
      cout << "Favor entrar una expresion en infijo: ";
      cin >> infixExp;
      cout << endl;

      string post = postfix(infixExp);
      
      cout << "La expresion en posfijo es: "
         << post << endl;
      
      int result = posteval(post);

      cout<<"El resultado es: "<<result<<endl;
   system ("pause");
   return 0;
}

//Function definitions

//Postfix: return a string of the infix arithmetic equiation in postfix
string postfix (string infixExp)
{
   stack <char> opStack;
   char token, topToken;
   string postfixExp;
   const string BLANK = " ";
   for (int i = 0; i < infixExp.length(); i++)
   {
      token = infixExp[i];
      switch (token)
      {
         case ' ' : break;
         case '(' : opStack.push(token);
                    break;
         case ')' : for ( ; ; )
                    {
                       assert (!opStack.empty());
                       topToken = opStack.top();
                       opStack.pop();
                       if (topToken == '(')
                       {
                          break;
                       }
                       postfixExp.append(BLANK + topToken);
                    }
                    break;
         case '+' : case '-' : case '*' :
         case '/' : case '%' :  
                    for ( ; ; )
                    {
                       if (opStack.empty() || opStack.top() == '(' ||
                          (token == '*' || token == '/' || token == '%') &&
                          (opStack.top() == '+' || opStack.top() == '-'))
                       {
                          opStack.push(token);
                          break;
                       }
                       else
                       {
                          topToken = opStack.top();
                          opStack.pop();
                          postfixExp.append(BLANK + topToken);
                       }
                    }
                    break;
         default : // operando
                   postfixExp.append(BLANK + token);
                   for ( ; ; )
                   {
                      if (!isalnum(infixExp[i+1]))
                      break;
                      i++;
                      token = infixExp[i];
                      postfixExp.append(1, token);
                   }
      }
   }
   

   for ( ; ; )
   {
      if (opStack.empty())
      {
         break;
      }
      topToken = opStack.top();
      opStack.pop();
      if (topToken != '(')
      {
         postfixExp.append(BLANK + topToken);
      }
      else
      {
         cout << " Error en la expresion infijo";
         break;
      }
   }
   return postfixExp;
}

//posteval: evaluates postfix expressions
int posteval( string post )
{
    stack<int> s;
    int result;
    int value;
    
    for(int i=0; i < post.length() ; i++){
        char token = post[i];
        if( token == ' ')
            ;
        else if( isdigit(token) ){
           int newtoken = '0' - token;
           newtoken = newtoken * -1;
           s.push(newtoken);}
        else{
            int rightop = s.top(); 
            s.pop();
            int leftop =  s.top();
            s.pop();
            
            switch (token){
               case '*':
                 result = leftop * rightop;
                 break;
               case '/':
                 result = leftop / rightop;
                 break;
               case '+':
                 result = leftop + rightop;
                 break;
               case '-':
                 result = leftop - rightop;
                 break;
               default:
                 cout<<"Super error\n";
            }
            s.push(result);
        }
    }
    value = s.top();
    return value;
}
