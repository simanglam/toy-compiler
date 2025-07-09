# toy-Compile

It is a toy compiler build with llvm to explore how compiler work.

# Syntax

## Variable declare

There are only one type 32-bit signed integer. To declare a variable with this type, just fallow syntax below.

```c
int varName;
```

You can also give it initial value by using assign operator `=`

```c
int varName = 10; // init variable with value 10
```

Note: you can only use letter as variable name. (Somebody didn't write Tonkenizer properly)

## Operator

Current support `+` `-` `*` `/` `=` `(` `)`. No unary operator for now, planning to implement.

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