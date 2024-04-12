#include <iostream>
#include <cstdlib>

using namespace std;

struct time
{
	int hour;
	int minute;
};

// enum class DayWeek {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
string DaysWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

class Bus
{
private:
	string pointFrom;
	string pointTo;
	double distance;
	time timeFrom;
	time timeTo;
	int places;
	struct days
	{
		string daysWeek;
		string daysMonth;
	} days;
	string model;

public:
	// Bus();
	void Input()
	{
		cout << "Please, input Bus info\nBus\t| Point From:  ";
		cin >> pointFrom;
		cout << "\t| Point To: ";
		cin >> pointTo;
		cout << "\t| Distance (km): ";
		cin >> distance;
		cout << "\t| Time From (hour minutes): ";
		cin >> timeFrom.hour >> timeFrom.minute;
		cout << "\t| Time To (hour minutes): ";
		cin >> timeTo.hour >> timeTo.minute;
		cout << "\t| Free Places: ";
		cin >> places;
		cout << "\t| Enter the days of the week (1 - Monday, 2 - Tuesday, 3 - Wednesday, 4 - Thursday, 5 - Friday, 6 - Saturday, 7 - Sunday, 0 - end): ";

		int valueDayWeek = -1;
		while (valueDayWeek)
		{
			cin >> valueDayWeek;
			if (valueDayWeek > 7 || valueDayWeek < 0)
				cout << "Input Error!";
			if (valueDayWeek == 0)
				break;
			days.daysWeek = days.daysWeek.length() ? (days.daysWeek + " " + DaysWeek[valueDayWeek - 1]) : DaysWeek[valueDayWeek - 1];
		}

		cout << "\t| Enter the days of the month (0 - end). Example: 1, 5, 15, 0: ";
		int valueDayMonth = -1;
		while (valueDayMonth)
		{
			cin >> valueDayMonth;
			if (valueDayMonth > 31 || valueDayMonth < 0)
				cout << "Input Error!";
			if (valueDayMonth == 0)
				break;
			days.daysMonth = days.daysMonth.length() ? (days.daysMonth + " " + to_string(valueDayMonth)) : to_string(valueDayMonth);
		}

		//	  	for (int i = 0, value = 0; i < 7; i++) {
		//			cin >> value;
		//			days.daysWeek[i] = value;
		//	  		if (value == 0) break;
		//		}

		//		for (int i = 0; i < 31; i++) {
		//			int value;
		//			cin >> value;
		//			if (value == 0) break;
		//			days.daysMonth[i] = value;
		//		}
	};

	void Print()
	{
		cout << "Days Week: " << days.daysWeek << endl;
		cout << "Days Month: " << days.daysMonth << endl;
	};
};

// Bus::Bus() : pointFrom("������"), pointTo("�����-���������"), distance(710.5), places(30), days({5,10,15,20})
//{
//	timeFrom.hour = 10;
//	timeFrom.minute = 0;
//	timeTo.hour = 20;
//	timeTo.minute = 30;
// }

// class Train {
// private:
//	string pointFrom;
//	string pointTo;
//	double distance;
//	time timeFrom;
//	time timeTo;
//	int places;
//	int days[4];
//	enum class type {plackart, coupe, sleep} type;
// public:
//   	Train();
//   	void Input();
//   	void Print();
// };
//
// class Airplane {
// private:
//	string pointFrom;
//	string pointTo;
//	double distance;
//	time timeFrom;
//	time timeTo;
//	int places;
//	int days[4];
//	enum class type {econom, business, representative} type;
//	string model;
//	string intermediate;
// public:
//   	Airplane();
//   	void Input();
//   	void Print();
// };

int main()
{
	Bus bus;
	bus.Input();
	bus.Print();
	system("pause");
	return 0;
}
