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

class Transport
{
protected:
    string pointFrom;
    string pointTo;
    double distance;
    time timeFrom;
    time timeTo;
    int places;
    days days;

public:
    Transport() : distance(0.0), places(0), timeFrom({0, 0}), timeTo({0, 0})
    {
    }
    int InputClass(string printText) // Представим что у транспорта может быть 3 класса
    {
        int valueClass = -1;
        while (!(valueClass >= 1 && valueClass <= 3))
        {
            cout << "\t| Class " << printText << " : ";
            cin >> valueClass;
            if (valueClass < 1 || valueClass > 3)
                cout << "Input Error!" << endl;
        }
        return valueClass;
    }

    virtual void Input()
    {
        cout << "\t| Point From:  ";
        cin >> pointFrom;
        cout << "\t| Point To: ";
        cin >> pointTo;
        cout << "\t| Distance (km): ";
        cin >> distance;

        InputTime(&timeFrom);
        InputTime(&timeTo, "To");
        InputDaysWeek(&days);
    };
    virtual void Print()
    {
        cout << "Point From: " << pointFrom << endl;
        cout << "Point To: " << pointTo << endl;
        cout << "Distance: " << distance << " km" << endl;
        cout << "Time From: " << timeFrom.hour << " " << timeFrom.minute << endl;
        cout << "Time To: " << timeTo.hour << " " << timeTo.minute << endl;
        cout << "Places: " << places << endl;
        cout << "Days Week: " << days.daysWeek << endl;
    };
};

class Bus : public Transport
{
private:
    string model;

public:
    void Input()
    {
        cout << "Please, input Bus info\nBus";
        Transport::Input();
        InputDaysMonth(&days);
        cout << "\t| Free Places: ";
        cin >> places;
        cout << "\t| Model: ";
        cin >> model;
    };

    void Print()
    {
        cout << "Bus:" << endl;
        Transport::Print();
        cout << "Days Month: " << days.daysMonth << endl;
        cout << "Model: " << model << endl;
    }
};

class Train : public Transport
{
private:
    string classesTransport[3] = {"Platscart", "Coupe", "Sleeping"};
    string classTransport;

public:
    void SetPlaces(int value)
    {
        switch (value)
        {
        case 1:
            places = 54;
            break;
        case 2:
            places = 36;
            break;
        case 3:
            places = 18;
            break;
        }
    };

    void Input()
    {
        cout << "Please, input Train info\nTrain";
        Transport::Input();
        int valueClass = Transport::InputClass("(1 - Platscart, 2 - Coupe, 3 - Sleeping)");
        classTransport = classesTransport[valueClass - 1];
        SetPlaces(valueClass);
    }

    void Print()
    {
        cout << "Train:" << endl;
        Transport::Print();
        cout << "Class: " << classTransport << endl;
    }
};

class AirPlane : public Transport
{
private:
    string classesTransport[3] = {"Economy", "Business", "Executive"};
    string classTransport;
    string model;
    string pointMiddle;

public:
    void SetPlaces(int value)
    {
        switch (value)
        {
        case 1:
            places = 200;
            break;
        case 2:
            places = 50;
            break;
        case 3:
            places = 20;
            break;
        }
    }

    void Input()
    {
        cout << "Please, input AirPlane info\nAirPlane";
        Transport::Input();
        cout << "\t| Point Middle: ";
        cin >> pointMiddle;
        cout << "\t| Model: ";
        cin >> model;
        int valueClass = Transport::InputClass("(1 - Economy, 2 - Business, 3 - Executive)");
        classTransport = classesTransport[valueClass - 1];
        SetPlaces(valueClass);
    }

    void Print()
    {
        cout << "AirPlane:" << endl;
        Transport::Print();
        cout << "Point Middle: " << pointTo << endl;
        cout << "Model: " << model << endl;
        cout << "Class: " << classTransport << endl;
    }
};

int main()
{
    cout << "\nStatic objects test\n";

    Bus b;
    b.Print();
    b.Input();
    b.Print();

    cout << endl;

    Train t;
    t.Print();
    t.Input();
    t.Print();

    cout << endl;

    AirPlane a;
    a.Print();
    a.Input();
    a.Print();

    cout << "\nDinamyc objects and polymorphism test\n";
    Transport *p;

    p = new Bus;
    p->Print();
    p->Input();
    p->Print();
    delete p;

    cout << endl;

    p = new Train;
    p->Print();
    p->Input();
    p->Print();
    delete p;

    cout << endl;

    p = new AirPlane;
    p->Print();
    p->Input();
    p->Print();
    delete p;

    cout << endl
         << "End test.\n";
    system("pause");
    return 0;
}
