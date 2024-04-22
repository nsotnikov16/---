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
    Transport() : distance(0.0), places(0), timeFrom({0, 0}), timeTo({0, 0}), type("")
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

    string GetPointFrom()
    {
        return pointFrom;
    }

    string GetPointTo()
    {
        return pointTo;
    }

    string GetType()
    {
        return type;
    };
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
        cout << "AirPlane:" << endl;
        Transport::Print();
        cout << "Point Middle: " << pointTo << endl;
        cout << "Model: " << model << endl;
        cout << "Class: " << classTransport << endl;
    }
};

void AddObject(Transport *transports[], int *N, Transport *transport)
{
    char keyType;

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
    cout << "Enter the index of the object: ";
    cin >> index;

    if (index < 0 || index >= *N)
    {
        cout << "\nIncorrect index!";
        return;
    }

    delete transports[*N];
    for (; index < *N - 1; index++)
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

void SortByTimeFrom(Transport *A[], int N)
{
}

void SortByTimeTo(Transport *A[], int N)
{
}

void SortByTimeFull(Transport *A[], int N)
{
}

void SortByDistance(Transport *A[], int N)
{
}

void FindByPointType(Transport *transports[], int N, int type = 1)
{
    int count = 0;
    string point;
    string p;

    cout << (type == 1 ? "Input Point From: " : "Input Point To: ");
    cin >> point;

    for (int i = 0; i < N; i++)
    {
        p = type == 1 ? transports[i]->GetPointFrom() : transports[i]->GetPointTo();
        if (p == point)
        {
            transports[i]->Print();
            cout << endl;
            count++;
        }
    }

    cout << "\nObjects found - " << count;
    return;
}

void Menu(char *key, Transport *transports[], int *N, Transport *transport)
{
    cout << "\n\n";
    cout << "1. Add Transport" << endl;
    cout << "2. Delete Transport" << endl;
    cout << "3. Print Transports" << endl;
    cout << "4. Sort Transports By Time From" << endl;
    cout << "5. Sort Transports By Time To" << endl;
    cout << "6. Sort Transports By Time Full" << endl;
    cout << "7. Sort Transports By Distance" << endl;
    cout << "8. Find Transports By Point From" << endl;
    cout << "9. Find Transports By Point To" << endl;
    cin >> key;

    switch (*key)
    {
    case '1':
        AddObject(transports, N, transport);
        break;
    case '2':
        DeleteObject(transports, N);
        break;
    case '3':
        PrintObjects(transports, *N);
        break;
    case '4':
        break;
    case '5':
        break;
    case '6':
        break;
    case '7':
        break;
    case '8':
        FindByPointType(transports, *N);
        break;
    case '9':
        FindByPointType(transports, *N, 2);
        break;
    default:
        cout << "The command was not found!" << endl;
        break;
    }
}

int main()
{
    char key;
    Transport *transports[CountObjects];
    int N = 0;
    Transport *transport;
    do
    {
        Menu(&key, transports, &N, transport);
    } while (key != '0');
    system("pause");
    return 0;
}
