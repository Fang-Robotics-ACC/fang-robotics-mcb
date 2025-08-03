Code Architecture
=================

Code Architecture is an often neglected an misunderstood aspect of programming 
design. There is seldom one correct ideal way to accomplish every goal. To begin 
understand why Fang Robotics MCB is structured the way it is, let us examine 
these aspects.

Core Focii:

* Modularity: *The code should not have to be duplicated to be reused in a*
  *slightly different manner.*
* Testability: *Every aspect of the code minus direct hardware access should be* 
  *able to be automatically verified and documented with lightweight unit tests.*
* Legibility: *The code should be easy to understand, even for nonprogrammers.*
  *Code is read more than it is written.*
* Robustness: *The code should be reliable in performance.*

Out of those focii, these distinct features emerged:

* Dimensional Analysis: *No using raw floats or doubles*
* NASA's Big Ten: *How to write code that doesn't crash (partially adapted)*
* SOLID: *A framework for modular code*
* Nested Config Structs: *Shorten construtors and make configuration more*
  *organized*
* Single Reponsibility Principle: *So important it is said twice*
* Doxygen Documentation: *Document code... in the code*
* Dependency Injection: *Decouple higher level code from lower level specifics*
* Unit Tests: *Test code... with code... Works in tandem with Dependency*
  *Injection*
* TRAProot: *Taproot wrappers with dimensional analysis and polymorphism*
* RAIL: *Uniform abstraction interfaces with testing mocks*
* And more!

.. toctree::
    :glob:

    */index
