#include <iostream>
#include <cstdlib>

using namespace std;

#define CountObjects 20

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

double convertTime(time time)
{
    return time.hour + (time.minute / 60);
}

string getInputValueStr(string inputText)
{
    string value;
    cout << inputText;
    cin >> value;
    return value;
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

int InputClass(string printText) // Ïðåäñòàâèì ÷òî ó òðàíñïîðòà ìîæåò áûòü 3 êëàññà
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

bool compareTime(time time1, time time2)
{
    if (time1.hour == time2.hour)
    {
        return time1.minute > time2.minute;
    }
    return time1.hour > time2.hour;
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
    string type;

public:
    Transport() : distance(0.0), places(0), timeFrom({0, 0}), timeTo({0, 0}), type("None")
    {
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

    string GetType()
    {
        return type;
    }

    string GetPointFrom()
    {
        return pointFrom;
    }

    string GetPointTo()
    {
        return pointTo;
    }

    time GetTimeFrom()
    {
        return timeFrom;
    }

    time GetTimeTo()
    {
        return timeTo;
    }

    double GetDistance()
    {
        return distance;
    }

    double GetTimeFull()
    {
        double convertTimeFrom = convertTime(timeFrom);
        double convertTimeTo = convertTime(timeTo);
        if (convertTimeFrom < convertTimeTo)
        {
            return convertTimeTo - convertTimeFrom;
        }

        return 24 - convertTimeFrom + convertTimeTo;
    }
};

class Bus : public Transport
{
private:
    string model;

public:
    Bus() : Transport()
    {
        type = "1";
    }
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
        cout << "\n\nBus:" << endl;
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
    Train() : Transport()
    {
        type = "2";
    }
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
        int valueClass = InputClass("(1 - Platscart, 2 - Coupe, 3 - Sleeping)");
        classTransport = classesTransport[valueClass - 1];
        SetPlaces(valueClass);
    }

    void Print()
    {
        cout << "\n\nTrain:" << endl;
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
    AirPlane() : Transport()
    {
        type = "3";
    }
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
        int valueClass = InputClass("(1 - Economy, 2 - Business, 3 - Executive)");
        classTransport = classesTransport[valueClass - 1];
        SetPlaces(valueClass);
    }

    void Print()
    {
        cout << "\n\nAirPlane:" << endl;
        Transport::Print();
        cout << "Point Middle: " << pointTo << endl;
        cout << "Model: " << model << endl;
        cout << "Class: " << classTransport << endl;
    }
};

void AddObject(Transport *transports[], int *N)
{
    char keyType;
    Transport *transport;

    if (*N >= CountObjects)
    {
        cout << "The maximum number has been added" << endl;
        return;
    }

    cout << "Choose (1 - Bus, 2 - Train, 3 - AirPlane):" << endl;
    cin >> keyType;

    switch (keyType)
    {
    case '1':
        transport = new Bus;
        break;
    case '2':
        transport = new Train;
        break;
    case '3':
        transport = new AirPlane;
        break;
    default:
        cout << "incorrect choice!" << endl;
        break;
    }

    if (!transport)
        return;

    transport->Input();
    transports[*N] = transport;
    *N += 1;

    cout << "\nTransport added successfully!";
}

void DeleteObject(Transport *transports[], int *N)
{
    int index;

    if (*N == 0)
    {
        cout << "The objects do not exist!\n";
        return;
    }

    cout << "Enter the index of the object from 0"
         << " to " << *N - 1 << ": ";
    cin >> index;

    if (index < 0 || index > *N)
    {
        cout << "\nIncorrect index!";
        return;
    }

    delete transports[index];

    for (; index < *N; index++)
    {
        transports[index] = transports[index + 1];
    }

    *N -= 1;

    cout << "\nTransport was deleted successfully!";
}

void PrintObjects(Transport *transports[], int N)
{
    if (!N)
    {
        cout << "The objects do not exist\n";
        return;
    }

    for (int i = 0; i < N; i++)
        transports[i]->Print();
}

typedef bool (*condition)(Transport * t1, Transport * t2);

/* Ñîðòèðîâêà ïî óñëîâèþ, ÷òîáû íå äóáëèðîâàòü ïîõîæèå öèêëû */
void SortObjects(Transport *transports[], int N, condition condition)
{
    if (N <= 0)
    {
        cout << "The objects do not exist!\n";
        return;
    }

    Transport *transport;
    int i, j;
    for (i = N - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (condition(transports[i], transports[j]))
            {
                transport = transports[i];
                transports[i] = transports[j];
                transports[j] = transport;
            }
        }
    }
}

