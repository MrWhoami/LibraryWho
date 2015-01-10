# Class BorrowNode
## General Description
Used in the `class Reader` to storage the borrowed books information.
## Location  
`class BorrowBode` is  declared in **reader.h** and is defined in **reader.cpp**.  
## Variables  
    public:
    ISBN theBook
    Date borrowDate
    bool renew
    BookBorrowed* nextBook  
Just like their names.  
## Function  
    Date returnDate()  
Return the expected latest return date.