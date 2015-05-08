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

	while(true){
		for(int i = 0; i < NUMBER_OF_CHANNELS; i++){
			if(inputPorts[i].nb_read(sample)){

				if(dataBuffers[i].size < MAX_BUFFER_SIZE && !overflow){
					dataBuffers[i].push_back(sample);
					currentTimebin++;
				} else {
					overflow = true;
				}
			}
			//End of timeframe
			if(currentTimebin == MAX_NUMBER_OF_TIMEBINS){
				Packet packet(timeFrame, i, dataBuffers.size(), overflow);
				headerBuffers[i].push_back(packet);
			}
		}
		wait(waitTime, SC_NS);
	}
}
