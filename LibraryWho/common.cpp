//
//  common.cpp
//  LibraryWho
//
//  Created by Jiyuan Liu on 14/12/27.
//  Copyright (c) 2014年 Jiyuan Liu. All rights reserved.
//

#include "common.h"

bool Date::operator == (const Date& x) {
    bool equal = 1;
    equal = (this->year==x.year)&equal;
    equal = (this->month==x.month)&equal;
    equal = (this->day==x.day)&equal;
    return equal;
}

bool Date::operator != (const Date& x) {
    bool equal = 0;
    equal = (this->year!=x.year)|equal;
    equal = (this->month!=x.month)|equal;
    equal = (this->day!=x.day)|equal;
    return equal;
}

bool Date::operator <<(const string dataIn) {
    sscanf(dataIn.c_str(), "%hd-%hd-%hd", &year, &month, &day);
    if(year<1000 || year>2100)
        return 0;
    else if (month>12 || month<1)
        return 0;
    else if (day<1)
        return 0;
    bool leap = 0;
    if (year%4 == 0) {
        if (year%100 == 0) {
            if (year%400 == 0) {
                leap = 1;
            } else {
                leap = 0;
            }
        } else {
            leap = 1;
        }
    } else {
        leap = 0;
    }
    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day > 31) {
                return 0;
            } else {
                return 1;
            }
            break;
        case 2:
            if (leap) {
                if (day > 29) {
                    return 0;
                } else {
                    return 1;
                }
            } else {
                if (day > 28) {
                    return 0;
                } else {
                    return 1;
                }
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day > 30) {
                return 0;
            } else {
                return 1;
            }
            break;
            
        default:
            return 0;
    }
}

bool ISBN::operator ==(const ISBN& x) {
    bool equal = 1;
    equal = (this->group1==x.group1)&equal;
    equal = (this->group2==x.group2)&equal;
    equal = (this->group3==x.group3)&equal;
    equal = (this->group4==x.group4)&equal;
    equal = (this->group5==x.group5)&equal;
    return equal;
}

bool ISBN::operator !=(const ISBN& x) {
    bool equal = 0;
    equal = (this->group1!=x.group1)|equal;
    equal = (this->group2!=x.group2)|equal;
    equal = (this->group3!=x.group3)|equal;
    equal = (this->group4!=x.group4)|equal;
    equal = (this->group5!=x.group5)|equal;
    return equal;
}

void ISBN::operator >>(unsigned long long &isbnInt) {
    unsigned long long power = 1000000000000;
    isbnInt = 0;
    for (int i=0; i<group5s.length(); i++) {
        isbnInt += (group5s[i]-'0')*power;
        power = power/10;
    }
    for (int i=0; i<group4s.length(); i++) {
        isbnInt += (group4s[i]-'0')*power;
        power = power/10;
    }
    for (int i=0; i<group3s.length(); i++) {
        isbnInt += (group3s[i]-'0')*power;
        power = power/10;
    }
    for (int i=0; i<group2s.length(); i++) {
        isbnInt += (group2s[i]-'0')*power;
        power = power/10;
    }
    for (int i=0; i<group1s.length(); i++) {
        isbnInt += (group1s[i]-'0')*power;
        power = power/10;
    }
}

bool ISBN::operator <<(const string isbnIn) {
    size_t pos;
    size_t pos2;
    pos = isbnIn.find("-");
    group1s = isbnIn.substr(0,pos);
    pos2 = isbnIn.find("-", pos+1);
    group2s = isbnIn.substr(pos+1, pos2-pos-1);
    pos = pos2;
    pos2 = isbnIn.find("-", pos+1);
    group3s = isbnIn.substr(pos+1, pos2-pos-1);
    pos = pos2;
    pos2 = isbnIn.find("-", pos+1);
    group4s = isbnIn.substr(pos+1, pos2-pos-1);
    pos = pos2;
    group5s = isbnIn.substr(pos+1);
    group1 = stoi(group1s);
    group2 = stoi(group2s);
    group3 = stoi(group3s);
    group4 = stoi(group4s);
    group5 = stoi(group5s);
    if(group1 != 978 && group1 != 979) {
        return 0;
    }
    else {
        unsigned long count = 0;
        count = group1s.length()+group2s.length()+group3s.length()+group4s.length()+group5s.length();
        if (count != 13)
            return 0;
        int tmp = 0;
        count = 1;
        for (int i=0; i<group1s.length(); i++) {
            if (count%2) {
                tmp += group1s[i]-'0';
            } else {
                tmp += (group1s[i]-'0')*3;
            }
            count++;
        }
        for (int i=0; i<group2s.length(); i++) {
            if (count%2) {
                tmp += group2s[i]-'0';
            } else {
                tmp += (group2s[i]-'0')*3;
            }
            count++;
        }
        for (int i=0; i<group3s.length(); i++) {
            if (count%2) {
                tmp += group3s[i]-'0';
            } else {
                tmp += (group3s[i]-'0')*3;
            }
            count++;
        }
        for (int i=0; i<group4s.length(); i++) {
            if (count%2) {
                tmp += group4s[i]-'0';
            } else {
                tmp += (group4s[i]-'0')*3;
            }
            count++;
        }
        tmp = (10-tmp%10)%10;
        if (tmp != group5)
            return 0;
        else
            return 1;
    }
}
