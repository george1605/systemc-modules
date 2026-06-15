#include <systemc.h>
#include <systemc>

SC_MODULE (counter) {
   sc_in_clk     clock ;      // Clock input of the design
   sc_in<bool>   reset ;      // active high, synchronous Reset input
    sc_in<bool>   enable;      // Active high enable signal for counter
    sc_out<sc_uint<4> > counter_out; // 4 bit vector output of the counter
    sc_in<sc_uint<4>> di; // 4 bit Data input
    sc_in<bool> pl; // Parallel load
    sc_uint<4>	count;


    void incr_count () {

      if (reset.read() == 1) {
        count =  0;
        counter_out.write(count);

      } else if (pl.read() == 1) {
    	  count = di.read();
    	  counter_out.write(count);
      } else if (enable.read() == 1) {
        count = count + 1;
        counter_out.write(count);
        cout << "@" << sc_time_stamp() << " :: Incremented Counter "
          << counter_out.read() << endl;
      }
    }


    SC_CTOR(counter) {
      cout << "Executing new" << endl;
      SC_METHOD(incr_count);
      sensitive << reset;
      sensitive << clock.pos();
    }

};
