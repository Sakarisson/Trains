#ifndef DISTANCE_H
#define DISTANCE_H

class StationMap {
public:
    StationMap(std::string name) : _name(name) {}
    void addDistance(std::string&, int&);
private:
    std::string _name;
    std::vector<Distance> _distances;
};

class Distance {
public:
    Distance(std::string to, int distance)
        : _to(to), _distance(distance) {}
    int getDistance() const;
    std::string getStationName() const { return _to; }
private:
    std::string _to;
    int _distance;
};

//class DistanceManager {
//public:
//
//private:
//    std::vector<Distance> _distances;public:
//    DistanceManager() {}
//    void addDistance(std::string&, std::string&, int distance);
//    int getDistance(std::string& a, std::string& b) {
//        auto it = std::find_if(_distances.begin(), _distances.end(), [station](Distance& d) { return d.getStationName() == station; });
//        if (it != _distances.end()) {
//            return (*it).getDistance();
//        }
//        else {
//            return 0;
//        }
//    }
//};

#endif // !DISTANCE_H
