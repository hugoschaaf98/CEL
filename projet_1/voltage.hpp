/* outils pour creer plusieurs tensions dephasées
 *
 * Projet CEL, S4 ENIB 2018
 * SCHAAF HUGO
 */

//
// each voltage source must be between the n°2 and n°9 pin of the arduino
//

#ifndef VOLTAGE_HPP
#define VOLTAGE_HPP

#include <cstdint>

#define SWITCHING 0
#define WAITING 1

namespace cel{

	/*** voltage type ***/
	struct voltage{

		uint8_t pin_no,
		uint32_t t_start,
		uint32_t t_end,
		uint32_t T_high,
		uint32_t period

	};

	voltage createVoltage(uint8_t pin_no, uint32_t t_start, uint32_t t_end, uint32_t T_high);
	bool checkOverlapping(uint8_t v_count, float duty_cycle, uint32_t period);
	bool generateSig(voltage** v_tab, uint8_t count);

	bool setPin(voltage *v, uint8_t pin_no);
	bool setTstart(voltage *v, uint32_t t_start);
	bool setTend(voltage* v, uint32_t t_end);
	bool setThigh(voltage *v, uint32_t T_high);

	uint8_t getPin(voltage *v);
	uint32_t getTstart(voltage *v);
	uint32_t getTend(voltage *v);
	uint32_t getThigh(voltage *v);
	uint32_t getPeriod(voltage *v);


}// namespace cel





#endif