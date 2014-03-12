/**
 * A simple Orangutan task scheduler based on a
 * 1000Hz timer.
 *
 * There are currently four tasks:
 *
 * Task1: Set the Green LED, initiated by a pin change interrupt,
 * to the TOP Button state inside the ISR.
 *
 * Task2: Set the Yellow LED, initiated by the timer,
 * to the Bottom Button state released by the Scheduler.
 * (Note: this currently simulates a Yellow LED by writing
 * to the LCD. Adjust the 'poll_bottom_button' function to
 * point to whatever external LED you are using.)
 *
 * Task3: Toggle the Red LED, initiated by the timer,
 * released by the Scheduler.
 *
 * Task4: A timer-based, 1000Hz task scheduler.
 */
#include <pololu/orangutan.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile char green_led_on = 0;
volatile char red_led_on = 0;

volatile uint16_t counter = 0;

#define BIT(b) (1 << (b))

// simple Task representation
typedef struct Task {
	uint16_t period;
	void (*interrupt_function)(void);
	char released;
	char* name;
} Task;

void toggle_red_led();
void poll_bottom_button();

#define NUM_TASKS 2

Task poll_bottom_button_task = { .period = 250, .interrupt_function =
		&poll_bottom_button, .released = 0, .name = "Poll Bottom Button" };

Task toggle_red_led_task = { .period = 500, .interrupt_function =
		&toggle_red_led, .released = 0, .name = "Toggle Red LED" };

Task* tasks[NUM_TASKS];

int main() {
	tasks[0] = &poll_bottom_button_task;
	tasks[1] = &toggle_red_led_task;

	clear();
	green_led(0);
	red_led(0);

	// timer interrupt
	TIMSK3 = BIT(OCIE3A);
	TCCR3A = BIT(COM3A1);
	TCCR3B = BIT(CS32) | BIT(CS30) | BIT(WGM32);
	OCR3A = 20;

	// pin change interrupt
	PCICR = BIT(PCIE2);
	PCIFR = BIT(PCIF2);
	PCMSK2 = BIT(PCINT21);

	sei();

	while (1) {
		int i;
		for (i = 0; i < NUM_TASKS; i++) {
			Task* task = tasks[i];
			if (task->released) {
				task->interrupt_function();
				task->released = 0;
			}
		}
	}
}

// toggle green LED on button pin change and top button press
ISR(PCINT2_vect) {
	green_led(button_is_pressed(TOP_BUTTON));
}

// assume a 1000 tick hyperperiod -- release tasks (jobs) as necessary
ISR(TIMER3_COMPA_vect) {
	if (counter == 1000) {
		counter = 0;
	}

	int i;
	for (i = 0; i < NUM_TASKS; i++) {
		Task* task = tasks[i];
		// release a job at the start of its period
		if (task->period && (counter % task->period == 0)) {
			task->released = 1;
		}
	}

	counter++;
}

// toggle the red LED
void toggle_red_led() {
	red_led_on = ~red_led_on;
	red_led(red_led_on);
}

// turn on (simulated) yellow LED if bottom button is pressed
void poll_bottom_button() {
	clear();
	if (button_is_pressed(BOTTOM_BUTTON)) {
		print("Yellow LED ON");
	} else {
		print("Yellow LED OFF");
	}
}
