/**
 * Main file for running the BLE samples.
 */
extern "C" {
	void app_main(void);
}

void SampleHID(void);

void app_main(void) {
	SampleHID();
} // app_main
