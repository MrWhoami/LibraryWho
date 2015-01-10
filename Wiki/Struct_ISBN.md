# Struct ISBN
## General Description
`struct ISBN` is used to store the ISBN code of a book. ISBN is the short of International Standard Book Number. For more information about the ISBN, click [here](http://en.wikipedia.org/wiki/International_Standard_Book_Number).
## Location
`struct ISBN` is declared  in **common.h** and is defined in **common.cpp**. 
## Variables
    string group1s  
    string group2s  
    string group3s  
    string group4s
    string group5s
Those five variables are used to store the five parts of an ISBN code.
## Operators
### ==
This operator is used to compare two ISBN code. If they are the same, the operator will return true. Else, it will return false.   
### !=
Opposite to the operator '=='.  
### >>  
Change a ISBN code into a unsigned int. It will return nothing but change the unsigned int value.  
### <<
Change a string into a ISBN. If the string is an ISBN code, it will return true. Else, it will return false.  

    Example:  
    ISBN isbn1;  
    ISBN isbn2;  
    string a = "978-7-100-08905-0";  
    string b = "978-7-100-08905-0";  
    string c = "hey-7-100-08905-0";  
    if(isbn1 << c) cout << 1;  
    else cout << 0;  
    isbn1 << a;  
    isbn2 << b;  
    if(isbn1 == isbn2) cout << 1;  
    else cout << 0;  
    if(isbn1 != isbn2) cout << 1;  
    else cout << 0;  

The expected output is: `010`  
### =  
Assign the ISBN value from another ISBN code.  