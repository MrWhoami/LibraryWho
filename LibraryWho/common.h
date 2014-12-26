//
//  common.h
//  LibraryWho
//
//  Created by Whoami on 14/12/15.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#ifndef LibraryWho_common_h
#define LibraryWho_common_h

#include <string>
using namespace std;

#define DEFAULT_PATH "/Users/apple/Documents/LibraryWho/"

struct Date {
    short year;
    short month;
    short day;
    bool operator ==(const Date& x) {
        bool equal = 1;
        equal = (this->year==x.year)&equal;
        equal = (this->month==x.month)&equal;
        equal = (this->day==x.day)&equal;
        return equal;
    }
    bool operator !=(const Date& x) {
        bool equal = 0;
        equal = (this->year!=x.year)|equal;
        equal = (this->month!=x.month)|equal;
        equal = (this->day!=x.day)|equal;
        return equal;
    }
    bool operator <<(const string dataIn) {
        sscanf(dataIn.c_str(), "%hd-%hd-%hd", &year, &month, &day);
        if(year < 1000 || year > 2100)
            return 0;
        else
            return 1;
    }
};

struct ISBN {
    unsigned group1;
    unsigned group2;
    unsigned group3;
    unsigned group4;
    unsigned group5;
    bool operator ==(const ISBN& x) {
        bool equal = 1;
        equal = (this->group1==x.group1)&equal;
        equal = (this->group2==x.group2)&equal;
        equal = (this->group3==x.group3)&equal;
        equal = (this->group4==x.group4)&equal;
        equal = (this->group5==x.group5)&equal;
        return equal;
    }
    bool operator !=(const ISBN& x) {
        bool equal = 0;
        equal = (this->group1!=x.group1)|equal;
        equal = (this->group2!=x.group2)|equal;
        equal = (this->group3!=x.group3)|equal;
        equal = (this->group4!=x.group4)|equal;
        equal = (this->group5!=x.group5)|equal;
        return equal;
    }
    void operator >>(unsigned &isbnInt) {
        unsigned power = 10;
        unsigned powerTmp = 10;
        isbnInt = (unsigned)group5;
        isbnInt += (unsigned)group4*power;
        for (powerTmp=10; group4/powerTmp!=0; powerTmp=powerTmp*10) {
            power = power*10;
        }
        power = power*10;
        isbnInt += (unsigned)group3*power;
        for (powerTmp=10; group3/powerTmp!=0; powerTmp=powerTmp*10) {
            power = power*10;
        }
        power = power*10;
        isbnInt += (unsigned)group2*power;
        for (powerTmp=10; group2/powerTmp!=0; powerTmp=powerTmp*10) {
            power = power*10;
        }
        power = power*10;
        isbnInt += (unsigned)group1*power;
    }
    bool operator <<(const string isbnIn) {
        sscanf(isbnIn.c_str(), "%d-%d-%d-%d-%d", &group1, &group2, &group3, &group4, &group5);
        if(group1 != 978 | group1 != 979) {
            return 0;
        }
        else {
            int count = 0;
            unsigned power = 10;
            for (power=10; group1/power!=0; power=power*10) {
                count++;
            }
            count++;
            for (power=10; group2/power!=0; power=power*10) {
                count++;
            }
            count++;
            for (power=10; group3/power!=0; power=power*10) {
                count++;
            }
            count++;
            for (power=10; group4/power!=0; power=power*10) {
                count++;
            }
            count++;
            for (power=10; group5/power!=0; power=power*10) {
                count++;
            }
            count++;
            if (count != 13)
                return 0;
            *this >> power;
            count = 0;
            int tmp = power%10;
            power = power/10;
            count += (power%10)*3;
            power = power/10;
            count += (power%10)*1;
            power = power/10;
            count += (power%10)*3;
            power = power/10;
            count += (power%10)*1;
            power = power/10;
            count += (power%10)*3;
            power = power/10;
            count += (power%10)*1;
            power = power/10;
            count += (power%10)*3;
            power = power/10;
            count += (power%10)*1;
            power = power/10;
            count += (power%10)*3;
            power = power/10;
            count += (power%10)*1;
            power = power/10;
            count += (power%10)*3;
            power = power/10;
            count += (power%10)*1;
            count = (10-(count%10))%10;
            if (tmp != count)
                return 0;
            else
                return 1;
        }
    }
};

#endif
