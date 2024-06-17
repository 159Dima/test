#include <cassert>
#include <string>
#include <iostream>

using namespace std;

class House {
    // Реализуйте самостоятельно
public:
    House(int length, int width, int hight): length_(length), width_(width), hight_(hight){}
    int GetHeight() const {
        return hight_;
    }
    int GetWidth() const{
        return width_;
    }
    int GetLength() const {
        return length_;
    }

private:
    int length_, width_, hight_;
};

class Resources {
    // Реализуйте самостоятельно
public:
    Resources(int brick_count):brick_count_(brick_count){}
    void TakeBricks(int count) {
        if (count < 0 || count > brick_count_) throw std::out_of_range("недостаток керпичей");
        brick_count_ -= count;
    }
    int GetBrickCount() const {
        return brick_count_;
    }
private:
    int brick_count_;
};

struct HouseSpecification {
    int length = 0;
    int width = 0;
    int height = 0;
};

class Builder {
public:
    Builder(Resources& resoursces): resurc_(resoursces){}
    House BuildHouse(HouseSpecification spec) {
        int wail = (spec.length * spec.height * 4 * 8 + spec.width * spec.height * 4 * 8) * 2;
        if (resurc_.GetBrickCount() < wail)throw std::runtime_error("мало керпичей");
        resurc_.TakeBeicks(wail);
        House haus(spec.length, spec.width, spec.height);
        return haus;
    }

private:
    Resources& resurc_;

};

int main() {
    Resources resources{ 10000 };
    Builder builder1{ resources };
    Builder builder2{ resources };

    House house1 = builder1.BuildHouse(HouseSpecification{ 12, 9, 3 });
    assert(house1.GetLength() == 12);
    assert(house1.GetWidth() == 9);
    assert(house1.GetHeight() == 3);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House house2 = builder2.BuildHouse(HouseSpecification{ 8, 6, 3 });
    assert(house2.GetLength() == 8);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House banya = builder1.BuildHouse(HouseSpecification{ 4, 3, 2 });
    assert(banya.GetHeight() == 2);
    cout << resources.GetBrickCount() << " bricks left"s << endl;
}
