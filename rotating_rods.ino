/*
 * Rotating Rods - 22 large vertical rods (X aluminum profiles) rotates to create visual patterns.
 * Based on Dan Reisinger's artwork.
 *
 * Wiring:
 *   https://docs.google.com/presentation/d/1KEq_qDWCliBDza_pi2NsCsC85T2rr4le3yrmxQ1LMs4/edit?usp=sharing
 *   ┌────────┬─────────────────────────────────────────┬──────────────────┐
 *   │ Axis   | Driver                                  │ Sensor           │
 *   ├────────┼──────┬──────┬──────┬──────┬──────┬──────┼─────┬─────┬──────┤
 *   │        │ PUL+ │ PUL- │ DIR+ │ DIR- │ ENA+ │ ENA- │ BLU │ BRN │ BLK  │
 *   ├────────┼──────┼──────┼──────┼──────┼──────┼──────┼─────┼─────┼──────┤
 *   │     00 │ 0D04 │ -5V  │ 0D03 │ -5V  │ 0D02 │ -5V  │ -5V │ +5V │ 0A00 │
 *   │     01 │ +5V  │ 0D07 │ 0D06 │ -5V  │ 0D05 │ -5V  │ -5V │ +5V │ 0A01 │
 *   │     02 │ +5V  │ 0D10 │ 0D09 │ -5V  │ 0D08 │ -5V  │ -5V │ +5V │ 0A02 │
 *   │     03 │ +5V  │ 0D13 │ 0D12 │ -5V  │ 0D11 │ -5V  │ -5V │ +5V │ 0A03 │
 *   │     04 │ 1D04 │ -5V  │ 1D03 │ -5V  │ +5V  │ 1D02 │ -5V │ +5V │ 1A00 │
 *   │     05 │ +5V  │ 1D07 │ 1D06 │ -5V  │ 1D05 │ -5V  │ -5V │ +5V │ 1A01 │
 *   │     06 │ +5V  │ 1D10 │ 1D09 │ -5V  │ 1D08 │ -5V  │ -5V │ +5V │ 1A02 │
 *   │     07 │ +5V  │ 1D13 │ 1D12 │ -5V  │ 1D11 │ -5V  │ -5V │ +5V │ 1A03 │
 *   │     08 │ 2D04 │ -5V  │ +5V  │ 2D03 │ 2D02 │ -5V  │ -5V │ +5V │ 2A00 │
 *   │     09 │ +5V  │ 2D07 │ 2D06 │ -5V  │ 2D05 │ -5V  │ -5V │ +5V │ 2A01 │
 *   │     10 │ +5V  │ 2D10 │ 2D09 │ -5V  │ 2D08 │ -5V  │ -5V │ +5V │ 2A02 │
 *   │     11 │ +5V  │ 2D13 │ 2D12 │ -5V  │ 2D11 │ -5V  │ -5V │ +5V │ 2A03 │
 *   │     12 │ 3D04 │ -5V  │ +5V  │ 3D03 │ +5V  │ 3D02 │ -5V │ +5V │ 3A00 │
 *   │     13 │ +5V  │ 3D07 │ 3D06 │ -5V  │ 3D05 │ -5V  │ -5V │ +5V │ 3A01 │
 *   │     14 │ +5V  │ 3D10 │ 3D09 │ -5V  │ 3D08 │ -5V  │ -5V │ +5V │ 3A02 │
 *   │     15 │ +5V  │ 3D13 │ 3D12 │ -5V  │ 3D11 │ -5V  │ -5V │ +5V │ 3A03 │
 *   │     16 │ +5V  │ 4D04 │ 4D03 │ -5V  │ 4D02 │ -5V  │ -5V │ +5V │ 4A00 │
 *   │     17 │ +5V  │ 4D07 │ 4D06 │ -5V  │ 4D05 │ -5V  │ -5V │ +5V │ 4A01 │
 *   │     18 │ +5V  │ 4D10 │ 4D09 │ -5V  │ 4D08 │ -5V  │ -5V │ +5V │ 4A02 │
 *   │     19 │ +5V  │ 4D13 │ 4D12 │ -5V  │ 4D11 │ -5V  │ -5V │ +5V │ 4A03 │
 *   │     20 │ +5V  │ 5D04 │ 5D03 │ -5V  │ +5V  │ 5D02 │ -5V │ +5V │ 5A00 │
 *   │     21 │ +5V  │ 5D07 │ 5D06 │ -5V  │ 5D05 │ -5V  │ -5V │ +5V │ 5A01 │
 *   └────────┴──────┴──────┴──────┴──────┴──────┴──────┴─────┴─────┴──────┘
 *   * Connect 2pcs 2KOhm pullup resistors from +5V to 0DA4 (SDA) and 0DA5 (SCL).
 *
 * I2C commands: [cmd_start, cmd_id, cmd_args]
 *   cmd_start:
 *     0x55.
 *   cmd_id:
 *     1: homing.
 *     2: set axes quadrants [q0, s0, q1, s1, q2, s2, q3, s3] (q=quadrant, s=speed).
 *   cmd_args:
 *     [quadrant bits]:
 *       7-2: rotations      - 0=the fastest direction, >0=right, <0=left.
 *       1-0: quadrant index - 0=home=0°, 1=90°, 2=180°, 2=270°.
 *     [speed]:
 *       0-255 the greater the faster.
 *
 * arad.rgb@gmail.com 19/02/2022.
 */

