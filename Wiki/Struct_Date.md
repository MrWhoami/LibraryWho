# Struct Date
## General Description
`struct Date` is used to store the date information with year, month and day. It is used in this project to store the date information such as borrow date, return date and so on.
## Location
`struct Date` is declared in **common.h** and is defined in **common.cpp**.
## Variables
    short year  
This variable is used to store the year information which must be between 1000 and 2100.  

    short month  
This variable is used to store the month information which must be between 1 and 12.    

    short day  
This variable is used to store the day information which must be between 1 and 31.  
## Operators
### ==
This operator is used to compare two Date. If they are the same, the operator will return true. Else, it will return false.  
### != 
Opposite to the operator '=='.  
### <<  
Change a string into a Date. If the string is an ISBN code, it will return true. Else, it will return false.  

    Example:  
    Date date1;  
    Date date2;  
    string a = "1995-06-03";  
    string b = "1995-06-03";  
    string c = "2222-22-22";  
    if(date1 << c) cout << 1;  
    else cout << 0;  
    date1 << a;  
    date2 << b;  
    if(date1 == date2) cout << 1;  
    else cout << 0;  
    if(date1 != date2) cout << 1;  
    else cout << 0;  
The expected out put is: `010`