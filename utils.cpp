#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "stack.hpp"

using namespace std;

bool checkParentheses(const string& line, const vector<pair<char,char>>& pairs){
    //TODO
    Stack<char> parentheses;
    char get_closer[256]={};
    char get_opener[256]={};
    for(long unsigned int i=0;i<pairs.size();i++)
    {
        get_closer[pairs[i].first] = pairs[i].second;
        get_opener[pairs[i].second] = pairs[i].first;
        
        // not parenthese -> get_closer is zero and get_opener is also zero;
        // opening parenthese -> get_closer is nonzero;
        // closing parenthese -> get_closer is zero;
    }
    // have to consider the case of a pair with same first val and second val;
    // for immediately checking closing parenthese -> hash
    
    for(long unsigned int i=0;i<line.length();i++)
    {
        char tmp = line[i];
        if(get_closer[tmp]==0 && get_opener[tmp]==0) continue;//not parenthese
        
        if(parentheses.isEmpty())
        {
            if(get_closer[tmp]==0) return false;//closing parenthese.
            parentheses.push(tmp);//opening parenthese.
        }
        else
        {
            if(tmp == get_closer[parentheses.top()]) parentheses.pop();//match with top
            else if(get_closer[tmp]) parentheses.push(tmp);//opening parenthese.
            else if(get_closer[tmp]==0) return false;//closing parenthese.
        }
    }
    return parentheses.isEmpty();//empty->true, not empty->false;
}

float calculate(const string& line){
    //TODO
    Stack<float> numbers;
    Stack<char> operators;
    string reverse_polish;
    if(line=="" || line==" ") return 0;
    // convert to RPN
    int index = 0;
    do
    {
        if('0' <= line[index] && line[index] <= '9' || line[index]=='.')
        {
            // operand
            do
            {
                reverse_polish += line[index++];
            }while(index < line.length() && ('0' <= line[index] && line[index] <= '9' || line[index]=='.'));
            // when the above 'do - while' ends, 'index' indicates an operator or is equal to 'line.lenght()'.
            reverse_polish += ' '; // insert blank between two numbers
        }
        else
        {
            // operator
            if((line[index]=='+' || line[index]=='-') && (index==0 || line[index-1]=='+' || line[index-1]=='-' || line[index-1]=='*' || line[index-1]=='/' || line[index-1]=='('))
            {
                // unary operator +, -
                // plus : binary->'+', unary->'#'
                // minus : binary->'-', unary->'$'
                operators.push((line[index]=='+')*'#' + (line[index]=='-')*'$');
            }
            else if(operators.isEmpty()) operators.push(line[index]);
            else
            {
                switch (line[index])
                {
                case '(':
                    operators.push('(');
                    break;
                case ')':
                    while(operators.top()!='(') reverse_polish += operators.pop();
                    operators.pop();
                    break;
                case '*':
                case '/':
                    while(!operators.isEmpty() && operators.top()!='(' && (operators.top()=='*' || operators.top()=='/')) reverse_polish += operators.pop();
                    operators.push(line[index]);
                    break;
                case '+':
                case '-':
                    while(!operators.isEmpty() && operators.top()!='(') reverse_polish += operators.pop();
                    operators.push(line[index]);
                    break;
                
                default:
                    break;
                }
            }
            index++;
        }
        
    }while(index < line.length());
    while(!operators.isEmpty()) reverse_polish += operators.pop();
    // cout<<reverse_polish<<endl;

    // NaN inf do not occur;
    // calculate the RPN;
    index = 0;
    do
    {
        if('0' <= reverse_polish[index] && reverse_polish[index] <= '9' || reverse_polish[index]=='.')
        {
            // operand
            string tmp = "";
            do
            {
                tmp += reverse_polish[index++];
            }while(index < reverse_polish.length() && reverse_polish[index]!=' ');
            //ends with ' ';
            numbers.push(stof(tmp));
        }
        else
        {
            // operator
            float res;
            float operand2 = numbers.pop();
            float operand1;
            switch (reverse_polish[index])
            {
                case '#':
                    res = operand2;
                    break;
                case '$':
                    res = - operand2;
                    break;
                case '+':
                    operand1 = numbers.pop();
                    res = operand1 + operand2;
                    break;
                case '-':
                    operand1 = numbers.pop();
                    res = operand1 - operand2;
                    break;
                case '*':
                    operand1 = numbers.pop();
                    res = operand1 * operand2;
                    break;
                case '/':
                    operand1 = numbers.pop();
                    res = operand1 / operand2;
                    break;
                
                default:
                    break;
            }
            // ends with '+', '-', '*', '/';
            numbers.push(res);
        }
        index++;// indicate digit
        //serial two or more numbers are valid for RPN unlike infix
    }while(index < reverse_polish.length());

    return numbers.pop();
}

