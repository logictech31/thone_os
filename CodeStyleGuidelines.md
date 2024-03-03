1. Methods must have Capital letters
2. Members which have 
3. Write functions/methods like this
```
// Function name and description if necessary
printf() {
    // code goes here
}
```
4. Information about the line goes above the code
```
foo() {
    // what the code does
    logic {
        the_code_(some_params, ...);
    }
}
```
5. structs/classes must be defined in Upper snake case like this =>
```
class Global_Descriptor_Table {
    // does something
}
```

6. To look clean, the class access specifiers must be defined like this
```
class C1 {
protected:
    method();
    
    class C2 {
    private:
        // something
    }
public:
    method(int params)
}
```

7. C++ Headers are declared with .hxx and files with .cxx for my code
-------------------------------------
Update this if necessary

Some tips listed in Bjarne Stroustrup's CPP book:
When you program, you create a concrete representation of ideas in your solutions to some problem. Let the structure of the prog reflect those ideas as directly as possible:
1. If you can think of "it" as a separate idea, make it a class
2. If you can think of "it" as a separate entity, make it an object of some class
3. If two classes have a common interface, make that interface an abstract class
4. If the implementations of two classes have something significant in common, make that commonality a base class
5. If a class is a container of objects, make it a template
6. If a fn implements an algorithm for a container, make it a template function implementing the algorithm for a family of containers
7. If a set of classes templates, etc. are logically related, place them in a common namespace

When you define either a class that does not implement a  math entity like a matrix or a complex num or low-level type such as a linked list:
1. Don't use global data (use members)
2. Don't use global functions
3. Don't use public data members
4. Don't use friends, except to avoid 1 and 3
5. Don't put a type"type field in a class; use virtual functions
6. Don't use inline functinos, except as a significant optimization