#include <Arduino.h>
#include <Wire.h>
#include <AccelStepper.h>							// https://github.com/waspinator/AccelStepper.git

#define SERIAL_BAUD_RATE				(115200)	// debug UART baudrate
#define AXIS_ENA_PIN					(2)			// pins (2 + 3n) connected to stepper driver ENAs
#define AXIS_DIR_PIN					(3)			// pins (3 + 3n) connected to stepper driver DIRs
#define AXIS_PUL_PIN					(4)			// pins (4 + 3n) connected to stepper driver PULs
#define AXIS_LMT_PIN					(A0)		// pins (A0 + n) connected to limit (home) sensor
#define AXIS_PER_ARDUINO				(4)			// max 4 axes (stepper motor drivers) per arduino UNO
#define AXIS_TOTAL_COUNT				(22)		// total axes in the exhibit
#define AXIS_SPEED						(250*8)		// max axis speed (10 - 2550) steps per seconds (if CMD_SPEED_SCALE = 10)
#define AXIS_ACCELERATION				(100*6)		// acceleration and deceleration rate
#define AXIS_STEPS_PER_REVOLUTION		(1600)		// must match the stepper driver DIP switch configuration
#define AXIS_HOMING_OFFSET				(70)		// steps offset of the sensor reading to the axis alignment
#define AXIS_HOMING_TIMEOUT_MS			(6000)		// amount of time for all axes to be at home after homing cmd
#define AXIS_QUADRANT_COUNT				(4)
#define AXIS_STEPS_PER_QUADRANT			(AXIS_STEPS_PER_REVOLUTION / AXIS_QUADRANT_COUNT)
#define CMD_START						(0x55)
#define CMD_SPEED_SCALE					(10)
#define ARDUINO_COUNT					((AXIS_TOTAL_COUNT + AXIS_PER_ARDUINO - 1) / AXIS_PER_ARDUINO)
#define NL								"\n"

enum {
	AXIS_STATUS_IDLE = 0,
	AXIS_STATUS_HOMING1,
	AXIS_STATUS_HOMING2,
	AXIS_STATUS_STUCK,
};

enum {
	CMD_NONE = 0,
	CMD_SET_AXES_QUADRANTS,
	CMD_HOMING,
	CMD_COUNT,
};

typedef struct {
	uint8_t index;
	uint8_t status;
	AccelStepper *motor;
} axis_t;

typedef struct {
	uint8_t id;
	union {
		uint8_t args[8];
		struct {
			uint8_t index:2;
			int8_t rotations:6;
			uint8_t speed;
		} set_axis_args[4];
	};
} cmd_t;

