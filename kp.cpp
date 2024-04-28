#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

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

int InputClass(string printText) // ?????????? ??? ? ?????????? ????? ???? 3 ??????
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
        cout << "Type: " << type << endl;
        cout << "Point From: " << pointFrom << endl;
        cout << "Point To: " << pointTo << endl;
        cout << "Distance: " << distance << " km" << endl;
        cout << "Time From: " << timeFrom.hour << " " << timeFrom.minute << endl;
        cout << "Time To: " << timeTo.hour << " " << timeTo.minute << endl;
        cout << "Places: " << places << endl;
        cout << "Days Week: " << days.daysWeek << endl;
    };

    virtual void Save(ostream &os)
    {
        os << pointFrom << "|";
        os << pointTo << "|";
        os << distance << "|";
        os << timeFrom.hour << " " << timeFrom.minute << "|";
        os << timeTo.hour << " " << timeTo.minute << "|";
        os << places << "|";
        os << days.daysWeek << "|";
        os << days.daysMonth << "|";
        os << type << "|";
    };

    virtual void Load(istream &is)
    {
        getline(is, pointFrom, '|');
        pointFrom.erase(0, pointFrom.find_first_not_of(" \t\n\r\f\v"));
        getline(is, pointTo, '|');

        string distanceString;
        getline(is, distanceString, '|');
        distance = stod(distanceString);

        string timeFromString;
        getline(is, timeFromString, '|');
        stringstream ss1(timeFromString);
        ss1 >> timeFrom.hour >> timeFrom.minute;

        string timeToString;
        getline(is, timeToString, '|');
        stringstream ss2(timeToString);
        ss2 >> timeTo.hour >> timeTo.minute;

        string placesString;
        getline(is, placesString, '|');
        places = stoi(placesString);

        getline(is, days.daysWeek, '|');
        getline(is, days.daysMonth, '|');
        getline(is, type, '|');
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

    void Save(ostream &os)
    {
        Transport::Save(os);
        os << model << "|";
    }

    void Load(istream &is)
    {
        Transport::Load(is);
        getline(is, model, '|');
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

    void Save(ostream &os)
    {
        Transport::Save(os);
        os << classTransport << "|";
    }

    void Load(istream &is)
    {
        Transport::Load(is);
        getline(is, classTransport, '|');
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

    void Save(ostream &os)
    {
        Transport::Save(os);
        os << classTransport << "|";
        os << model << "|";
        os << pointMiddle << "|";
    }

    void Load(istream &is)
    {
        Transport::Load(is);
        getline(is, classTransport, '|');
        getline(is, model, '|');
        getline(is, pointMiddle, '|');
    }
};

class Collection
{
private:
    vector<Transport *> transports;

public:
    enum class types
    {
        None,
        Bus,
        Train,
        AirPlane
    };
    virtual ~Collection()
    {
        Clear();
    };
    void Clear()
    {
        for (auto t : transports)
            delete t;

        transports.clear();
    };

    bool Save(string filename)
    {
        ofstream fout(filename);
        if (!fout)
            return false;
        fout << GetSize() << endl;
        for (int i = 0; i < GetSize(); i++)
        {
            fout << transports[i]->GetType() << endl;
            transports[i]->Save(fout);
            fout << endl;
        }
        fout.close();
        return true;
    }

    bool Load(string filename)
    {
        int n, i;
        ifstream fin(filename);
        if (!fin)
            return false;
        Clear();
        fin >> n;
        for (i = 0; i < n; i++)
        {
            int type;
            fin >> type;
            Transport *t = Create((types)type);
            if (!t)
                break;
            t->Load(fin);
            Add(t);
        }
        fin.close();
        if (i == n)
            return true;
        Clear();
        return false;
    }

    int GetSize()
    {
        return transports.size();
    }

    Transport *Create(types type)
    {
        Transport *transport = nullptr;
        switch (type)
        {
        case types::Bus:
            transport = new Bus;
            break;
        case types::Train:
            transport = new Train;
            break;
        case types::AirPlane:
            transport = new AirPlane;
            break;
        }

        return transport;
    }

    void Add(Transport *transport)
    {
        transports.push_back(transport);
    };

    bool Delete(int pos)
    {
        if (pos < 0 || pos >= GetSize())
            return false;
        delete transports[pos];
        transports.erase(transports.begin() + pos);
        return true;
    };
    bool Print()
    {
        if (!GetSize())
            return false;

        for (auto t : transports)
            t->Print();

        return true;
    };

    typedef bool (*conditionSort)(Transport *t1, Transport *t2);
    void Sort(conditionSort condition)
    {
        if (!GetSize())
            return;

        Transport *transport = nullptr;

        for (int i = GetSize() - 1; i > 0; i--)
        {
            for (int j = 0; j < i; j++)
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

    typedef bool (*conditionFilter)(Transport *transport, string inputValue);
    int Filter(string inputValue, conditionFilter condition)
    {
        int count = 0;
        for (auto t : transports)
        {
            if (condition(t, inputValue))
            {
                t->Print();
                count++;
            }
        }

        return count;
    }
};

bool SortByTimeFrom(Transport *t1, Transport *t2)
{
    return compareTime(t2->GetTimeFrom(), t1->GetTimeFrom());
}

bool SortByTimeTo(Transport *t1, Transport *t2)
{
    return compareTime(t2->GetTimeTo(), t1->GetTimeTo());
}

bool SortByTimeFull(Transport *t1, Transport *t2)
{
    return t1->GetTimeFull() < t2->GetTimeFull();
}

bool SortByDistance(Transport *t1, Transport *t2)
{
    return t2->GetDistance() > t1->GetDistance();
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

void Menu(Collection *transports)
{
    int key;
    Transport *t = nullptr;

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
    cout << "11. Save Data" << endl;
    cout << "12. Load Data" << endl;
    cout << "0. Exit" << endl;
    cin >> key;

    switch (key)
    {
    case 1:
        int keyType;

        cout << "Choose (1 - Bus, 2 - Train, 3 - AirPlane):" << endl;
        cin >> keyType;
        t = transports->Create((Collection::types)keyType);
        if (t)
        {
            t->Input();
            transports->Add(t);
            cout << "\nTransport added successfully!";
        }
        else
        {
            cout << "incorrect choice!" << endl;
        }

        break;
    case 2:
        int index;
        cout << "Enter the index of the object from 0"
             << " to " << transports->GetSize() - 1 << ": ";
        cin >> index;
        transports->Delete(index) ? cout << "\nTransport was deleted successfully!" : cout << "\nIncorrect index!";
        break;
    case 3:
        if (!transports->Print())
            cout << "The objects do not exist\n";
        break;
    case 4:
        transports->Sort(&SortByTimeFrom);
        break;
    case 5:
        transports->Sort(&SortByTimeTo);
        break;
    case 6:
        transports->Sort(&SortByTimeFull);
        break;
    case 7:
        transports->Sort(&SortByDistance);
        break;
    case 8:
        transports->Filter(getInputValueStr("Input Point From: "), &FilterByPointFrom);
        break;
    case 9:
        transports->Filter(getInputValueStr("Input Point To: "), &FilterByPointTo);
        break;
    case 10:
        transports->Filter(getInputValueStr("Input type (1 - Bus, 2 - Train, 3 - AirPlane): "), &FilterByType);
        break;
    case 11:
        transports->Save("data.txt");
        break;
    case 12:
        transports->Load("data.txt");
        break;
    case 0:
        cout << "Exit" << endl;
        break;
    default:
        cout << "The command was not found!" << endl;
        break;
    }

    if (key != 0)
        Menu(transports);
}

int main()
{
    char key;
    Collection transports;
    Menu(&transports);
    system("pause");
    return 0;
}
