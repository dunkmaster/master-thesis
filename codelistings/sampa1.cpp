class SAMPA : public sc_module {
public:


	//I/O Ports.
	sc_port< sc_fifo_in_if< Sample > >  inputPorts[NUMBER_OF_CHANNELS];
	sc_port< sc_fifo_out_if< Packet > > eLinks[NUMBER_OF_ELINKS];

	//4 async serial out threads
	void serialOut0(void);
	void serialOut1(void);
	void serialOut2(void);
	void serialOut3(void);

	//Routing method, serial outs read from correct buffer.
	int processData(int serialOut);

	//Thread which receives samples for every channel.
	void receiveSamples(void);

	SAMPA(sc_module_name name);

private:
	int Addr; //Hardware Address
	std::list<Sample> dataBuffers[NUMBER_OF_CHANNELS]; //Sample FIFOs
	std::list<Packet> headerBuffers[NUMBER_OF_CHANNELS]; //SAMPA Header FIFOs

};
