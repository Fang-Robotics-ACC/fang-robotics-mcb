Class Variant Design Pattern
=============================

When a class is created through dependency injection, it is often preferable to 
automated the most commonly created configurations.

Within tradition DI with languages such as Java, this is done through factory 
functions; however, in C++, this means that it can only be instantiated as a 
pointer or smart pointer, which limits options.

The solutions was to create a class, which the created instance was composed 
inside, whose lifetime would be tied to that of the variant class.

One option was to have a get() function which would be cumbersome, the other was 
through inheritance since that instance could them be used as the original 
class.

**The example below explains the common components of a "Variant" which 
automates the creation of an object which relies on dependents so that the 
lifetime of the object is tied to it (so that it can be used as a normal 
variable) and that the object can be used as that an instance of that class.**

Often this allows the variant to require not passing of dependents.

Inheritance is preferable since it reduces the need to write boilerplate code 
which would have been doThis() {instance.doThis();}

SimpleAmmoBooster takes two fywheel systems (which in this case are variables of 
IFlywheel Notice that PierceAmmoBooster takes in the configuration for those 
motors, instantiates them and can be used as a regular variable or be used with 
a unique\_pointer to be passed into another constructor.

Sometimes it seem cumbersome to have so many configuration structs rely on 
others. Configuring a massive system will require the same amount of variables 
regardless. The other alternative is hardcoding with global or static variables, 
having a massive constructor, or a large struct.


```cpp
// Notice that this inherits SimpleAmmoBooster over composition
// since it makes sense to automate the boilerplate code
// the "is a" relationship of inheritance makes more sense
// when worded as "can be used as a"
class PierceAmmoBooster : public SimpleAmmoBooster
{
public:
    // This uses another class
    // using Flywheel = M3508BasicFlywheel;

    // The class handles the configuration of both flywheels
    struct Config
    {
        MetersPerSecond ammoVelocity;
        Flywheel::Config leftFlywheelConfig;
        Flywheel::Config rightFlywheelConfig;
    };

    // The constructor handles common dependencies (drivers) and the
    // configuration struct
    PierceAmmoBooster(Drivers& drivers, const Config& config):
        // This is where the actual ammo booster is "instantiated"
        SimpleAmmoBooster
        {
            drivers,
            makeFlywheels(drivers, config), //the flywheels are passed via a 
            // maker function
            {config.ammoVelocity}
        }
    {
    }
private:
    /**
     * We cannot copy and std::initializer_list is kinda mid at this
     * So we must do this hack
     */
    static Flywheels makeFlywheels(Drivers& drivers, const Config& config)
    {
        // In some cases, it is more convenient to have a maker function
        // which automates the creation of dependencies then passes a
        // constructed form

        // Flywheels is a collction of individual Flywheels, generalizing
        // the case where varying numbers are used

        Flywheels flywheels{};
        flywheels.push_back(std::make_unique<Flywheel>(drivers, 
        config.leftFlywheelConfig));
        flywheels.push_back(std::make_unique<Flywheel>(drivers, config.rightFlywheelConfig));
        return flywheels;
    };

};
```
