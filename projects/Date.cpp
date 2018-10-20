// Copyright 2018 Gribak Jaroslav

#include <iostream>
#include <string>

class Date {
 public:
    explicit Date(int year, int month, int day);
    bool IsLeap() const;
    std::string ToString() const;
    Date DaysLater(int days) const;
    int DaysLeft(Date date) const;
    static bool IsLeap(int year);
 private:
    int year;
    int month;
    int day;
    int *days_in_month;
};

Date::Date(int year, int month, int day) {
  this->year = year;
  this->month = month;
  this->day = day;
  days_in_month = new int[12];
  for (int i = 1; i <= 12; i++)
    days_in_month[i - 1] = 28 + (i + i / 8) % 2 + 2 % i + 2 * (1 / i);
}

bool Date::IsLeap(int year) {
  return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

bool Date::IsLeap() const {
  return Date::IsLeap(year);
}

std::string Date::ToString() const {
  std::string temp[3];
  temp[0] = std::to_string(day);
  temp[1] = std::to_string(month);
  temp[2] = std::to_string(year);

  for (int i = 0; i < 3; i++) {
    int len = 2 * (i / 2 + 1);
    for (int j = temp[i].length(); j < len; j++)
      temp[i] = '0' + temp[i];
  }
  return temp[0] + '.' + temp[1] + '.' + temp[2];
}

Date Date::DaysLater(int days) const {
  Date date(year, month, day);
  days += day;
  while (days > days_in_month[date.month - 1]) {
    days -= days_in_month[date.month - 1];

    if (date.month == 2 && IsLeap())
      days -= 1;

    date.month++;
    if (date.month > 12) {
      date.month = 1;
      date.year++;
    }
  }
  date.day = days;
  return date;
}

int Date::DaysLeft(Date date) const {
  int days = date.day - day;
  int temp_m = date.month;
  int temp_y = date.year;

  while (temp_y != year || temp_m != month) {
    temp_m--;
    if (temp_m == 0) {
      temp_m = 12;
      temp_y--;
    }

    days += days_in_month[temp_m - 1];
    if (temp_m == 2 && IsLeap(temp_y))
      days++;
  }

  return days;
}
