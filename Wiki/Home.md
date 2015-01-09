# LibraryWho
## General Description
This is a command line library management tool. It can manage the books in the library and the readers reading here.
## Function Description
### Book Management
1. Add new books through command line;
2. Import book list through files in special format;
3. Find a book through its ISBN, title, writer, publish date;
4. Find the number of books in this library; 
8. Export the book list；  
9. Backup the library book information.

### Reader Management
1. Add new readers through command line;
2. Import reader list through files in special format;
3. Find a reader through its name, borrowed books;
4. Judge whether the reader has broken the rule;
5. Calculate the return date；  
6. Renew the return date;
5. Get the books the reader borrowed;
6. Find the number of readers in this library;
7. Export the reader list;  
8. Backup the library reader information.

## Reference
### Environment Recommend
+ Architectures:    Standard Architectures (64-bit Intel)(x86_64)
+ Base SDK:         OS X 10.10
+ Compiler:         Apple LLVM 6.0
+ Dialect:          GNU++11
+ Standard Library: linc++

### Class List
+ Class Book
+ Class Reader
+ Class Library
+ Class BorrowNode
+ Class Queue
+ Class BookBorrowed
+ Struct ISBN
+ Struct Date
+ Sturct ReaderNode
+ Struct BookNode