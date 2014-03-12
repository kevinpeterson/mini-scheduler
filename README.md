mini-scheduler
==============
A simple Orangutan task scheduler based on a 1000Hz timer.

There are currently four tasks:

* Task1: Set the Green LED, initiated by a pin change interrupt,
 to the TOP Button state inside the ISR.

* Task2: Set the Yellow LED, initiated by the timer,
to the Bottom Button state released by the Scheduler.
(Note: this currently simulates a Yellow LED by writing
to the LCD. Adjust the 'poll_bottom_button' function to
point to whatever external LED you are using.)

* Task3: Toggle the Red LED, initiated by the timer,
released by the Scheduler.

* Task4: A timer-based, 1000Hz task scheduler.
