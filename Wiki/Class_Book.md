#Class Book
## General Description  
Class Book is used to store book information.
## Location
Class Book is declared in book.h and defined in book.cpp.  
## Member Variables
    private:  
    ISBN isbn;  
    BorrowNode* readers;  
    
    public:  
    string name;  
    string author;  
    Date date;  
    unsigned price;  
    int quantity;  
#### ISBN isbn
The ISBN code of the book.  
#### BorrowNode* readers
The readers of the book.
#### string name
The name of the book.  
#### string author  
The author of the book.  
#### Date date
The publication date of the book.  
#### unsigned price
The price of the book with two place decimal. The point is ignored.  
#### int quantity
The inventory(not borrowed) of the book.  
## Member Function
    publish:  
    Book(ISBN isbnIn);  
    ~Book();  
    int getTotal();  
    int getReaderNum();  
    int getReaders(unsigned* &rid);  
    int borrowBook(unsigned rid);  
    int returnBook(unsigned rid);  
    void inputPrice(double priceIn);  
    double outputPrice();  
    ISBN getISBN();  
#### Book(ISBN isbnIn)
The constructor of Class Book. A object must be created with an ISBN code.  
#### ~Book()  
The destructor of Class Book.  
#### int getTotal()  
To get the total number of inventor, including the borrowed books.  
#### int getReaderNum()  
To get the reader number of the book.  
#### int getReaders(unsigned* &rid)  
To get the rids of readers of the book. The parameter is the head pointer of a static linked list of the unsigned type. The function will return the reader number.  
#### int borrowBook(unsigned rid)  
The reader with the RID inputed in parameter borrow a book. The return number 0 means the book is borrowed successfully. The number 1 means the inventory is 0. The number 2 means the reader has already borrowed the book.  
#### int returnBook(unsigned rid)  
The reader with the RID inputed in parameter return a book. The return number 0 means the book is borrowed successfully. The number 1 means the reader hasn't borrowed the book yet.  
#### void inputPrice(double priceIn)
To input the price with a double type parameter.  
#### double outputPrice()  
To output the price in double type.  
#### ISBN getISBN()
To get the ISBN code of the book.  