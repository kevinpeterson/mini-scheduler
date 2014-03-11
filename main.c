#include <pololu/orangutan.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile char green_led_on = 0;
volatile char red_led_on = 0;
volatile char yellow_led_on = 0;

volatile uint16_t counter = 0;

#define BIT(b) (1 << (b))

typedef struct Task {
	uint16_t period;
	void (*interrupt_function)(void);
	char released;
	char* name;
} Task;

void poll_for_button_push();
void toggle_red_led();
void button_push_interrupt();

#define NUM_TASKS 3

Task push_button_task = { .period = 0, .interrupt_function =
		&button_push_interrupt, .released = 0, .name = "Push Button" };

Task poll_button_task = { .period = 250, .interrupt_function =
		&poll_for_button_push, .released = 0, .name = "Poll Button" };

Task toggle_red_led_task = { .period = 500, .interrupt_function =
		&toggle_red_led, .released = 0, .name = "Toggle Red LED" };

Task* tasks[NUM_TASKS];

int main() {
	tasks[0] = &push_button_task;
	tasks[1] = &poll_button_task;
	tasks[2] = &toggle_red_led_task;

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

// release the push_button task on button pin change
ISR(PCINT2_vect) {
	push_button_task.released = 1;
}

// assume a 1000 tick hyperperiod -- release tasks (jobs) as necessary
ISR(TIMER3_COMPA_vect) {
	if (counter == 1000) {
		counter = 0;
	}

	int i;
	for (i = 0; i < NUM_TASKS; i++) {
		Task* task = tasks[i];
		if (task->period && (counter % task->period == 0)) {
			task->released = 1;
		}
	}

	counter++;
}

void poll_for_button_push() {
	green_led(button_is_pressed(BOTTOM_BUTTON));
}

void toggle_red_led() {
	red_led_on = ~red_led_on;
	red_led(red_led_on);
}

void button_push_interrupt() {
	clear();
	if (yellow_led_on) {
		print("Yellow LED ON");
	} else {
		print("Yellow LED OFF");
	}
	yellow_led_on = ~yellow_led_on;
}
