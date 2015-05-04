class SAMPA : public sc_module {
public:

	//I/O Ports.
	sc_port< sc_fifo_in_if< Sample > >  inputPorts[NUMBER_OF_CHANNELS];
	sc_port< sc_fifo_out_if< Packet > > eLinks[NUMBER_OF_ELINKS];

	//Channels
	Channel *channels[SAMPA_NUMBER_INPUT_PORTS];

	//Initialize channels
	void initChannels(void);

	//4 async serial out threads
	void serialOut0(void);
	void serialOut1(void);
	void serialOut2(void);
	void serialOut3(void);

	//Routing method, serial outs read from correct buffer.
	int processData(int serialOut);
	SAMPA(sc_module_name name);

private:
	int Addr; //Hardware Address
};

void SAMPA::processData(int serialOut){

	//Go through all channels for specific serialout
	for(int i = 0; i < constants::CHANNELS_PER_E_LINK; i++){
		float waitTime = 0.0;
		//Find channel
		int channelId = i + (serialOut*constants::CHANNELS_PER_E_LINK);
		Channel *channel = channels[channelId];

		//find header
		if(!channel->headerBuffer.empty()){
			Packet header = channel->headerBuffer.front();
			channel->headerBuffer.pop();

			//Read from databuffer, but check for overflow.
			if(!header.overflow || header.numberOfSamples > 0){

				for(int j = 0; j < header.numberOfSamples; j++){
					if(!channel->dataBuffer.empty()){

						channel->dataBuffer.pop_front();
					}
				}
			}
			//Simulate number of clock cycles it took to read the timeframe.
			waitTime = (5 + header.numberOfSamples); //50bit header + 10 bit samples
			porter_SAMPA_to_GBT[serialOut]->nb_write(header);
			wait((constants::SAMPA_OUTPUT_WAIT_TIME * waitTime), SC_NS);
		}
	}
}

void SAMPA::serialOut0(){
	//1 of 4 serial out threads
	while(true){
		//wait small amount of time to create cycle.
		wait(1, SC_NS);
		processData(0); //0-3
	}
}
