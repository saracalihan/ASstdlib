/*
 * Copyright (c) 2024, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more detail.
 */

#ifndef DATE_H
#define DATE_H

#include <stdlib.h>
#include<time.h>
#include <cstdio>


typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Date;

struct tm date_to_tm(const Date* d) {
    struct tm t = {0};
    t.tm_year = d->year - 1900;
    t.tm_mon = d->month - 1;
    t.tm_mday = d->day;
    t.tm_hour = d->hour;
    t.tm_min = d->minute;
    t.tm_sec = d->second;

    return t;
}

Date tm_to_date(const struct tm* t) {
    Date d={0};
    d.year = 1900 + t->tm_year;
    d.month = 1 + t->tm_mon;
    d.day = t->tm_mday;
    d.hour = t->tm_hour;
    d.minute = t->tm_min;
    d.second = t->tm_sec;

    return d;
}

Date date_now(){
    time_t now;
    struct tm *t;

    time(&now);
    t = localtime(&now);

    return tm_to_date(t);
}

long date_to_unix_timestamp(const Date* d){
    struct tm t=date_to_tm(d);
    return mktime(&t);
}

char* date_to_string(const Date* d) {
    char *buffer = (char*)malloc(sizeof(char)*20);
    snprintf(buffer, 20, "%04d-%02d-%02dT%02d:%02d:%02d",
             d->year, d->month, d->day,
             d->hour, d->minute, d->second);
    return buffer;
}

Date date_from_string(const char* str){
    struct tm t={0};

    if (strptime(str, "%Y-%m-%dT%H:%M:%S", &t) == NULL) {
        perror("[DATE] date parse error!\n");
        exit(1);
    }

    return tm_to_date(&t);
}

/**
    This function does not return real date!
    It return diffirence between two dates using Date structure.
 */
Date date_difference(const Date* d1, const Date* d2) {
    struct tm t1 = date_to_tm(d1);
    struct tm t2 = date_to_tm(d2);

    time_t timestamp1 = mktime(&t1);
    time_t timestamp2 = mktime(&t2);

    time_t diff = timestamp1 > timestamp2 ? timestamp1 - timestamp2 : timestamp2 - timestamp1;

    Date d={0};
    d.day = diff/(24 * 60 * 60);
    diff %= 24 * 60 * 60;

    d.hour = diff/(60 * 60);
    diff %= 60 * 60;

    d.minute = diff/ 60;
    diff %= 60;

    d.second = diff;

    d.month = d.day/30;
    d.year = d.month/12;

    return d;
}
#endif // DATE_H
