# Class Reader
## General Description  
`class Reader` is used to storage the whole information of one reader.
## Location
`class Reader` is declared in **reader.h** and is defined in **reader.cpp**.
## Variables
    private:  
    BookBorrowed *bookBorrowed  
    unsigned rid  
    int borrowed  
    
    public:  
    string name
    int level
    string email  
Most of them just storage the information just like their name. Each user `rid` is unique. The integer `borrowed` storages the history number. The integer `level` shows the max book number the reader can borrow. 
## Function  
    void importData(ISBN*, Data*, bool*, int, int)
    unsigned gerRid()
    int getNumber()
    int getBorrowed()
    int getBook(ISBN* &)
    int getData(Date* &)
    int getRenew(bool* &)
    int borrowNew(ISBN)
    int returnOld(ISBN)
    int renewBook(ISBN)  
### Backup Functions  
`importData` is used to restore the previous data.
`getBook`,`getData`,`getRenew`is used to backup data.
### About Reader
`getRid` returns the rid of this reader.
`getNumber` returns the book number the reader is reading.  
`getBorrowed` returns the history number.  
`borrowNew`,`returnOld`,`renewBook` do the jobs just like their function name.