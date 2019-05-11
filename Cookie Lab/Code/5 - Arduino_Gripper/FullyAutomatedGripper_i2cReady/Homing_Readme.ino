
//      ******************************************************************
//      *                                                                *
//      *   Example of finding the Home position using a limit switch    *
//      *                                                                *
//      *            S. Reifel & Co.                6/24/2018            *
//      *                                                                *
//      ******************************************************************


// Many stepper motor projects need to move to exact positions.  This usually
// requires that the stepper motor library knows where the motor is before it
// makes its first move.  To achieve this automatically, you will use a
// Limit Switch that is pressed by the mechanism when the motor moves
// all-the-way to one end of its travel.  This procedure called "Homing", is
// executed when power is first applied.  A homing program moves the motor
// toward the limit switch until the switch is pressed, then resets the
// library so that the motor is now at position 0.
//
// Home automatically is easily done using one of these functions:
//    moveToHomeInSteps()
//    moveToHomeInRevolutions()
//    moveToHomeInMillimeters()
//
// This example shows how to home your device.  The mechanism in my example has
// a stepper motor with a lead-screw.  On its left side is a limit switch that
// the mechanism bumps into when the motor has reached its left most limit of
// travel.  Note: The switch must be configured to go LOW when pressed at the
// home position.
//
// Documentation at:
//    https://github.com/Stan-Reifel/SpeedyStepper
//
//
// The motor must be connected to the Arduino with a driver board having a
// "Step and Direction" interface.  It's VERY important that you set the
// motor current first!  Read the driver board's documentation to learn how.

// ***********************************************************************

// First you must tell the library "how many steps it takes to move one
// millimeter".  Setup is configured with a lead-screw having
// 25 full-steps/mm and 1x microstepping.