/* Ñîðòèðîâêà ïî âðåìåíè îòïðàâëåíèÿ ïî âîçðàñòàíèþ */
bool SortByTimeFrom(Transport * t1, Transport * t2)
{
    return compareTime(t2->GetTimeFrom(), t1->GetTimeFrom());
}

/* Ñîðòèðîâêà ïî âðåìåíè îòïðàâëåíèÿ ïî âîçðàñòàíèþ */
bool SortByTimeTo(Transport * t1, Transport * t2)
{
    return compareTime(t2->GetTimeTo(), t1->GetTimeTo());
}

/* Ñîðòèðîâêà ïî îáùåìó âðåìåíè â ïóòè ïî âîçðàñòàíèþ */
bool SortByTimeFull(Transport * t1, Transport * t2)
{
    return t1->GetTimeFull() < t2->GetTimeFull();
}

/* Ñîðòèðîâêà ïî ðàññòîÿíèþ ïî âîçðàñòàíèþ */
bool SortByDistance(Transport * t1, Transport * t2)
{
    return t2->GetDistance() > t1->GetDistance();
}

typedef bool (*conditionFilter)(Transport *transport, string inputValue);

// Ôèëüòðàöèÿ ïî óñëîâèþ
void Filter(Transport *transports[], int N, string inputValue, conditionFilter c)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (c(transports[i], inputValue))
        {
            transports[i]->Print();
            cout << endl;
            count++;
        }
    }

    cout << "\nObjects found - " << count;
    return;
}
bool FilterByPointFrom(Transport *transport, string inputValue)
{
    return transport->GetPointFrom() == inputValue;
}

bool FilterByPointTo(Transport *transport, string inputValue)
{
    return transport->GetPointTo() == inputValue;
}

bool FilterByType(Transport *transport, string inputValue)
{
    return transport->GetType() == inputValue;
}

void Menu(Transport *transports[], int *N)
{
    int key;

    cout << "\n\n";
    cout << "1. Add Transport" << endl;
    cout << "2. Delete Transport" << endl;
    cout << "3. Print Transports" << endl;
    cout << "4. Sort Transports By Time From" << endl;
    cout << "5. Sort Transports By Time To" << endl;
    cout << "6. Sort Transports By Time Full" << endl;
    cout << "7. Sort Transports By Distance" << endl;
    cout << "8. Filter Transports By Point From" << endl;
    cout << "9. Filter Transports By Point To" << endl;
    cout << "10. Filter Transports By Type" << endl;
    cout << "0. Exit" << endl;
    cin >> key;

    switch (key)
    {
    case 1:
        AddObject(transports, N);
        break;
    case 2:
        DeleteObject(transports, N);
        break;
    case 3:
        PrintObjects(transports, *N);
        break;
    case 4:
        SortObjects(transports, *N, &SortByTimeFrom);
        break;
    case 5:
        SortObjects(transports, *N, &SortByTimeTo);
        break;
    case 6:
        SortObjects(transports, *N, &SortByTimeFull);
        break;
    case 7:
        SortObjects(transports, *N, &SortByDistance);
        break;
    case 8:
        Filter(transports, *N, getInputValueStr("Input Point From: "), &FilterByPointFrom);
        break;
    case 9:
        Filter(transports, *N, getInputValueStr("Input Point To: "), &FilterByPointTo);
        break;
    case 10:
        Filter(transports, *N, getInputValueStr("Input type (1 - Bus, 2 - Train, 3 - AirPlane): "), &FilterByType);
        break;
    case 0:
        cout << "Exit" << endl;
        break;
    default:
        cout << "The command was not found!" << endl;
        break;
    }

    if (key != 0)
        Menu(transports, N);
}

int main()
{
    char key;
    Transport *transports[CountObjects];
    int N = 0;

    Menu(transports, &N);

    for (int i = 0; i < N; i++)
        delete transports[i];

    system("pause");
    return 0;
}
