Code Architecture
=================

##Core Focii:
* Modularity: The code should not have to be duplicated to be reused in a slightly different manner.
* Testability: Every aspect of the code minus direct hardware access should be able to be verified with lightweight unit tests.
* Legibility: The code should be easy to understand, even for nonprogrammers.
* Robustness: The code should be reliable in performance.

##Out of those focii, these distinct features emerged:
* Dimensional Analysis: No using raw floats or doubles.
* NASA's Big Ten: Partially adapted.
* SOLID: A framework for modular code.
* Nested Config Structs: shorten construtors and make use easier.
* Single Reponsibility Principle: So important it is said twice.
* Doxygen Documentation: Document code... in the code.
* Dependency Injection: Decouple higher level code from lower level specifics.
* Unit Tests: Works in tandem with Dependency Injection.
* TRAProot: taproot wrappers.
* and more.

.. toctree::
    :glob:
    *
