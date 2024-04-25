#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Transport
{
public:
    void Print();
    string GetPointFrom();
    string GetPointTo();
    string GetType();
};

class Bus : public Transport
{
};

class Train : public Transport
{
};

class AirPlane : public Transport
{
};

class Collection
{
private:
    vector<Transport *> transports;
    enum class types
    {
        None,
        Bus,
        Train,
        AirPlane
    };

public:
    virtual ~Collection()
    {
        Clear();
    };
    void Clear()
    {
        for (int i; i < transports.size(); i++)
            delete transports[i];

        transports.clear();
    };
    bool Add(types type)
    {
        Transport *transport;
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

        if (!transport)
            return false;

        transports.push_back(transport);

        return true;
    };
    bool Delete(int pos)
    {
        delete transports[pos];
        transports.erase(transports.begin() + pos);
        return true;
    };
    void Print()
    {
        for (auto t : transports)
            t->Print();
    };

    typedef bool (*conditionSort)(Transport *t1, Transport *t2);
    bool Sort(conditionSort condition)
    {
        if (!transports.size())
            return false;

        Transport *transport;

        for (int i = transports.size(); i > 0; i--)
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
};

int main()
{
    return 0;
}