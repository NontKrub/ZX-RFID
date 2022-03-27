#ifndef __ZX_RFID_H__
#define __ZX_RFID_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "kidbright32.h"
#include "esp_log.h"

class ZX_RFID : public Device {
	private:		
		enum {
			s_detect,
			s_init,
			s_recheck_connection,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;

	public:
		// constructor
		ZX_RFID() ;
		
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		bool isDetected() ;
		char* readUID() ;

		
};

#endif