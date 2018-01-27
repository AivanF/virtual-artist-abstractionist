/*
 mem.h
 
 Math expression creator.
 Namespace and classes definition.
 
 Created by Aivan on 15.12.14.
 Copyright AivanF. (c) 2014-2018
 
 This code is provided 'as-is', without any express or implied warranty.
 You may not hold the author liable.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:
 
 1	The origin of this code must not be misrepresented. You must not claim
 that you wrote the original software. When use the code, you must give
 appropriate credit, provide a link to this license, and indicate if changes were made.
 
 2	Altered source versions must be plainly marked as such, and must not be misrepresented
 as being the original software.
 
 3	This notice may not be removed or altered from any source distribution.
 */


#ifndef Math_mem__h
#define Math_mem__h

#include <string.h>
#include <stdlib.h>
#include <vector>
#include <cmath>


using namespace std;

namespace mem {
    // Random integer number from 0 to argument
    int Random(int number);
    
    const double Pi = 3.1415926535;
    
    // Constants for funcions
    const int func_count = 6;
    const int sum = 0;
    const int dif = 1;
    const int mult = 2;
    const int divis = 3;
    const int sinus = 4;
    const int cosin = 5;
    const string funcs[] = {"+", "-", "*", "/", "sin", "cos"};
    
    static int _exps = 0;
    static int _vars = 0;
    static int _nums = 0;
    
    typedef float type_value;
    
    /// Parent abstract class.
    class Value {
    public:
        /// Returns calculated value.
        virtual type_value GetValue();
        
        /// Virtual method for getting string.
        virtual string GetString();
        
        /// Virtual method for setting value.
        virtual void SetValue(type_value mean);
        
        virtual ~Value();
    };
    
    
    /// Child class of Value.
    /// Holds a constant number.
    class Number : public Value {
    private:
        /// The value of number
        type_value value;
        
    public:
        /// Returns calculated value.
        virtual type_value GetValue();
        
        /// Returns string with value,
        virtual string GetString();
        
        /// Sets value.
        virtual void SetValue(type_value mean);
        
        /// Returs saved value.
        virtual type_value ReturnValue();
        
        /// Constructor.
        Number(type_value mean);
        
        /// Destructor.
        ~Number();
    };
    
    
    /// Tha Variable.
    /// Child class of Value.
    /// Stores a pointer to number and a name.
    class Variable : public Value {
    private:
        /// The value of variable.
        type_value *value;
        //// The name of variable.
        string name;
        
    public:
        /// Returns calculated value.
        virtual type_value GetValue();
        
        /// Returns string with name.
        virtual string GetString();
        
        /// Sets value.
        virtual void SetValue(string title, type_value *number);
        
        /// Returs saved value.
        virtual type_value ReturnValue();
        
        /// Constructor.
        Variable(string title, type_value *number);
        
        /// Destructor.
        ~Variable();
    };
    
    
    /// The Expression.
    /// Child class of Value.
    /// Includes two Values and operation for them.
    class Expression : public Value {
    private:
        /// Type of operation.
        int action;
        /// Two arguments for operation.
        Value *val1, *val2;
        
    public:
        /// Returns value calculated by two arguments and operation.
        virtual type_value GetValue();
        
        /// Returns string by two arguments and type of operation.
        virtual string GetString();
        
        /// Sets Expression values.
        virtual void SetValue(Value *a, Value *b, int type);
        
        /// Constructor by two arguments and type of operation.
        Expression(Value *a, Value *b, int type);
        
        /// Destructor for deleting two arguments.
        ~Expression();
    };
    
    
    /// Static class for clearing memory.
    class Pool {
    private:
        static vector<Value*> _pool;
        
    public:
        /// Tries to add new value.
        static void add(Value *value);
        
        /// Deletes all saved values.
        static void clear();
    };
    
    
    /// Creates Value by depth of expression.
    Value *SetDeepValue(int depth);
    
    /// Creates Value by depth of expression with Variables.
    Value *SetDeepValueVars(int depth, Value *var0, Value *var1);
    
    /// Creates Value by depth of expression with many Variables.
    Value *SetDeepValueVarsMany(int depth, Value *var0, Value *var1, Value *var2);
    
    /// Clears memory.
    void clearPool();
    
    /// Prints objects counts to check memory.
    void printCounts();
}

#endif
