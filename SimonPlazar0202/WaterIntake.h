#ifndef SIMONPLAZAR0202_WATERINTAKE_H
#define SIMONPLAZAR0202_WATERINTAKE_H

class WaterIntake {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
    float quantity;
public:
    WaterIntake();

    WaterIntake(unsigned int day1, unsigned int month1, unsigned int year1, float quantity1);

    unsigned int getDay() const;

    unsigned int getMonth() const;

    unsigned int getYear() const;

    float getQuantity() const;

    void setQuantity(float quantity2);

    std::string toString() const;

    void addQuantity(float quantity3);
};

#endif //SIMONPLAZAR0202_WATERINTAKE_H