const uint8_t CMD_ARGS_COUNT[CMD_COUNT] = {8, 0};

cmd_t *cmds;
axis_t *axes;
uint8_t arduino_id;

// add the "<<" operator to Serial and other objects inherited from Print class
template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }

bool is_axis_home(axis_t *axis)
{
	return !digitalRead(AXIS_LMT_PIN + axis->index);
}

void handle_axes_homing()
{
	Serial << "Homing..." << NL;

	// set axes to rotate a bit away from home if needed
	for (axis_t *axis = axes; axis->motor; axis++) {
		axis->motor->setCurrentPosition(0);
		axis->motor->enableOutputs();
		if (is_axis_home(axis)) {
			Serial << "  axis: " << axis->index << " is already home, rotating..." << NL;
			axis->motor->moveTo(-AXIS_STEPS_PER_REVOLUTION / 8);
		}
	}

	// wait for axes to rotate away
	for (bool running = true; running;) {
		running = false;
		for (axis_t *axis = axes; axis->motor; axis++) {
			axis->motor->run();
			running |= axis->motor->isRunning();
		}
	}

	// set axes to rotate 1.5 revolutions
	for (axis_t *axis = axes; axis->motor; axis++) {
		if (is_axis_home(axis)) {
			axis->motor->disableOutputs();
			axis->status = AXIS_STATUS_STUCK;
			Serial << "  axis: " << axis->index << " is still home, is it stuck?!" << NL;
		}
		else {
			axis->motor->moveTo(AXIS_STEPS_PER_REVOLUTION * 1.5);
			axis->status = AXIS_STATUS_HOMING1;
		}
	}

	// wait for axes to reach home, and go back home if it overshoot
	for (bool running = true; running;) {
		running = false;
		for (axis_t *axis = axes; axis->motor; axis++) {
			if (axis->status == AXIS_STATUS_HOMING1) {
				if (is_axis_home(axis)) {
					axis->motor->move(AXIS_HOMING_OFFSET);
					axis->status = AXIS_STATUS_HOMING2;
				}
			}
			else if (axis->status == AXIS_STATUS_HOMING2) {
				if (!axis->motor->isRunning()) {
					axis->motor->disableOutputs();
					axis->motor->setCurrentPosition(0);
					axis->status = AXIS_STATUS_IDLE;
					Serial << "  axis: " << axis->index << " is home!" << NL;
					continue;
				}
			}
			else
				continue;
			running |= axis->motor->isRunning();
			axis->motor->run();
		}
	}

	// report all homeless axes
	for (axis_t *axis = axes; axis->motor; axis++) {
		if ((axis->status == AXIS_STATUS_HOMING1) || (axis->status == AXIS_STATUS_HOMING2)) {
			axis->motor->disableOutputs();
			axis->status = AXIS_STATUS_STUCK;
			Serial << "  axis: " << axis->index << " didn't made it home!" << NL;
		}
	}

	if (arduino_id)
		Serial << "Done homing!" << NL;
}

void i2c_on_receive(int len)
{
	Serial << "I2C received " << len << " bytes:" << NL;

	if (cmds->id) {
		Serial << "  still processing old cmd id: " << cmds->id << '!' << NL;
		return;
	}

	len = Wire.read();
	if (len != CMD_START) {
		Serial << "  wrong cmd start: " << len << '!' << NL;
		return;
	}

	uint8_t cmd_id = Wire.read();
	if ((cmd_id <= 0) || (cmd_id >= CMD_COUNT)) {
		Serial << "  wrong cmd id: " << cmd_id << '!' << NL;
		return;
	}

	len = Wire.available();
	if (len != CMD_ARGS_COUNT[cmd_id - 1]) {
		Serial << "  wrong cmd args count: " << len << '!' << NL;
		return;
	}

	cmds->id = cmd_id;
	for (uint8_t i = 0; i < len; i++)
		cmds->args[i] = Wire.read();
	Serial << "  cmd id: " << cmd_id << " parsed successfully!" << NL;
}

