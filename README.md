# toy-Compile

It is a toy compiler build for language Ciring with llvm to explore how compiler work.

# Syntax

## Variable declare

There are two types 32-bit signed integer and double. You can declare varible with fallowing syntax:

```c
int varName;
double varName;
```

You can also give it initial value by using assign operator `=`

```c
int varName = 10; // init variable with value 10
double varName = 0.0; // init variable with value 0.0
```

Or with `argName[i]` to declare an array with length i.

Note: You couldn't declare multiple variable with same type seprated by comma as C can:

```c
int var1, var2; // Invalid
```

Plan to support in future.

Note2: You can't assign an expression to global variable.

## Operator

Currently support:

* Binary operator
  * `+` for add
  * `-` for sub
  * `*` for mul
  * `/` for div
  * `=` for assign
  * `[i]` for access i-th element in an array
* Unaray operator
  * `-` 
  * `!` for logical not  
* Logical operator
  * `>` for greater
  * `>=` for greater and equal
  * `<` for less
  * `<=` for less and equal
  * `==` for equal
  * `!=` for unequal

## Loop

Who need loops when you have recursion?

```c
// Don't:
for (int i = 0; i < 10; i ++)

// instead
int func(int i){
    if (i < 10)
        return func(i - 1) + i;
}
```

## Function

To declare a function, just follow syntax below:

```c
return-type funcName(argType argName, argType argName....) {
    function Body.
}
```

Or you may also declare the function forward, in forward declaration you may omit the argName.

```c
return-type funcName(argType, argType); // forward declare
```

## Comment

You're code should be self-document enough, hence Ciring doesn't provide comment.