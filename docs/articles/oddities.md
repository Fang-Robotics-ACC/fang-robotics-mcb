Oddities
========

There awesome odd things in the code base that you need to look out for. The 
current ones related to smart pointers and FANG\_ASSERT.

## Smart Pointers

Smart pointers are passed into the constructor via std::move()

```cpp

Constructor(std::unique_ptr<Type>() object) : object_{std::move(object)}
{
}
```
The constructor needs to pass a **smart** pointer via value instead of l-value 
reference, address, or r-value reference.

This is important because it shows the caller of the constructor that their 
variables are being moved into the parameters when being used as arguments. In 
addition, the variables being initialized within the class are clearly being 
initialized via moving instead of copy or reference.

It guarantees and shows that guarantee that move semantics are being used.

### Stack Overflow explanation

https://stackoverflow.com/questions/75800644/passing-stdunique-ptr-to-constructor-through-r-value-reference

"Don't use std::unique\_ptr at all where no transfer is intended (use a raw 
pointer, or perhaps a reference if it's guaranteed non-null). If ownership may 
or may not be transferred, depending on something unknown at compile-time, then 
that's the single (and exceedingly rare) use for passing by rvalue-reference. 
I've never needed to do that in my entire career."

When passing via reference, it is unclear if the pointer is moved. Although 
passing by r-value reference allows a move, it does not necessarily trigger a 
complete move.

Since the initialized member variables also require the pointer to use 
std::move(), it makes it clear that the object is obtaining the pointer (since 
the r-value reference type is not clear in the constructor parameter name). 
std::move().

When the constructor is called, std::move() also makes it explicit.

"One specific benefit to passing by value is that if the constructor throws 
before its data is assigned, the temporary copy in the parameter will get 
destructed, and we don't end up failing to move from the caller.

But the main benefit is clarity - instead of readers asking why we're taking a 
reference to the caller's pointer, we simply do the obvious and expected thing.

When passing by value, the target object is definitely no longer owned by the 
caller. When passed by reference, we don't know whether the new A has taken 
ownership or not, unless we inspect A's implementation."

In simpler terms, B() is unequivocally a sink, whereas A() may or may not be."

## FANG\_ASSERT

Asserts are one of the major points within NASA's Big 10 rules in safety 
critical code. Unfortunately, assertions within embedded are a lot more 
difficult. While within a normal environment, they would provide the error 
message as well as the location of the error, within the embedded environment, 
it is not so clear.

FANG\_ASSERTS evaluate to a regular assertion when used in a testing 
environment (hosted on a PC). The assertion with provide the file name as well 
as the line number where it failed.

```cpp
void modm_abandon(const modm::AssertionInfo &info)
{
    //This forces the debugger to see it via copy constructor
    static modm::AssertionInfo readInfo = info; 
    //TODO: write to terminal or buzz in morse code
    fang::Drivers& drivers{fang::DriversSingleton::getDrivers()};
    fang::emergency::killSystem();

    fang::error::playFailedAssertBuzz(drivers.pwm);

    FREEZE_SYSTEM();
}
```
However, when in an embedded environment, FANG\_ASSERT becomes a modm\_assert 
which will eventually be evaluated to the modm\_abandon() function.

The assertion info can be piped to UART or any method of communication. At the 
time of writing this article, it is in the process of being implemented.

## Virtual Declaration when two base classes have the same virtual function

https://stackoverflow.com/questions/1313063/request-for-member-is-ambiguous-in-g

```cpp
class HolonomicSubsystem:
        public IHolonomicDrive,
        public tap::control::Subsystem
    {
    public:
        HolonomicSubsystem(Drivers& drivers) : Subsystem{&drivers}
        {}

        //Prevent ambiguity error since multiple ancestors have initialize()
        virtual void initialize() override = 0;
        virtual ~HolonomicSubsystem() {};
    };
```
If HolonomicSubsystem does not have an explicit override for initialize(), it 
leads to compilation errors because void initialize() is defined in both classes 
it inherits from.

Please note that we are not overly abusing inheritance as IHolonomicDrive is a 
purely abstract class.

This is the interface that it uses for meshing with commands so that different 
holonomic drives can be used for the same command


```cpp
template <class Velocity, class AngularVelocity>
class IHolonomicDrive:
    virtual public IHolonomicControl<Velocity, AngularVelocity>,
    virtual public system::ISystem
{
public:
    virtual ~IHolonomicDrive() {};
};
```
initialize() is defined in ISystem.

```cpp
class Subsystem
{
public:
    Subsystem(Drivers* drivers);

    virtual ~Subsystem();

    /**
     * Called once when you add the Subsystem to the commandScheduler stored in the
     * Drivers class.
     */
    virtual void initialize() {}
```
initialize() is defined in Subsystem

So in order to provide the compiler a correct definition, it has to be 
explicitly defined in IHolonomicSubsystem (this is required due to taproot 
commands requiring taproot Subsystem registration).

When MecanumDrive's initialize() is called when casted as a Subsystem or an 
IHolonomicDrive, the same initialize() is called.
