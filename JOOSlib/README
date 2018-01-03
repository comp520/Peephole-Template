The JOOS library forms a way of interfacing JOOS to the functionality 
supported in Java.   Typically the libarary exists in order to access
constants,  static methods,  static fields,  or to handle other restrictions
enforced by JOOS. 

The JOOS library can be found in the subdirectory joos/lib and it currently
consists of:

JoosConstants.java   - we don't support constants in joos,  so this is
                       a way of extracting constant values from Java libs.

                       for example,  new JoosConstants.black()
                           returns the constant Color.black

                       look in the file $JOOSDIR/joos/lib/JoosConstants.java
                       to see the exact name of each constant.  Usually it
                       is the same name as in the Java class, except where
                       the same name is used in more than one Java class.

JoosContainer.java   - a wrapper for the java Container class.  This provides
                       two different names for overloaded "add" method
                       of Container.  The JOOS versions are
                       addString, and addPosition.

JoosDimension.java   - a wrapper for the java Dimension class.  This provides
                       methods to set and get the values of the height and
                       width fields.

JoosEvent.java       - a wrapper for the java Event class.  This provides
                       methods to get and set fields of an Event.

JoosException.java   - defines a new runtime exception that is called
                        from Joos library routines.  This does not need
                        to be made visible to JOOS programs.  

JoosFraction.java    - a new class that stores a numerator and denominator
                         of a fraction.   We need this because we don't have
                         real numbers in JOOS.  Thus we can carry around
                         JoosFractions in JOOS programs, and then have 
                         other library routines convert into doubles when
                         accessing Java methods.

JoosGridBagConstraints.java
                     - a wrapper for the java GridBagConstraints class, it
                       provides methods for setting and reading fields.  Note
                       that setWeightX and setWeightY use JoosFractions to
                       translate into doubles. 

JoosIO.java          - a VERY Basic IO library.  The java IO library is quite
                       complex.  This provides a very simple way of reading
                       and printing values. 
                           See $JOOSDIR/Progs/Simple/TestIO.java for some
                       simple examples,  and
                           see $JOOSDIR/Progs/Simple/TestIOlist.java a more
                            complex example that tokenizes many input
                            entries on one line.


JoosMediaTracker.java - a wrapper for the java MediaTracker class.  This is
                        required because the MediaTracker events waitForAll
                        and waitForID can raise InterruptedExceptions. 
                        Since JOOS does not support Exceptions, we provide
                        new versions of waitForAll and waitForID that return
                        true if an interruption occurs, and false otherwise.


JoosObject.java       - a wrapper for the java Object class.  Provides a 
                        new version of the wait method that returns true
                        if interrupted, and false otherwise.

JoosRectangle.java    - a wrapper for the java Rectangle class.  

JoosRunnable.java

JoosString.java      - String ops that let you capture a string and
                           convert it back to integer, boolean or String.

JoosSystem.java

JoosThread.java

JoosURL.java

WigApplet.java

