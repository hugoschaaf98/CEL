/* outils pour creer plusieurs tensions dephasées
 *
 * Projet CEL, S4 ENIB 2018
 * SCHAAF HUGO
 */

#ifndef VOLTAGEP2_HPP
#define VOLTAGEP2_HPP

#include <stdint.h>
#include <Arduino.h>

namespace cel{

	/*** voltage type ***/
	struct voltage{
		uint32_t t_start;
		uint32_t t_end;
		uint32_t period;
		uint32_t phase;
		uint8_t pin_no;
		bool state;
	};

	voltage createVoltage(uint8_t pin_no, uint32_t period, uint32_t t_start = 0, uint32_t t_end = 0, uint32_t phase = 0, bool state = 0);
	bool generateSig(voltage &v, uint32_t t);

	bool setPin(voltage &v, uint8_t pin_no);
	bool setTstart(voltage &v, uint32_t tstart);
	bool setTend(voltage &v, uint32_t tend);
	bool setPeriod(voltage &v, uint32_t period);
  bool setState(voltage &v, bool state);


	uint8_t getPin(voltage &v);
	uint32_t getTstart(voltage &v);
	uint32_t getTend(voltage &v);
	uint32_t getPeriod(voltage &v);
	bool getState(voltage &v);



}// namespace cel





#endif
