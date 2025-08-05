Dependency Injection Basics
===========================

Dependency injection is a common design pattern within programming. Although
its name may sound harrowing, it's quite a simple pattern. If you have worked 
with legos or the wall outlet, then proper dependency injection will be easy to 
understand.

In programming, there are variou levels of abstracts. Let's take, for example, a 
class which manages 4 motors called a QuadDrive. Traditionally, the QuadDrive 
would have 4 instances of objects which are drivers for motors such as the DJI 
M3508 or the Repeat Ultra MK 2. These would be private variables.

.. code-block:: cpp

  /**
   * Doxygen detectable comment :D
   */
  class QuadDrive
  {
  public:
      QuadDrive() {}
      void setWheelSpeeds(const QuadRPM& wheelSpeeds);
  private:
      Motor frontLeft_{};
      Motor frontRight_{};
      Motor rearLeft_{};
      Motor rearRight_{};
  };

This obeys the general principles of encapsulation and single responsibility.

However, what if you desired a QuadDrive with a different combo of motors? What 
if you wanted to test the QuadDrive to verify its functionality. Given the 
nature of the QuadDrive, it itself does not output any data to test with 
traditional unit tests. Another approach must be utilized.

There are some important things to note here: 1. A QuadDrive only sets the
speeds of the motors. It provides a way to encapsulate the responsibility of
the lifetime of the motors as well. 2. The QuadDrive can function with any
motor which can set the wheel speeds.

What if instead of having a hardcoded Motor type, the QuadDrive could take in 4 
motors of any kind as long as their speed could be set? Let us create a pure 
abstract class called ISpeedMotor. (I stands for interface, a class with no 
concrete functions which must be implemented by those which inherit from it. 
This allows collections of many objects which may behave in different ways but 
still essentially do the same category of thing.)

.. code-block:: cpp

  class ISpeedMotor
  {
  public:
      // There are glitches when use = default with
      //interfaces
      virtual ~ISpeedMotor(){}  void setSpeed(const RPM& speed) = 0;
  };

And what if our QuadDrive utilized that class? And took 4 motors within its 
constructor?
  
.. code-block:: cpp

  /**
   * Doxygen detectable comment :D
   */
  class QuadDrive
  {
  public:
      QuadDrive
      (
           std::unique_ptr<ISpeedMotor> frontLeft,
           std::unique_ptr<ISpeedMotor> frontRight,
           std::unique_ptr<ISpeedMotor> rearLeft,
           std::unique_ptr<ISpeedMotor> rearRight
      ):
          // Be carefful to move with frontLeft or lese
          // A segmentation error will occur when it is used
          frontLeft_{std::move(frontLeft)},
          frontRight_{std::move(frontRight)}, 
          rearLeft_{std::move(rearLeft)},
          rearRight_{std::move(rearRight)}
      {}
      void setWheelSpeeds(const QuadRPM& wheelSpeeds);
  private:
      std::unique_ptr<ISpeedMotor> frontLeft_;
      std::unique_ptr<ISpeedMotor> frontRight_;
      std::unique_ptr<ISpeedMotor> rearLeft_;
      std::unique_ptr<ISpeedMotor> rearRight_;
  };

Although, generally, we will create instances with a uniform type of motor, this 
is to demonstrate the power of dependency injectoin

.. code-block:: cpp

  std::unique_ptr<DjiM3508> m3508{};
  std::unique_ptr<RepeatUltraMk2> ultra{};
  std::unique_ptr<DjiGM06020> gm6020{};
  // A mock class may be used for proper function calls
  std::unique_ptr<TestMotor> test{};

  //Note: that we can use pass an anonymous instance directly, but for 
  //demonstrative purposes and a clearer syntax for the beginner
  QuadDrive quad
  {
      std::move(m3508),
      std::move(ultra),
      std::move(gm6020),
      std::move(test)
  };

Don't know about std::move() or move semantics? Check `this
<https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/>`_
out! Note that we are messing with dynamic memory so that the memory does not
need to be bound to an external instance. Once it is "moved", the quad instance
owns it and is solely responsible for deleting it/figuring out what to do with
it or who to let see it. If we utilized the stack, encapsulation would not be
respected. On performance, the only hit is on object creation, references and
pointers have the same performances, it's just that references are a lot safer
for non-owning instaces since it guards against null and other raw pointer
shenaigans.

This might seem tedious, but classes or factory functions can be automated to 
create the most common "variants" of QuadDrive (variant is a term used in 
fang-robotics-mcb and not in common programming jargon (yet). It just means a 
instance of a class which utilizes dependency injection. So an M3508QuadDrive 
can be made.

Check out this example from the codebase itself!

This uses the Variant Class design pattern in which a class inherits from a 
dependency injection class (so that it itself may be used as an instance of that 
class for convenience) who only initializes the class within its constructor.

.. code-block:: cpp

    class UltraMk2BaseQuaddrive : public BaseQuadDrive
    {
    public:
        using Motor = motor::RepeatUltraMk2;
        struct Config
        {
            Motor::Config frontLeftConfig;
            Motor::Config frontRightConfig;
            Motor::Config rearLeftConfig;
            Motor::Config rearRightConfig;
        };

        UltraMk2BaseQuaddrive(Drivers& drivers, const Config& config):
            BaseQuadDrive
            {
                drivers,
                std::make_unique<Motor>(config.frontLeftConfig),
                std::make_unique<Motor>(config.frontRightConfig),
                std::make_unique<Motor>(config.rearLeftConfig),
                std::make_unique<Motor>(config.rearRightConfig)
            }
        {
        }
    };

Note that since that the unique_ptr instances from std::make_unique() are 
anonymous (they have no names attached to them), they are considered r-values, 
which may sound useless since they pop out of existence almost immediately until 
one relize that in the case of dynamic memory management, they are safe to 
"steal" from since they are going out of scope. This ensures that the thief 
class or function will not delete memory which might need to be used afterwards 
because its owner is pretty much non-existence within the next cycle (ish, Tron 
reference ahhh).

`This article <https://vladris.com/blog/2016/07/06/dependency-injection-in-c.html>`_ goes
more in depth.
