#include "PhysicalProperty.hpp"

int main() {
    auto time1 = PhysicalProperty<0,0,1>(20.0);
    auto time2 = PhysicalProperty<0,0,1>(10.0f);
    auto speed = PhysicalProperty<1,0,-1>(2.0);
    auto distance = speed * (time1 + time2);
	
    std::cout << "Speed " << speed << " for time " << (time1 + time2) << " is distance " << distance << '\n';
	
    auto force = 200.0_Newtons;
    auto mass = 5.0_kilograms;
    auto acc = force / mass;
    std::cout << "Force " << force << " on mass " << mass << " gives acceleration " << acc << '\n';

    auto energy = 50e3_Joules;
    auto mass2 = 750.0_kilograms;
    auto vel = sqrt(2.0 * energy / mass2);
    std::cout << "Energy " << energy << " applied to mass " << mass2 << " gives velocity change " << vel << '\n';
    
    constexpr auto ft = 0.3048_meters;
    auto three_feet = 3.0 * ft;
    auto minute = 60.0_seconds;
    std::cout << "Three ft/min is " << three_feet / minute << '\n';
    std::cout << "3000rpm is " << 3000.0 / minute << '\n';
}
