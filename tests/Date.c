#include "../Date.h"
#include "../Test.h"
#include <string.h>

int main(){
    Date d = {2023, 12, 25, 10, 30, 45};
    Date d2 = {2024, 1, 5, 12, 15, 30};

    Tests({
        Describe("Date to struct tm conversion", {
            Test("Date to struct tm should convert correctly", {
                struct tm t = date_to_tm(&d);
                (t.tm_year == 123&&
                t.tm_mon == 11&&
                t.tm_mday == 25&&
                t.tm_hour == 10&&
                t.tm_min == 30&&
                t.tm_sec == 45);
            });
        });

        Describe("Date to Unix timestamp conversion", {
            Test("Date to Unix timestamp should convert correctly", {
                long timestamp = date_to_unix_timestamp(&d);
                struct tm t = date_to_tm(&d);
                long expected_timestamp = mktime(&t);
                timestamp == expected_timestamp;
            });
        });

        Describe("struct tm to Date conversion", {
            Test("struct tm to Date should convert correctly", {
                struct tm t = {0};
                t.tm_year = 123; // 2023 - 1900
                t.tm_mon = 11;   // December is 11 (0-based)
                t.tm_mday = 25;
                t.tm_hour = 10;
                t.tm_min = 30;
                t.tm_sec = 45;
                d = tm_to_date(&t);
                (d.year == 2023&&
                d.month == 12&&
                d.day == 25&&
                d.hour == 10&&
                d.minute == 30&&
                d.second == 45);
            });
        });

        Describe("Date string conversion", {
            Test("String to Date should convert correctly", {
                const char* date_str = "2023-12-25T10:30:45";
                d = date_from_string(date_str);
                (d.year == 2023&&
                d.month == 12&&
                d.day == 25&&
                d.hour == 10&&
                d.minute == 30&&
                d.second == 45);
            });

            Test("Date to string should convert correctly", {
                char* date_str = date_to_string(&d);
                strcmp(date_str, "2023-12-25T10:30:45") == 0;
            });
        });

        Describe("date_now function", {
            Test("date_now should return current date", {
                Date d = date_now();
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                Date current = tm_to_date(t);

                (d.year == current.year&&
                d.month == current.month&&
                d.day == current.day&&
                d.hour == current.hour&&
                d.minute == current.minute&&
                d.second == current.second);
            });
        });

        Describe("Date difference", {
        Test("Calculating difference between dates should give correct result", {
            Date result = date_difference(&d, &d2);
            result.year == 0&&
            result.month == 0&&
            result.day == 11&&
            result.hour == 1&&
            result.minute == 44&&
            result.second == 45;
        });
    });
    });

    return 0;
}
