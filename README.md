mini-scheduler
==============
A simple Orangutan task scheduler based on a 1000Hz timer.

There are currently four tasks:

* **Task1:** Set the Green LED, initiated by a pin change interrupt, to the TOP Button state inside the ISR.
	* **Note:** This uses the onboard green LED.
 
* **Task2:** Set the Yellow LED, initiated by the timer, to the Bottom Button state released by the Scheduler.
	* **Note:** LED should be put in C1.
 
* **Task3:** Toggle the Red LED, initiated by the timer, released by the Scheduler.
	* **Note:** This uses the onboard red LED.
 
* **Task4:** A timer-based, 1000Hz task scheduler.


Compiling/Programming
---------------------
In the root directory:
```
make
```

```
make program
```
