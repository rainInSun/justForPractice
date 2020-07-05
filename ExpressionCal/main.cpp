#include <QCoreApplication>
#include <QDebug>

#include <string>
#include <stack>
#include <vector>
#include <sstream>


int getIndex(char theta)   //获取theta所对应的索引
{
    int index = -1;
    switch (theta)
    {
    case '+':
        index = 0;
        break;
    case '-':
        index = 1;
        break;
    case '*':
        index = 2;
        break;
    case '/':
        index = 3;
        break;
    case '(':
        index = 4;
        break;
    case ')':
        index = 5;
        break;
    case '#':
        index = 6;
    default:break;
    }
    return index;
}

char getPriority(char theta1, char theta2)   //获取theta1与theta2之间的优先级
{
    const char priority[][7] =     //算符间的优先级关系
    {
        { '>','>','<','<','<','>','>' },
        { '>','>','<','<','<','>','>' },
        { '>','>','>','>','<','>','>' },
        { '>','>','>','>','<','>','>' },
        { '<','<','<','<','<','=','0' },
        { '>','>','>','>','0','>','>' },
        { '<','<','<','<','<','0','=' },
    };

    int index1 = getIndex(theta1);
    int index2 = getIndex(theta2);
    return priority[index1][index2];
}

bool isOperator(char inChar)
{
    int flag = getIndex(inChar);
    if (flag == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
};

double calResult(double lNum, char op, double rNum)
{
    double result = 0.0;
    switch (op)
    {
    case '+':
        result = lNum + rNum;
        break;
    case '-':
        result = lNum - rNum;
        break;
    case '*':
        result = lNum * rNum;
        break;
    case '/':
        if (rNum != 0)
            result = lNum / rNum;
        break;
    default:
        break;
    }
    return result;
};

double expressionCal(const std::string &expression)
{
    std::stack<double> numStack;
    std::stack<char> opStack;
    opStack.push('#');

    for (int i = 0; i < expression.length(); i++)
    {
       if (isOperator(expression[i]))
       {
           switch (getPriority(opStack.top(), expression[i]))
           {
           case '>':
               while (getPriority(opStack.top(), expression[i]) == '>')
               {
                   double rNum = numStack.top();
                   numStack.pop();
                   double lNum = numStack.top();
                   numStack.pop();
                   char op = opStack.top();
                   opStack.pop();
                   double tmpRes = calResult(lNum, op, rNum);
                   numStack.push(tmpRes);
               }
               break;
           case '<':
               opStack.push(expression[i]);
               break;
           case '=':
               opStack.pop();
               break;
           }
       }
       else
       {
            for (int j = i; j < expression.length(); j++)
            {
                if (isOperator(expression[j]))
                {
                    std::string tmpNum = expression.substr(i, j - i);
                    std::stringstream str(tmpNum);
                    double num;
                    str>>num;
                    numStack.push(num);

                    i = j - 1;
                    break;
                }
            }
       }
    }
    return numStack.top();
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string inStr = "11/1000#";

    double result = expressionCal(inStr);
    qDebug()<<result;

    return a.exec();
}
