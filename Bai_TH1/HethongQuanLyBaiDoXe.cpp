#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

static std::string toLowerStr(const std::string& s) {
    std::string r = s;
    for (std::string::size_type i = 0; i < r.size(); ++i) {
        if (r[i] >= 'A' && r[i] <= 'Z') r[i] = static_cast<char>(r[i] - 'A' + 'a');
    }
    return r;
}

static std::string normalizeType(const std::string& t) {
    std::string low = toLowerStr(t);
    if (low == "car") return "Car";
    if (low == "motorcycle") return "Motorcycle";
    if (low == "bicycle") return "Bicycle";
    return "";
}

class Vehicle {
private:
    int vehicleID;
    std::string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;
    bool isOccupied;

public:
    static const int RATE_CAR = 20000;
    static const int RATE_MOTORCYCLE = 10000;
    static const int RATE_BICYCLE = 5000;

    Vehicle()
        : vehicleID(0), vehicleType("Car"), entryTime(0),
          parkingDuration(1), parkingFee(0.0), isOccupied(false) {}

    Vehicle(int id, const std::string& type, int entry, int duration, bool occupied = true)
        : vehicleID(0), vehicleType("Car"), entryTime(0),
          parkingDuration(1), parkingFee(0.0), isOccupied(false) {
        setVehicleID(id);
        setVehicleType(type);
        setEntryTime(entry);
        setParkingDuration(duration);
        isOccupied = occupied;
        calculateFee();
    }

    int getVehicleID() const { return vehicleID; }
    std::string getVehicleType() const { return vehicleType; }
    int getEntryTime() const { return entryTime; }
    int getParkingDuration() const { return parkingDuration; }
    double getParkingFee() const { return parkingFee; }
    bool getIsOccupied() const { return isOccupied; }

    bool setVehicleID(int id) {
        if (id <= 0) return false;
        vehicleID = id;
        return true;
    }
    bool setVehicleType(const std::string& type) {
        std::string t = normalizeType(type);
        if (t.empty()) return false;
        vehicleType = t;
        calculateFee();
        return true;
    }
    bool setEntryTime(int t) {
        if (t < 0 || t > 23) return false;
        entryTime = t;
        return true;
    }
    bool setParkingDuration(int d) {
        if (d < 1 || d > 23) return false;
        parkingDuration = d;
        calculateFee();
        return true;
    }
    void setParkingFee(double fee) { parkingFee = (fee < 0 ? 0 : fee); }
    void setIsOccupied(bool occ) { isOccupied = occ; }

    static bool isValidTimeRange(int entry, int duration) {
        return entry >= 0 && entry <= 23 && duration >= 1 && duration <= 23
               && (entry + duration) <= 24;
    }

    void calculateFee() {
        int rate = 0;
        if (vehicleType == "Car") rate = RATE_CAR;
        else if (vehicleType == "Motorcycle") rate = RATE_MOTORCYCLE;
        else if (vehicleType == "Bicycle") rate = RATE_BICYCLE;
        parkingFee = static_cast<double>(rate) * parkingDuration;
    }

    void display() const {
        std::cout << "    - ID: " << vehicleID
                  << " | Loai: " << vehicleType
                  << " | Gio vao: " << entryTime << "h"
                  << " | Thoi gian do: " << parkingDuration << "h"
                  << " | Phi: " << std::fixed << std::setprecision(0)
                  << parkingFee << " VND" << std::endl;
    }
};

class ParkingLot {
private:
    int parkID;
    char size;
    Vehicle vehicle1, vehicle2, vehicle3;
    bool hasVehicle1, hasVehicle2, hasVehicle3;

    static char normalizeSize(char c) {
        if (c >= 'a' && c <= 'z') return static_cast<char>(c - 'a' + 'A');
        return c;
    }
    static bool isValidSize(char c) { return c == 'S' || c == 'M' || c == 'L'; }
    static int capacityOf(char c) { return c == 'S' ? 1 : (c == 'M' ? 2 : 3); }

public:
    ParkingLot()
        : parkID(0), size('S'),
          hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {}

    ParkingLot(int id, char s)
        : parkID(id), size('S'),
          hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {
        setSize(s);
    }

    int getParkID() const { return parkID; }
    char getSize() const { return size; }
    int getCapacity() const { return capacityOf(size); }
    int getVehicleCount() const {
        return (hasVehicle1 ? 1 : 0) + (hasVehicle2 ? 1 : 0) + (hasVehicle3 ? 1 : 0);
    }
    bool isFull() const { return getVehicleCount() >= getCapacity(); }
    bool isEmpty() const { return getVehicleCount() == 0; }

    bool setParkID(int id) {
        if (id <= 0) return false;
        parkID = id;
        return true;
    }
    bool setSize(char s) {
        s = normalizeSize(s);
        if (!isValidSize(s)) return false;
        int cap = capacityOf(s);
        if (cap < 3 && hasVehicle3) return false;
        if (cap < 2 && hasVehicle2) return false;
        size = s;
        return true;
    }

    bool containsVehicle(int vID) const {
        if (hasVehicle1 && vehicle1.getVehicleID() == vID) return true;
        if (hasVehicle2 && vehicle2.getVehicleID() == vID) return true;
        if (hasVehicle3 && vehicle3.getVehicleID() == vID) return true;
        return false;
    }

    bool displayVehicleIfFound(int vID) const {
        if (hasVehicle1 && vehicle1.getVehicleID() == vID) { vehicle1.display(); return true; }
        if (hasVehicle2 && vehicle2.getVehicleID() == vID) { vehicle2.display(); return true; }
        if (hasVehicle3 && vehicle3.getVehicleID() == vID) { vehicle3.display(); return true; }
        return false;
    }

    bool addVehicle(const Vehicle& v) {
        if (containsVehicle(v.getVehicleID())) return false;
        int cap = getCapacity();
        if (!hasVehicle1) {
            vehicle1 = v; vehicle1.setIsOccupied(true); hasVehicle1 = true;
            return true;
        }
        if (cap >= 2 && !hasVehicle2) {
            vehicle2 = v; vehicle2.setIsOccupied(true); hasVehicle2 = true;
            return true;
        }
        if (cap >= 3 && !hasVehicle3) {
            vehicle3 = v; vehicle3.setIsOccupied(true); hasVehicle3 = true;
            return true;
        }
        return false;
    }

    bool removeVehicle(int vID) {
        if (hasVehicle1 && vehicle1.getVehicleID() == vID) {
            vehicle1 = Vehicle(); hasVehicle1 = false;
            return true;
        }
        if (hasVehicle2 && vehicle2.getVehicleID() == vID) {
            vehicle2 = Vehicle(); hasVehicle2 = false;
            return true;
        }
        if (hasVehicle3 && vehicle3.getVehicleID() == vID) {
            vehicle3 = Vehicle(); hasVehicle3 = false;
            return true;
        }
        return false;
    }

    void displayLotInfo() const {
        std::cout << "Bai do ID: " << parkID
                  << " | Kich thuoc: " << size
                  << " | Suc chua: " << getCapacity()
                  << " | Dang do: " << getVehicleCount() << std::endl;
        if (isEmpty()) {
            std::cout << "    (Bai trong)" << std::endl;
            return;
        }
        if (hasVehicle1) vehicle1.display();
        if (hasVehicle2) vehicle2.display();
        if (hasVehicle3) vehicle3.display();
    }
};
