Welcome to Fang Robotics MCB

Commit Style
============
We expect all commits to be in this style.
https://www.conventionalcommits.org/en/v1.0.0/

Coding Expections
=================
0. Documentation - code should be self-documenting with comments (if necessary). This includes commits explaning *why* a change is done.
   If you cannot explain *why* a change is occuring, then it was probably not a good change or an ill-planned one. Ask for help on 
   on what you are attempting to fix or improve.
1. Functionality - the code should work.
2. Organization - all functions and classes should have one and only one responsibility. If your class definition exceeds 100 lines,
   it is a general symptom of not-so-good organization. Bundle sub-blocks into *what* is happening. Add comments on *why* something is happening.
3. Testability - all new feature pull requests must have tests as a "proof of work"
4. Modularity - the a reasonable line of code should not necessarily cause fears of catastrophic damage.
   Changes to a specific type functionality should only be done in one place
5. Optimize only when needed - Yes, virtual functions do have slight overhead; however, they offer powerful gains. Nevertheless, it is important
   to acknowledge that something might need to be optimized via or avoiding virtual functions from time to time. All pull requests involving this
   must document a means to ascertain the overhead and the extent of the overhead.

Philosophy
==========

0. Do it at least 80% correctly the 1st time - we balance having standards and maintaining practicality
1. If it is broke, fix it now. (We allow minor formatting errors to be bundled with any type of commit - only minor ones however such as extra lines or spaces).
2. Flag any hacks - during time-critical moments, it may be necessary to do a "hack"; however, these should be flagged in the conventional commit
   as of type "hack" e.g. "hack(feature): fixes [problem]".
3. Really flag any hacks //THIS IS REALLY SUS BECAUSE THAT IS SUS TOO.
4. Branch early, branch often. Try out timelines without consequence, with git we are gods.
5. Bundle complicated things with functions, structs, and classes. (functional programming has its place, but oop exists for a reason).
6. If something feels like an eyesore, it probably is broken or at a high risk of breaking.
7. Take care of yourself - touch grass
8. If there is a good reason to break a rule or principle, break it and document **why**, but know what you are doing.
   If you don't know what you are doing, take the extra time.
9. People are better to ask for help than computers, it helps build **community**, make **friends**, and increase self reliance.
10. A programmer who needs to always look something up every other line or get a programmer (or AI especially) to write it is always less skilled.
11. Take the time to learn. Once you get past the curve, you will find yourself being a god-tier dev!
   

SOLID programming: https://www.geeksforgeeks.org/solid-principle-in-programming-understand-with-real-life-examples/
Design Patterns andhttps://refactoring.guru/
Great Book To Read: https://pragprog.com/titles/tpp20/the-pragmatic-programmer-20th-anniversary-edition/

Coding Style
===========
We use a variant of the Google C++ style: https://google.github.io/styleguide/

## These are the following changes
### Braces
Aligned braces ONLY
```
const char* sensibleBraces()
{
    return "I like Bjarne Stroustrup, but aligned braces (Allman) make too much sense";
}
```

### Variable names
**It is always preferred to make a variable name too long than too short. Code is always read more than it is written, and if you know
how to use tab, you can autocomplete long names.**


Non-const variables shall be mixedCase beginning with lowercase. 
```
double coolVariable{};
```
Const variables shall begin with k. kVariable. This is a departure from the k\_variable convention.

```
const double kEternallyCoolVariable{};
```

### Initialization
Under all circumstances uniform-bracket initialiation shall be used.

```
int count{10};
```

### Enums
After long deliberation, we have noted that C++ standards have been departing from 90s-era C standards.
Due to the issue of preprocessor directives causing an increasing amount of conflicts with anything in SHOUT\_CASE,
a new standard for enums must be adopted.

Google's style of kEnumName, is found to be too cumbersome and unecessarily pedantic as enum classes are accessed as
EnumClassName::enum.

The simple solution is to use lowerMixedCase.
```
enum class Friendliness
{
    befriendAllThings,
    friendly,
    destroy,
    destroyAllThings  
};

robot.setPersonality(Friendliness::befriendAllThings);
```

For enums (which are **heavily** discouranged), the kEnumName is **heavily** encouraged.


### Class
#### Members
##### Member Variables
This is a departure from the learncpp.com style with appending m. It has been found to be cumbersome
in having a constant member variable be named mk\_variable (when signifying immutibility). k\_variable
was reserved for non-member consts. In order to reduce the chance of naming conflicts/shadowing, non-static constant
member variables shall have a k appendend to the beginning of the name and a _ to the end to the end.

All private member variables shall end with \_
```
class Club
{
public:
    static constexpr int kMaxCapacity{10};
private:
    static constexpr int kBudgetRedLimit{1000};
    const int kDanceFloorLength_;
    int peopleCount_;
};
```

##### Static Functions - mixed case beginning with lower case Class::staticFunction()

### Interfaces
Interface Naming Conventions. An interface (purely abstract class with virtual functions), shall be appended with I.
I love taproot, but DjiMotorInterface is more cumbersome than IDjiMotor. It also immediately informs the user that
they are dealing with an abstract class.
```
ICoolInterface& cool{glacier};
```


