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
	list<Sample> dataBuffers[NUMBER_OF_CHANNELS]; //Sample FIFOs
	list<Packet> headerBuffers[NUMBER_OF_CHANNELS]; //SAMPA Header FIFOs
};

void SAMPA::receiveSamples(){
	Sample sample;
	int currentTimebin = 0;
	float waitTime = 100.0; // 10bit 10 MHz clock: 1 / 10 ^ 6 = 100 ns.
	bool overflow = false;
	while(true){
		for(int i = 0; i < NUMBER_OF_CHANNELS; i++){

			if(inputPorts[i].nb_read(sample)){
				if(dataBuffers[i].size < MAX_BUFFER_SIZE
					&& !overflow){
						dataBuffers[i].push_back(sample);
						currentTimebin++;
					} else {
						overflow = true;
					}
				}
				if(currentTimebin == MAX_NUMBER_OF_TIMEBINS){ //End of timeframe

					//Creating a header packet and adding to headerBuffer.
					Packet packet(timeFrame, i, dataBuffers.size(), overflow);
					headerBuffers[i].push_back(packet);
				}
			}
			wait(waitTime, SC_NS);
		}
	}
