//
//  main.cpp
//  Math
//
//  Created by IV-an on 13.11.14.
//  Copyright (c) 2014 Альфа 3. All rights reserved.
//

#include <iostream>
#include "stdlib.h"
#include "string.h"

using namespace std;

// Random integer number from 0 to argument
int Random(int number)
{
    return (rand() % (number + 1));
}

// Constants for signs
const int sign_count = 4;
const int sum = 0;
const int dif = 1;
const int mult = 2;
const int divis = 3;
const string signs[] = {"+", "-", "*", "/"};

// Parent class
class Value
{
public:
    // Virtual method for getting value
    virtual float GetValue()
    {
        return -0.0;
    }
    // Virtual method for getting string
    virtual string GetString()
    {
        string answer = "|";
        return answer;
    }
    // Virtual method for setting value
    virtual void SetValue()
    {
    }
};

// The Number
// Child class of Value
// It has float value
class Number : public Value
{
private:
    // The value of number
    float value;
public:
    // Getting value
    virtual float GetValue()
    {
        return value;
    }
    // Getting string by value
    virtual string GetString()
    {
        return to_string(value);
    }
    // Setting value
    virtual void SetValue(float mean)
    {
        value = mean;
    }
    // Constructor
    Number(float number) : Value()
    {
        value = number;
    }
    
};

// The Variable
// Child class of Value
// Number with a name
class Variable : public Value
{
private:
    // The value of variable
    float value;
    // The name of variable
    string name;
public:
    // Getting value
    virtual float GetValue()
    {
        return value;
    }
    // Getting string by name
    virtual string GetString()
    {
        return name;
    }
    // Setting value
    virtual void SetValue(string title, float number)
    {
        value = number;
        name = title;
    }
    // Constructor
    Variable(string title, float number) : Value()
    {
        value = number;
        name = title;
    }
};

// The Expression
// Child class of Value
// Includes twe Values and operation by them
class Expression : public Value
{
private:
    // Type of operation
    int action;
    // Two arguments for operation
    Value * val1, * val2;
public:
    // Getting value by two arguments and type of operation
    virtual float GetValue()
    {
        float answer = 0.0;
        switch (action){
            case sum:{
                answer = val1->GetValue() + val2->GetValue();
            } break;
            case dif:{
                answer = val1->GetValue() - val2->GetValue();
            } break;
            case mult:{
                answer = val1->GetValue() * val2->GetValue();
            } break;
            case divis:{
                if (val2->GetValue() != 0.0)
                    answer = val1->GetValue() / val2->GetValue();
            } break;
        }
        return answer;
    }
    // Getting string by two arguments and type of operation
    virtual string GetString()
    {
        string answer = "";
        answer = "(" + val1->GetString() + signs[action] + val2->GetString() + ")";
        return answer;
    }
    // Setting value
    virtual void SetValue(Value * a, Value * b, int type)
    {
        if (val1 != a){
            delete val1;
            val1 = a;
        }
        if (val2 != b){
            delete val2;
            val2 = b;
        }
        action = type;
    }
    // Constructor by two arguments and type of operation
    Expression(Value * a, Value * b, int type) : Value()
    {
        val1 = a;
        val2 = b;
        action = type;
    }
    // Destructor for deleting two arguments
    ~Expression()
    {
        delete val1;
        delete val2;
    }
    
};

// Constructor for Value by depth of expression
Value * SetLongValue(int depth)
{
    Value * answer;
    if (depth > 0){
        answer = new Expression(SetLongValue(depth - 1), SetLongValue(depth - 1), Random(sign_count - 1));
    }else{
        answer = new Number((float)(Random(10) / 10.0));
    }
    return answer;
}

// Constructor for Value by depth of expression
Value * SetLongValueVars(int depth, Variable var0, Variable var1)
{
    Value * answer;
    if (depth > 0){
        answer = new Expression(SetLongValue(depth - 1), SetLongValue(depth - 1), Random(sign_count - 1));
    }else{
        switch (Random(2)) {
            case (1):{
                answer = &var0;
            } break;
            case (2):{
                answer = &var1;
            } break;
            default:{
                answer = new Number((float)(Random(10) / 10.0));
            } break;
        }
    }
    return answer;
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    Value * first;
    //first = SetLongValue(5);
    Value *a, *b;
    a = new Number(2.0);
    b = new Variable("x", 3.141596);
    first = new Expression(a, b, divis);
    cout << (first->GetString()) << " = " << (first->GetValue()) << "\n";
    //cout << (b->GetString()) << " = " << (b->GetValue()) << "\n";
    std::cout << "Hello, World!\n";
    return 0;
}