void i2c_on_request()
{
	uint8_t status = 0;

	Serial << "I2C request! sending axes status report: [ ";
	for (axis_t *axis = axes; axis->motor; axis++) {
		Serial << axis->status << ' ';
		status <<= 2;
		status |= axis->status;
	}
	Wire.write(status);
	Serial << ']' << NL;
}

void clone_first_cmd()
{
	for (uint8_t i = 1; i < ARDUINO_COUNT; i++)
		memcpy(cmds + i, cmds, sizeof(cmd_t));
}

void handle_set_axes_quadrant()
{
	int8_t cur_quadrant;
	int8_t target_quadrant;
	int8_t dist_quadrant;
	uint8_t rotations;
	uint16_t speed;

	for (axis_t *axis = axes; axis->motor; axis++) {
		if (axis->status)
			continue;

		speed = cmds->set_axis_args[axis->index].speed;
		if (!speed)
			continue;

		speed *= CMD_SPEED_SCALE;
		axis->motor->setMaxSpeed(speed);
		axis->motor->enableOutputs();

		cur_quadrant = (axis->motor->targetPosition() / AXIS_STEPS_PER_QUADRANT) % AXIS_QUADRANT_COUNT;
		if (cur_quadrant < 0)
			cur_quadrant += AXIS_QUADRANT_COUNT;

		rotations = cmds->set_axis_args[axis->index].rotations;
		target_quadrant = cmds->set_axis_args[axis->index].index;

		dist_quadrant = target_quadrant - cur_quadrant;
		if (dist_quadrant <= -AXIS_QUADRANT_COUNT / 2)
			dist_quadrant += AXIS_QUADRANT_COUNT;
		else if (dist_quadrant > AXIS_QUADRANT_COUNT / 2)
			dist_quadrant -= AXIS_QUADRANT_COUNT;

		Serial << "Set axis " << axis->index << " speed: " << speed <<
			" rotations: " << rotations << " target: " << target_quadrant <<
			" cur: " << cur_quadrant << " dist: " << dist_quadrant << NL;

		// TODO: add support for rotations (now only takes the shortest path)
		if (!rotations)
			axis->motor->move(axis->motor->distanceToGo() + AXIS_STEPS_PER_QUADRANT * dist_quadrant);
	}
}

void handle_cmd()
{
	if (cmds->id) {
		if (cmds->id == CMD_HOMING)
			handle_axes_homing();
		else // if (cmds->id == CMD_SET_AXES_QUADRANTS)
			handle_set_axes_quadrant();
		cmds->id = CMD_NONE;
	}
}

void send_cmds()
{
	for (uint8_t i = 1; i < ARDUINO_COUNT; i++)
		if (cmds[i].id) {
			Wire.beginTransmission(i);
			Wire.write(CMD_START);
			Wire.write((uint8_t *)(cmds + i), 1 + CMD_ARGS_COUNT[cmds[i].id - 1]);
			Wire.endTransmission();
		}
	handle_cmd();
	memset(cmds, 0, ARDUINO_COUNT * sizeof(cmd_t));
}

void axes_homing()
{
	uint32_t start_ms = millis();

	cmds->id = CMD_HOMING;
	clone_first_cmd();
	send_cmds();

	Serial << "  waiting for slaves.." << NL;
	while ((millis() - start_ms) < AXIS_HOMING_TIMEOUT_MS)
		delay(100);

	for (uint8_t i = 1, status = 0; i < ARDUINO_COUNT; i++) {
		if (Wire.requestFrom(i, (uint8_t)1)) {
			status = Wire.read();
			for (uint8_t a = 0; a < AXIS_PER_ARDUINO; a++) {
				Serial << "  axis: " << (a + i * AXIS_PER_ARDUINO) <<
					(status & 0xC0 ? " didn't made it home!" : " is home!") << NL;
				status <<= 2;
			}
		}
		else
			Serial << "  axes: " << i * AXIS_PER_ARDUINO << '-' <<
				(i + 1) * AXIS_PER_ARDUINO - 1 << " didn't respond!" << NL;
	}

	Serial << "Done homing!" << NL;
	delay(1000);
}

