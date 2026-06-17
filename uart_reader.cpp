#include <systemc>
#include <systemc.h>

SC_MODULE(uart_reader) {
	sc_in_clk clock;
	sc_in<sc_bit> sin; // Serial In (reading 1 bit)
	sc_out<sc_bit> valid;
	sc_out<sc_bv<5>> value;

	sc_uint<4> counter; // Counter for the bit
	sc_bv<5> internal_value;

	enum state {
		STARTED, READ_DATA, PARITY, END, IDLE
	} reader_state;

	void read_data()
	{
		sc_bit zero;
		zero = "0";
		if(reader_state != STARTED && sin.read() == 0)
		{
			reader_state = STARTED;
			valid.write(zero);
		}

		if(reader_state == STARTED && counter < 5)
		{
			valid.write(zero);
			reader_state = READ_DATA;
			internal_value[counter] = sin.read();
			counter++;
		}

		if(counter == 5) {
			reader_state = PARITY;
			sc_bit x;
			x = internal_value.xor_reduce() == sin.read();
			valid.write(x);
			counter++;
		}

		if(counter == 6) {
			reader_state = END;
			sin.read();
		}

		if(reader_state == END) {
			value.write(internal_value);
			reader_state = IDLE;
		}
	}

	SC_CTOR(uart_reader) {
		reader_state = IDLE;
		SC_METHOD(read_data);
		sensitive << sin;
		sensitive << clock.pos();
	}
};
