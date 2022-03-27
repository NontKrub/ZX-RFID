Blockly.Blocks['rfid_is_detected'] = {
	init: function () {
		this.jsonInit({
			"message0": Blockly.Msg.ZX_RFID_IS_DETECTED_MESSAGE,
			"output": "Boolean",
			"colour": 135,
			"tooltip": Blockly.Msg.ZX_RFID_IS_DETECTED_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	}
};

Blockly.Blocks['rfid_read_uid'] = {
	init: function () {
		this.jsonInit({
			"message0": Blockly.Msg.ZX_RFID_READ_UID_MESSAGE,
			"output": "String",
			"colour": 135,
			"tooltip": Blockly.Msg.ZX_RFID_READ_UID_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	}
};
