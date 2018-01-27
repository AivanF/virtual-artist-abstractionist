//
//  mem.cpp
//  Math expression creator.
//  Classes implementation.
//
//  Created by Aivan on 15.12.14.
//  Copyright (c) 2014 AivanF. All rights reserved.
//

#include <string>
#include <iostream>
#include <vector>
#include "mem.h"


namespace mem {
    
#pragma mark - Pool class
    
    vector<Value*> Pool::_pool;
    
    void Pool::add(Value *value) {
        for (int i = 0; i < Pool::_pool.size(); i++)
            if (value == Pool::_pool[i])
                return;
        Pool::_pool.push_back(value);
    }
    
    void Pool::clear() {
        for (int i = 0; i < Pool::_pool.size(); i++)
            delete Pool::_pool[i];
        Pool::_pool.clear();
    }
    
    
#pragma mark - Value class
    
    type_value Value::GetValue() {
        return -0.0;
    }
    
    string Value::GetString() {
        string answer = "|";
        return answer;
    }
    
    void Value::SetValue(type_value mean) {
        // for overriding
    }
    
    Value::~Value() {
        // for overriding
    }
    
    
#pragma mark - Number class
    
    type_value Number::GetValue() {
        return value;
    }
    
    string Number::GetString() {
        return to_string(value);
    }
    
    void Number::SetValue(type_value mean) {
        value = mean;
    }
    
    type_value Number::ReturnValue() {
        return GetValue();
    }
    
    Number::Number(type_value mean) : Value() {
        value = mean;
        
        Pool::add(this);
        _nums++;
    }
    
    Number::~Number() {
        _nums--;
    }
    
    
#pragma mark - Variable class
    
    type_value Variable::GetValue() {
        return *value;
    }
    
    string Variable::GetString() {
        return name;
    }
    
    void Variable::SetValue(string title, type_value *number) {
        value = number;
        name = title;
    }
    
    type_value Variable::ReturnValue() {
        return GetValue();
    }
    
    Variable::Variable(string title, type_value *number) : Value() {
        value = number;
        name = title;
        
        Pool::add(this);
        _vars++;
    }
    
    Variable::~Variable() {
        _vars--;
    }
    
    
#pragma mark - Expression class
    
    type_value Expression::GetValue() {
        type_value answer = 0.0;
        switch (action) {
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
            case sinus:{
                answer = sin(val1->GetValue() + val2->GetValue());
            } break;
            case cosin:{
                answer = cos(val1->GetValue() * val2->GetValue());
            } break;
        }
        return answer;
    }
    
    string Expression::GetString() {
        string answer = "?";
        switch (action) {
            case sum: case dif: case divis: case mult:{
                answer = "(" + val1->GetString() + funcs[action] + val2->GetString() + ")";
            }break;
            case sinus: case cosin:{
                answer = funcs[action] + "(" + val1->GetString() + "+" + val2->GetString() + ")";
            } break;
        }
        return answer;
    }
    
    void Expression::SetValue(Value *a, Value *b, int type) {
        if (val1 != a) {
            delete val1;
            val1 = a;
        }
        if (val2 != b) {
            delete val2;
            val2 = b;
        }
        action = type;
    }
    
    Expression::Expression(Value *a, Value *b, int type) : Value() {
        val1 = a;
        val2 = b;
        action = type;
        
        Pool::add(this);
        _exps++;
    }
    
    Expression::~Expression() {
//        delete val1;
//        delete val2;
        _exps--;
    };
    
    
#pragma mark - Some functions
    
    int Random(int number) {
        return (rand() % (number + 1));
    }
    
    Value *SetDeepValue(int depth) {
        Value *answer;
        if (depth > 0) {
            answer = new Expression(SetDeepValue(depth - 1), SetDeepValue(depth - 1), Random(func_count - 3));
        } else {
            answer = new Number((type_value)((Random(100) + 1) / 100.0));
        }
        return answer;
    }
    
    Value *SetDeepValueVars(int depth, Value *var0, Value *var1) {
        Value *answer;
        if (depth > 0) {
            answer = new Expression(SetDeepValueVars(depth - 1, var0, var1),
                                    SetDeepValueVars(depth - 1, var0, var1),
                                    Random(func_count - 1));
        } else {
            switch (Random(4)) {
                case (0):{
                    answer = var0;
                } break;
                case (1):{
                    answer = var1;
                } break;
                default:{
                    answer = new Number((type_value)((Random(100) + 1) / 100.0));
                } break;
            }
        }
        return answer;
    }
    
    Value *SetDeepValueVarsMany(int depth, Value *var0, Value *var1, Value *var2) {
        Value *answer;
        if (depth > 0) {
            answer = new Expression(SetDeepValueVarsMany(depth - 1, var0, var1, var2),
                                    SetDeepValueVarsMany(depth - 1, var0, var1, var2),
                                    Random(func_count - 1));
        } else {
            switch (Random(4)) {
                case 0:{
                    answer = var0;
                } break;
                case 1:{
                    answer = var1;
                } break;
                case 2:{
                    answer = var2;
                } break;
                default:{
                    answer = new Number((type_value)((Random(100) + 1) / 100.0));
                } break;
            }
        }
        return answer;
    }
    
    void clearPool() {
        Pool::clear();
    }
    
    void printCounts() {
        cout << "Numbers: " << _nums << ".\n";
        cout << "Variables: " << _vars << ".\n";
        cout << "Expressions: " << _exps << ".\n";
    }
}
