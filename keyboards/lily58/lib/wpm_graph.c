// #include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "wpm.h"
#include "timer.h"
#include "oled_driver.h"

uint16_t timer = 0;
char wpm_text[5];
uint8_t x = 31;
uint8_t currwpm = 0;
uint8_t capped_currwpm = 0;
uint8_t vert_count = 0; 

//=============  USER CONFIG PARAMS  ===============
float max_wpm = 90.0f; //WPM value at the top of the graph window
uint8_t graph_refresh_interval = 80; //in milliseconds
uint8_t graph_area_fill_interval = 3; //determines how dense the horizontal lines under the graph line are; lower = more dense
uint8_t vert_interval = 3; //determines frequency of vertical lines under the graph line
bool vert_line = true; //determines whether to draw vertical lines
uint8_t graph_line_thickness = 3; //determines thickness of graph line in pixels
//=============  END USER PARAMS  ===============

void draw_wpm_graph(void) {
    currwpm = get_current_wpm();

    //check if it's been long enough before refreshing graph
	if(timer_elapsed(timer) > graph_refresh_interval){
		// cap the current WPM value at the max WPM value
		capped_currwpm = currwpm > max_wpm ? max_wpm : currwpm;

		// main calculation to plot graph line
		x = 32 - ((capped_currwpm / max_wpm) * 32);

		// make sure that the graph line doesn't go off the screen
		if (x < 1) { x = 1; }
		
		//first draw actual value line
		for(int i = 0; i <= graph_line_thickness - 1; i++){
			oled_write_pixel(1, x + i, true);
		}
		
		
		//then fill in area below the value line
		if(vert_line){
			if(vert_count == vert_interval){
				vert_count = 0;
				while(x <= 32){
					oled_write_pixel(1, x, true);
					x++;
				}
			} else {
				for(int i = 32; i > x; i--){
					if(i % graph_area_fill_interval == 0){
						oled_write_pixel(1, i, true);
					}
				}
				vert_count++;
			}
		} else {
			for(int i = 32; i > x; i--){
				if(i % graph_area_fill_interval == 0){
					oled_write_pixel(1, i, true);
				}
			}
		}
		
		//then move the entire graph one pixel to the right
		oled_pan(false); 
		
		//refresh the timer for the next iteration
		timer = timer_read();
    }

	//format current WPM value into a printable string
	sprintf(wpm_text,"%i", currwpm);
    	
	//formatting for triple digit WPM vs double digits, then print WPM readout
	if(currwpm >= 100){
		oled_set_cursor(14, 3);
		oled_write("WPM: ", false);
		oled_set_cursor(18, 3);
		oled_write(wpm_text, false);
	} else if (currwpm >= 10){
		oled_set_cursor(15, 3);
		oled_write("WPM: ", false);
		oled_set_cursor(19, 3);
		oled_write(wpm_text, false);
	} else if (currwpm > 0) {
		oled_set_cursor(16, 3);
		oled_write("WPM: ", false);
		oled_set_cursor(20, 3);
		oled_write(wpm_text, false);		
	}
}