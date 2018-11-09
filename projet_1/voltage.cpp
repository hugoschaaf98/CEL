#include "voltage.hpp"

namespace cel{

	// constructor
	voltage createVoltage(uint8_t pin_no, uint32_t t_start, uint32_t t_end, uint32_t T_high, uint32_t period){
		voltage v = {pin_no, t_start, t_end, T_high, period};
		return v
	}// end createVoltage()

	// check if the signal is overlapping
	bool checkOverlapping(uint8_t v_count, float duty_cycle, uint32_t period){

		//compute the sequence duration
		float result = (float)(v_count)*duty_cycle*(float)(period);
		if(result-period >= 0) return 0;//no overlapping
		else return 1;// overlapping
	}// end  checkOverlapping()
	
	// generate signals
	bool generateSig(voltage** v_tab, uint8_t count, uint32_t period){

		static bool first_start = 1;
		static uint8_t phase = SWITCHING;
		static uint32_t last_t_end = 0;
		static uint8_t voltage_src_no = 0;// save the current voltage source, and start with the 1st source of v_tab
		static voltage* current_v_ptr = v_tab[voltage_src_no];

		uint32_t current_time = millis();

		// if its the first start, initialize the 1 source properly
		if(first_start){
			for(uint8_t i = 0; i < count; i++){
				setTstart(v_tab[i], current_time+i*getThigh(v_tab[i]));
			}
			first_start =  0;
		}

		for(uint8_t i = 0; i < count; i++){

		}


		return 1
	}// end generateSig()

	/// mutateurs ///

	bool setPin(voltage* v, uint8_t pin_no){
		v->pin_no = pin_no;
		return 1;
	}

	bool setTstart(voltage* v, uint32_t t_start){
		v->t_start = t_start;
		return 1;
	}

	bool setTend(voltage* v, uint32_t t_end){
		v->t_end = t_end;
		return 1;
	}

	bool setThigh(voltage* v, uint32_t T_high){
		v->T_high = T_high;
		return 1;
	}

	bool setPeriod(voltage* v, uint32_t period){
		v->period = period;
		return 1;
	}

	/// accesseurs ///

	uint8_t getPin(voltage* v){
		return v->pin_no;
	}

	uint32_t getTstart(voltage* v){
		return v->t_start;
	}

	uint32_t getTend(voltage* v){
		return v->t_end;
	}

	uint32_t getThigh(voltage* v){
		return v->T_high;
	}
	uint32_t getPeriod(voltage* v);

}// namespace cel