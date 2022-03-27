#ifndef __ZX_RFID_CPP__
#define __ZX_RFID_CPP__

#include "ZX-RFID.h"
#include "rc522.h"
#include "stdio.h"
#include "string.h"

ZX_RFID::ZX_RFID() {
	channel = 0;
	address = 0x28;
	polling_ms = 300;
}

void ZX_RFID::init(void) {
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
}

int ZX_RFID::prop_count(void) {
	// not supported
	return 0;
}

bool ZX_RFID::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool ZX_RFID::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool ZX_RFID::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool ZX_RFID::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool ZX_RFID::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

uint8_t last_uid[5];
bool detected = false;

void tag_handler(uint8_t* sn) { // serial number is always 5 bytes long
    ESP_LOGI("ZX-RFID", "Tag: %#x %#x %#x %#x %#x",
        sn[0], sn[1], sn[2], sn[3], sn[4]
    );

	memcpy(last_uid, sn, 5);
	detected = true;
}

void ZX_RFID::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// clear error flag
				error = false;
				// set initialized flag
				initialized = true;

				// Go to main state
				state = s_init;
			} else {
				state = s_error;
			}
			break;
		
		case s_init: {
			const rc522_start_args_t start_args = {
				.i2c  = i2c,
				.callback = &tag_handler,
			};

			rc522_start(start_args);

			state = s_recheck_connection;
			break;
		}

		case s_recheck_connection:
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				tickcnt = get_tickcnt();

				if (i2c->detect(channel, address) != ESP_OK) {
					rc522_destroy();

					state = s_error;
					break;
				}
			}
			break;
		
		case s_wait:
			if (error) {
				// wait polling_ms timeout
				if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
					state = s_detect;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

	}
}

// Method
bool ZX_RFID::isDetected() {
	if (detected) {
		detected = false;
		return true;
	}

	return false;
}

char* ZX_RFID::readUID() {
	static char uid_str[20];
	sprintf(uid_str, "%02X%02X%02X%02X%02X", 
		last_uid[0], last_uid[1], last_uid[2], last_uid[3], last_uid[4]
	);

	return uid_str;
}

#endif