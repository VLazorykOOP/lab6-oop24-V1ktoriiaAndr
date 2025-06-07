#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class BaseVirtual {
    int baseData;
};

class Class1Virtual : virtual public BaseVirtual {
    int class1Data;
};

class Class2Virtual : virtual public BaseVirtual {
    int class2Data;
};

class Class3Virtual : virtual public Class1Virtual, virtual public BaseVirtual {
    int class3Data;
};

class Class4Virtual : virtual public Class2Virtual, virtual public BaseVirtual {
    int class4Data;
};

class FinalVirtual : virtual public Class1Virtual, virtual public Class2Virtual,
    virtual public Class3Virtual, virtual public Class4Virtual {
    int finalData;
};

class BaseNonVirtual {
    int baseData;
};

class Class1NonVirtual : public BaseNonVirtual {
    int class1Data;
};

class Class2NonVirtual : public BaseNonVirtual {
    int class2Data;
};

class Class3NonVirtual : public Class1NonVirtual, public BaseNonVirtual {
    int class3Data;
};

class Class4NonVirtual : public Class2NonVirtual, public BaseNonVirtual {
    int class4Data;
};

class FinalNonVirtual : public Class1NonVirtual, public Class2NonVirtual,
    public Class3NonVirtual, public Class4NonVirtual {
    int finalData;
};

void task1() {
    cout << "=== Sizes with virtual inheritance ===" << endl;
    cout << "BaseVirtual: " << sizeof(BaseVirtual) << endl;
    cout << "Class1Virtual: " << sizeof(Class1Virtual) << endl;
    cout << "Class2Virtual: " << sizeof(Class2Virtual) << endl;
    cout << "Class3Virtual: " << sizeof(Class3Virtual) << endl;
    cout << "Class4Virtual: " << sizeof(Class4Virtual) << endl;
    cout << "FinalVirtual: " << sizeof(FinalVirtual) << endl;

    cout << "\n=== Sizes without virtual inheritance ===" << endl;
    cout << "BaseNonVirtual: " << sizeof(BaseNonVirtual) << endl;
    cout << "Class1NonVirtual: " << sizeof(Class1NonVirtual) << endl;
    cout << "Class2NonVirtual: " << sizeof(Class2NonVirtual) << endl;
    cout << "Class3NonVirtual: " << sizeof(Class3NonVirtual) << endl;
    cout << "Class4NonVirtual: " << sizeof(Class4NonVirtual) << endl;
    cout << "FinalNonVirtual: " << sizeof(FinalNonVirtual) << endl;
}

class Function {
public:
    virtual double calculate(double x) const = 0;
    virtual ~Function() {}
};

class Line : public Function {
private:
    double a, b;
public:
    Line(double a_, double b_) : a(a_), b(b_) {}
    double calculate(double x) const override {
        return a * x + b;
    }
};

class Ellipse : public Function {
private:
    double a, b;
public:
    Ellipse(double a_, double b_) : a(a_), b(b_) {}
    double calculate(double x) const override {
        if (x * x / (a * a) > 1.0) {
            throw invalid_argument("The value of x does not belong to the definition area of the ellipse.");
        }
        return b * sqrt(1.0 - (x * x) / (a * a));
    }
};


class Hyperbola : public Function {
private:
    double a, b;
public:
    Hyperbola(double a_, double b_) : a(a_), b(b_) {}
    double calculate(double x) const override {
        if (x * x / (a * a) < 1.0) {
            throw invalid_argument("The value of x does not belong to the definition area of the hyperbola.");
        }
        return b * sqrt((x * x) / (a * a) - 1.0);
    }
};

