/*
 *    Filename: main.c
 *     Version: 0.0.1
 * Description: Ewiger Blinker
 *     License: GPLv3 or later
 *     Depends: global.h, io.h, sleep.h, wdt.h
 *
 *      Author: Copyright (C) Patrick Kanzler
 *        Date: 2013-05-30
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *  Set the following fuses:
 *	hfuse = 0xFF
 *	lfuse = 7A
 *
 */

#include "../lib/0.1.3/global.h"
#include "../lib/0.1.3/io/io.h"
#include <avr/sleep.h>
#include <avr/wdt.h>



#define LED_DDR DDRB				// LED hängt an DDRB
#define LED_PORT PORTB				// PORT der LED
#define LED_PIN PB3				// Layout sieht PIN3 vor
#define LED(x) out(LED_PORT,LED_PIN,0,x)

void WDT_off(void)
{
	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out
	*/
	WDTCR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCR = 0x00;
}


int main(void) {
	
	WDT_off(); //watchdog erstmal abschalten
	wdt_disable();
	LED_DDR = (1<<LED_PIN); //register setzen
		
	LED(0); //LED auf LOW ziehen --> AN
	delayms(20); //Delayzeit stellt die Impulsdauer und damit den Helligkeitseindruck ein
	LED(1); //LED auf HIGH setzen --> AUS
	wdt_enable(WDTO_2S); //setze den Watchdogtimer auf 2s
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); //PWR_DOWN --> quasi nur wdt kann chip wecken
    sleep_mode(); //in den Tiefschlaf wechseln
	
	while(1);
	return 0;
}
