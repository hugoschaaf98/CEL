#include "voltagep2.hpp"

namespace cel{

	// constructor
	voltage createVoltage(uint8_t pin_no, uint32_t period, uint32_t t_start, uint32_t t_end, uint32_t phase, bool state){
		voltage v = {t_start, t_end, period, phase, pin_no, state};
		return v;
	}// end createVoltage()
	
	// generate signals
	bool generateSig(voltage &v, uint32_t t){

		//if time is over a half period, toggle
		if( (float)(t-getTstart(v)) <= (float)(getPeriod(v))/2.){
			digitalWrite(getPin(v), LOW);
      setState(v,LOW);
		}
    else if( (float)(t-getTstart(v)) > (float)(getPeriod(v))/2. && t-getTstart(v) < getPeriod(v)){
      digitalWrite(getPin(v), HIGH);
      setState(v,HIGH);
		}
    else setTstart(v,t);
		return true;
	}// end generateSig()

	/// mutateurs ///

	bool setPin(voltage &v, uint8_t pin_no){
		v.pin_no = pin_no;
		return 1;
	}

	bool setTstart(voltage &v, uint32_t t_start){
		v.t_start = t_start;

		return 1;
	}

	bool setTend(voltage &v, uint32_t t_end){
		v.t_end = t_end;
		return 1;
	}

	bool setPeriod(voltage &v, uint32_t period){
		v.period = period;
		return 1;
	}

  bool setState(voltage &v, bool state){
    v.state = state;
    return 1;
  }

	/// accesseurs ///

	uint8_t getPin(voltage &v){
		return v.pin_no;
	}

	uint32_t getTstart(voltage &v){
		return v.t_start;
	}

	uint32_t getTend(voltage &v){
		return v.t_end;
	}

	uint32_t getPeriod(voltage &v){
		return v.period;
	}

	bool getState(voltage &v){
		return v.state;
	}

}// namespace cel
