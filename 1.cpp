#include <iostream>
#include <cstdlib>

using namespace std;

struct time
{
	int hour;
	int minute;
};

struct days
{
	std::string daysWeek;
	std::string daysMonth;
};

string DaysWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

bool checkValidityTime(time *time)
{
	return time->hour >= 0 && time->hour <= 23 && time->minute >= 0 && time->minute <= 59;
}

void InputTime(time *time, string type = "From")
{
	cout << "\t| Time " << type << " (hour minutes): ";
	cin >> time->hour >> time->minute;
	if (checkValidityTime(time))
		return;
	cout << "Input Error!" << endl;
	InputTime(time, type);
}

void InputDaysWeek(struct days *days)
{
	cout << "\t| Enter the days of the week (1 - Monday, 2 - Tuesday, 3 - Wednesday, 4 - Thursday, 5 - Friday, 6 - Saturday, 7 - Sunday, 0 - end): ";

	int valueDayWeek = -1;
	while (valueDayWeek)
	{
		cin >> valueDayWeek;
		if (valueDayWeek > 7 || valueDayWeek < 0)
			cout << "Input Error!" << endl;
		if (valueDayWeek == 0)
			break;
		days->daysWeek = days->daysWeek.length() ? (days->daysWeek + " " + DaysWeek[valueDayWeek - 1]) : DaysWeek[valueDayWeek - 1];
	}
}

void InputDaysMonth(struct days *days)
{
	cout << "\t| Enter the days of the month (0 - end): ";
	int valueDayMonth = -1;
	while (valueDayMonth)
	{
		cin >> valueDayMonth;
		if (valueDayMonth > 31 || valueDayMonth < 0)
			cout << "Input Error!" << endl;
		if (valueDayMonth == 0)
			break;
		days->daysMonth = days->daysMonth.length() ? (days->daysMonth + " " + to_string(valueDayMonth)) : to_string(valueDayMonth);
	}
}

class Bus
{
private:
	string pointFrom;
	string pointTo;
	double distance;
	time timeFrom;
	time timeTo;
	int places;
	days days;
	string model;

public:
	void Input()
	{
		cout << "Please, input Bus info\nBus\t| Point From:  ";
		cin >> pointFrom;
		cout << "\t| Point To: ";
		cin >> pointTo;
		cout << "\t| Distance (km): ";
		cin >> distance;

		InputTime(&timeFrom);
		InputTime(&timeTo, "To");

		cout << "\t| Free Places: ";
		cin >> places;
		cout << "\t| Model: ";
		cin >> model;
		InputDaysWeek(&days);
		InputDaysMonth(&days);
	};

	void Print()
	{
		cout << "Bus:" << endl;
		cout << "Point From: " << pointFrom << endl;
		cout << "Point To: " << pointTo << endl;
		cout << "Distance: " << distance << " km" << endl;
		cout << "Time From: " << timeFrom.hour << " " << timeFrom.minute << endl;
		cout << "Time To: " << timeTo.hour << " " << timeTo.minute << endl;
		cout << "Places: " << places << endl;
		cout << "Model: " << model << endl;

		cout << "Days Week: " << days.daysWeek << endl;
		cout << "Days Month: " << days.daysMonth << endl;
	};
};

class Train
{
private:
	string pointFrom;
	string pointTo;
	double distance;
	time timeFrom;
	time timeTo;
	int places;
	days days;
	string classesTransport[3] = {"Platscart", "Coupe", "Sleeping"};
	string classTransport;

public:
	void SetPlaces(int value)
	{
		if (value == 1)
			places = 54;
		if (value == 2)
			places = 36;
		if (value == 3)
			places = 18;
	}

	void Input()
	{
		cout << "Please, input Train info\nTrain\t| Point From:  ";
		cin >> pointFrom;
		cout << "\t| Point To: ";
		cin >> pointTo;
		cout << "\t| Distance (km): ";
		cin >> distance;

		InputTime(&timeFrom);
		InputTime(&timeTo, "To");

		int valueClass = -1;
		while (!(valueClass >= 1 && valueClass <= 3))
		{
			cout << "\t| Class (1 - Platscart, 2 - Coupe, 3 - Sleeping): ";
			cin >> valueClass;
			if (valueClass < 1 || valueClass > 3)
				cout << "Input Error!" << endl;
		}

		classTransport = classesTransport[valueClass - 1];
		SetPlaces(valueClass);

		InputDaysWeek(&days);
	};

	void Print()
	{
		cout << "Train:" << endl;
		cout << "Point From: " << pointFrom << endl;
		cout << "Point To: " << pointTo << endl;
		cout << "Distance: " << distance << " km" << endl;
		cout << "Time From: " << timeFrom.hour << " " << timeFrom.minute << endl;
		cout << "Time To: " << timeTo.hour << " " << timeTo.minute << endl;
		cout << "Class: " << classTransport << endl;
		cout << "Places: " << places << endl;

		cout << "Days Week: " << days.daysWeek << endl;
	};
};

class AirPlane
{
private:
	string pointFrom;
	string pointTo;
	string pointMiddle;
	double distance;
	time timeFrom;
	time timeTo;
	int places;
	days days;
	string classesTransport[3] = {"Economy", "Business", "Executive"};
	string classTransport;
	string model;

public:
	void SetPlaces(int value)
	{
		if (value == 1)
			places = 200;
		if (value == 2)
			places = 50;
		if (value == 3)
			places = 20;
	}

	void Input()
	{
		cout << "Please, input AirPlane info\nAirPlane\t| Point From:  ";
		cin >> pointFrom;
		cout << "\t| Point To: ";
		cin >> pointTo;
		cout << "\t| Point Middle: ";
		cin >> pointMiddle;
		cout << "\t| Distance (km): ";
		cin >> distance;

		InputTime(&timeFrom);
		InputTime(&timeTo, "To");

		cout << "\t| Model: ";
		cin >> model;

		int valueClass = -1;
		while (!(valueClass >= 1 && valueClass <= 3))
		{
			cout << "\t| Class (1 - Economy, 2 - Business, 3 - Executive): ";
			cin >> valueClass;
			if (valueClass < 1 || valueClass > 3)
				cout << "Input Error!" << endl;
		}

		classTransport = classesTransport[valueClass - 1];
		SetPlaces(valueClass);

		InputDaysWeek(&days);
	};

	void Print()
	{
		cout << "AirPlane:" << endl;
		cout << "Point From: " << pointFrom << endl;
		cout << "Point To: " << pointTo << endl;
		cout << "Distance: " << distance << " km" << endl;
		cout << "Time From: " << timeFrom.hour << " " << timeFrom.minute << endl;
		cout << "Time To: " << timeTo.hour << " " << timeTo.minute << endl;
		cout << "Model: " << model << endl;
		cout << "Class: " << classTransport << endl;
		cout << "Places: " << places << endl;

		cout << "Days Week: " << days.daysWeek << endl;
	};
};

int main()
{
	Bus bus;
	bus.Input();
	bus.Print();
	cout << endl;
	cout << endl;
	Train train;
	train.Input();
	train.Print();
	cout << endl;
	cout << endl;
	AirPlane airPlane;
	airPlane.Input();
	airPlane.Print();
	system("pause");
	return 0;
}
