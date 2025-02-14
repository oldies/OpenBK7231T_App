#include "../new_common.h"
#include "../new_pins.h"
#include "../new_cfg.h"
// Commands register, execution API and cmd tokenizer
#include "../cmnds/cmd_public.h"
#include "../mqtt/new_mqtt.h"
#include "../logging/logging.h"
#include "drv_local.h"
#include "drv_uart.h"
#include "../httpserver/new_http.h"
#include "../hal/hal_pins.h"


static softI2C_t g_softI2C;


void KP18058_Write(float *rgbcw) {
	bool bAllZero = false;
	int i;


	for (int i = 0; i < 5; i++) {
		if (rgbcw[i] > 0.01f) {
			bAllZero = false;
		}
	}

	if (bAllZero) {
		Soft_I2C_Start(&g_softI2C, 0x81);
		for (int i = 0; i < 13; i++) {
			Soft_I2C_WriteByte(&g_softI2C, 0x00);
		}
	}
	else {
		Soft_I2C_Start(&g_softI2C, 0xE1);
		Soft_I2C_WriteByte(&g_softI2C, 0x00);
		Soft_I2C_WriteByte(&g_softI2C, 0x03);
		Soft_I2C_WriteByte(&g_softI2C, 0x7D);
		for (int i = 0; i < 5; i++) {
			unsigned short cur_col_12 = MAP(rgbcw[g_cfg.ledRemap.ar[i]], 0, 255.0f, 0, 4095.0f);
			byte a, b;
			a = cur_col_12 & 0x3F;
			b = (cur_col_12 >> 6) & 0x3F;
			Soft_I2C_WriteByte(&g_softI2C, a);
			Soft_I2C_WriteByte(&g_softI2C, b);
		}
	}
	Soft_I2C_Stop(&g_softI2C);
}

// startDriver KP18058
// KP18058_Map 0 1 2 3 4
// KP18058_RGBCW FF00000000
void KP18058_Init() {

	g_softI2C.pin_clk = 7;
	g_softI2C.pin_data = 8;
	//g_softI2C.pin_clk = PIN_FindPinIndexForRole(IOR_KP18058_CLK, g_softI2C.pin_clk);
	//g_softI2C.pin_data = PIN_FindPinIndexForRole(IOR_KP18058_DAT, g_softI2C.pin_data);

	Soft_I2C_PreInit(&g_softI2C);

	//cmddetail:{"name":"BP5758D_RGBCW","args":"[HexColor]",
	//cmddetail:"descr":"Don't use it. It's for direct access of BP5758D driver. You don't need it because LED driver automatically calls it, so just use led_basecolor_rgb",
	//cmddetail:"fn":"BP5758D_RGBCW","file":"driver/drv_bp5758d.c","requires":"",
	//cmddetail:"examples":""}
	CMD_RegisterCommand("KP18058_RGBCW", CMD_LEDDriver_WriteRGBCW, NULL);
	//cmddetail:{"name":"SM2235_Map","args":"[Ch0][Ch1][Ch2][Ch3][Ch4]",
	//cmddetail:"descr":"Maps the RGBCW values to given indices of SM2235 channels. This is because SM2235 channels order is not the same for some devices. Some devices are using RGBCW order and some are using GBRCW, etc, etc. Example usage: SM2235_Map 0 1 2 3 4",
	//cmddetail:"fn":"SM2235_Map","file":"driver/drv_sm2235.c","requires":"",
	//cmddetail:"examples":""}
	CMD_RegisterCommand("KP18058_Map", CMD_LEDDriver_Map, NULL);
}