void task2() {
    try {
        cout << "Enter parameters for the line (a, b): ";
        double a, b;
        cin >> a >> b;
        Line line(a, b);

        cout << "Enter x for the line: ";
        double x;
        cin >> x;
        cout << "Line: y(" << x << ") = " << line.calculate(x) << endl;

        cout << "Enter parameters for the ellipse (a, b): ";
        cin >> a >> b;
        Ellipse ellipse(a, b);

        cout << "Enter x for the ellipse: ";
        cin >> x;
        cout << "Ellipse: y(" << x << ") = " << ellipse.calculate(x) << endl;

        cout << "Enter parameters for the hyperbola (a, b): ";
        cin >> a >> b;
        Hyperbola hyperbola(a, b);

        cout << "Enter x for the hyperbola: ";
        cin >> x;
        cout << "Hyperbola: y(" << x << ") = " << hyperbola.calculate(x) << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

class Worker {
protected:
    string name;
    string jobTitle;
public:
    Worker(const string& name_ = "", const string& jobTitle_ = "")
        : name(name_), jobTitle(jobTitle_) {
    }

    virtual ~Worker() {}

    friend ostream& operator<<(ostream& os, const Worker& worker) {
        os << "Name: " << worker.name << ", Job Title: " << worker.jobTitle;
        return os;
    }

    friend istream& operator>>(istream& is, Worker& worker) {
        cout << "Enter name: ";
        is >> worker.name;
        cout << "Enter job title: ";
        is >> worker.jobTitle;
        return is;
    }
};

class FamilyHead {
protected:
    int childrenCount;
    string familyAddress;
public:
    FamilyHead(int childrenCount_ = 0, const string& familyAddress_ = "")
        : childrenCount(childrenCount_), familyAddress(familyAddress_) {
    }

    virtual ~FamilyHead() {}

    friend ostream& operator<<(ostream& os, const FamilyHead& familyHead) {
        os << "Children Count: " << familyHead.childrenCount
            << ", Family Address: " << familyHead.familyAddress;
        return os;
    }

    friend istream& operator>>(istream& is, FamilyHead& familyHead) {
        cout << "Enter number of children: ";
        is >> familyHead.childrenCount;
        cout << "Enter family address: ";
        is.ignore();
        familyHead.familyAddress.clear();
        char ch;
        while ((ch = is.get()) != '\n') {
            familyHead.familyAddress += ch;
        }
        return is;
    }
};

class WorkerFather : public Worker, public FamilyHead {
private:
    string familyResponsibility;
public:
    WorkerFather(const string& name_ = "", const string& jobTitle_ = "",
        int childrenCount_ = 0, const string& familyAddress_ = "",
        const string& familyResponsibility_ = "")
        : Worker(name_, jobTitle_), FamilyHead(childrenCount_, familyAddress_),
        familyResponsibility(familyResponsibility_) {
    }

    void displayInfo() const {
        cout << "=== Worker-Father Information ===" << endl;
        cout << "Worker Info: " << static_cast<const Worker&>(*this) << endl;
        cout << "Family Head Info: " << static_cast<const FamilyHead&>(*this) << endl;
        cout << "Family Responsibility: " << familyResponsibility << endl;
    }

    friend istream& operator>>(istream& is, WorkerFather& workerFather) {
        cout << "Enter worker details:" << endl;
        cin >> static_cast<Worker&>(workerFather);
        cout << "Enter family head details:" << endl;
        cin >> static_cast<FamilyHead&>(workerFather);
        cout << "Enter family responsibility: ";
        workerFather.familyResponsibility.clear();
        char ch;
        while ((ch = is.get()) != '\n') {
            workerFather.familyResponsibility += ch;
        }
        return is;
    }
};

void task3() {
    WorkerFather workerFather;
    cout << "Enter details for the Worker-Father:" << endl;
    cin >> workerFather;
    workerFather.displayInfo();
}

int main() {
    int choice;
    do {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Task 1: Virtual vs Non-Virtual Inheritance" << endl;
        cout << "2. Task 2: Abstract Class and Derived Classes (Functions)" << endl;
        cout << "3. Task 3: Multiple Inheritance (Worker-Father)" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}