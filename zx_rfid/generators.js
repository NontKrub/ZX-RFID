Blockly.JavaScript['rfid_is_detected'] = function(block) {
	var code = 'DEV_I2C1.ZX_RFID().isDetected()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['rfid_read_uid'] = function(block) {
	var code = 'DEV_I2C1.ZX_RFID().readUID()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

