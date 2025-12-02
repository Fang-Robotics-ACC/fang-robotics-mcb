Wrap
====

This directory contains wrappers in order to provide a more uniform system of
accessing various APIs.

RAIL has been designed to be a more "customizable" library where templates can
be used with either primitive or custom types. This is due to some teams using
floats while other teams are using units.h (well, one - us).

units.h is a well-tested library used within a variety of industries. Yes, that
means that there are in fact satellites which rely upon it for calculations.
Because the type system doesn't have the concise names, it has been decided to
create aliases in order that the type handled could be just Seconds instead of
units::time etc.

Traproot (taproot wrappers) were created due to the oddities of taproot.
Taproot has been a godsend for Fang Robotics; nevertheless, the overuse of raw
pointers, out parameters, and the lack of dimensional analysis support meant
that in order to have an organized method of using it, units.h wrappers were
created. This is a zero cost abstraction. Bugs involving dimensional analysis
where a flurry of units are mangled in a log chain of conversion can be
painstaking to locate. By enforcing dimensional consistency, the programmer is
assured that at least the formulas make sense. Units.h also does automatic
conversion between compatible units.