void set_axis_quadrant(uint8_t axis_index, uint8_t quadrant_index, int8_t rotations, uint16_t speed)
{
	cmd_t *p = cmds + axis_index / AXIS_PER_ARDUINO;

	axis_index %= AXIS_PER_ARDUINO;
	p->id = CMD_SET_AXES_QUADRANTS;
	p->set_axis_args[axis_index].index = quadrant_index;
	p->set_axis_args[axis_index].rotations = rotations;
	p->set_axis_args[axis_index].speed = speed / CMD_SPEED_SCALE;
}

void set_axes_quadrant(uint8_t quadrant_index, int8_t rotations, uint16_t speed)
{
	set_axis_quadrant(0, quadrant_index, rotations, speed);
	memcpy(cmds->set_axis_args + 1, cmds->set_axis_args,
		sizeof(*(cmds->set_axis_args)) * (AXIS_PER_ARDUINO - 1));
	clone_first_cmd();
}

void update_pattern()
{
	// TODO: add more patterns - this simple one is the first testing
	uint32_t cur_ms = millis();
	static uint32_t last_ms = 0;
	static uint8_t last_quadrant_index = 0;

	if (cur_ms - last_ms > 3000) {
		last_ms = cur_ms;
		last_quadrant_index++;
		set_axes_quadrant(last_quadrant_index, 0, AXIS_SPEED);
		send_cmds();
	}
}

void setup()
{
	delay(500);										// wait for power stabilization
	Serial.begin(SERIAL_BAUD_RATE);					// init UART for debuging
	Serial << F("Rotating Rods V1 by A.E.TECH 2022") << NL;

	arduino_id = (PIND >> 2) & 7;					// D2-D4 encodes the arduino ID
	uint8_t axes_count = arduino_id < (AXIS_TOTAL_COUNT / AXIS_PER_ARDUINO) ?
		AXIS_PER_ARDUINO : AXIS_TOTAL_COUNT % AXIS_PER_ARDUINO;
	Serial << "  arduino_id: " << arduino_id << NL << "  axes_count: " << axes_count << NL;

	axes = new axis_t[axes_count + 1];				// allocate and initialize axes
	axes[axes_count].motor = NULL;					// last axis is NULL to stop iterations

	for (uint8_t i = 0; i < axes_count; i++) {
		axis_t *axis = axes + i;
		axis->index = i;
		axis->status = AXIS_STATUS_IDLE;
		axis->motor = new AccelStepper(
			AccelStepper::DRIVER, AXIS_PUL_PIN + i * 3, AXIS_DIR_PIN + i * 3);
		axis->motor->setEnablePin(AXIS_ENA_PIN + i * 3);
		axis->motor->setPinsInverted(arduino_id & 2, arduino_id & 4, !(arduino_id & 1));
		axis->motor->setMaxSpeed(AXIS_SPEED);
		axis->motor->setAcceleration(AXIS_ACCELERATION);
		axis->motor->disableOutputs();
		pinMode(AXIS_LMT_PIN + i, INPUT_PULLUP);
	}

	if (arduino_id) {
		cmds = new cmd_t;							// cmd object for slave
		Wire.begin(arduino_id);						// init I2C as slave
		Wire.onReceive(i2c_on_receive);				// slave cmd received callback
		Wire.onRequest(i2c_on_request);				// slave status requested callback
	}
	else {
		cmds = new cmd_t[ARDUINO_COUNT];			// cmd object for master and each slave
		Wire.begin();								// init I2C as master
		delay(500);									// master wait for its slaves
		axes_homing();								// send homing cmd to all slaves and home master's axes - blocking!
	}
}

void loop()
{
	if (arduino_id)
		handle_cmd();								// slave just handles cmds (recived from i2c_on_receive)
	else
		update_pattern();							// master calls send_cmds() that sends slave cmds and handle its own cmds

	for (axis_t *axis = axes; axis->motor; axis++)
		axis->motor->run();							// TODO: add axis enable / disable control

	delay(1);
}
