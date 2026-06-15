#include <systemc.h>
#include <systemc>
#include "main.cpp"

// the testbench
int sc_main(int argc, char** argv)
{
	 sc_signal<bool>   clock;
	 sc_signal<bool>   reset;
	 sc_signal<bool>   enable;
	 sc_signal<sc_uint<4> > counter_out;
	 sc_signal<bool>   pl;
	 sc_signal<sc_uint<4>> di;

	 counter cnt("COUNTER1");
	 cnt.clock(clock);
	 cnt.reset(reset);
	 cnt.enable(enable);
	 cnt.di(di);
	 cnt.pl(pl);
	 cnt.counter_out(counter_out);

	 sc_start(1, SC_NS);
	 sc_trace_file *wf = sc_create_vcd_trace_file("counter");

	 sc_trace(wf, clock, "clock");
	 sc_trace(wf, reset, "reset");
	 sc_trace(wf, enable, "enable");
	 sc_trace(wf, pl, "parallel_load");
	 sc_trace(wf, di, "data_in");
	 sc_trace(wf, counter_out, "count");

	 reset = 0;
	 pl = 0;
	 enable = 0;

	 for(int i = 0;i < 5;i++)
	 {
		 clock = 0;
		 sc_start(1, SC_NS);
		 clock = 1;
		 sc_start(1, SC_NS);
	 }

	 reset = 0;
	 reset = 1;
	 clock = 0;
	 sc_start(1, SC_NS);
	 reset = 0;
	 clock = 1;
	 sc_start(1, SC_NS);

	 cout << "@" << sc_time_stamp() <<" De-Asserting reset\n" << endl;

	 di = 10;
	 clock = 0;
	 sc_start(1, SC_NS);
	 clock = 1;
	 sc_start(1, SC_NS);

	 sc_close_vcd_trace_file(wf);
	 return 0;
}
