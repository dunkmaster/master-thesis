class Channel : public sc_module {
public:

	//Ports between the DataGenerator and the Channel
	sc_port< sc_fifo_in_if< Sample > > inputPort;

	//Data and Header buffers
	list<Sample> dataBuffer;
	list<Packet> headerBuffer;

  //Main SystemC Thread.
  void receiveData();
	//Getter and Setter methods
    .......
  //End
	Channel(sc_module_name name);

private:
	//Can specify which pad the channel comes from.
  int Pad;
	int PadRow;
	int Addr;
	int SampaAddr;
};

while(true){

		//Read from datagenerator
		if(port_DG_to_CHANNEL->nb_read(sample)){
			numberOfClockCycles++; //timebin

			//Check if max buffer size is reached.
			if(dataBuffer.size() + sample.size > constants::CHANNEL_DATA_BUFFER_SIZE){
				overflow = true;
			}

			//Add sample to buffer if there is no overflow.
			if(!overflow){
				numberOfSamples++;
			  addSampleToBuffer(sample, numberOfClockCycles);
			}

		}
		//When we reach the end of a timeWindow we send the header packet to its buffer and starts a new window
		if(numberOfClockCycles == constants::NUMBER_OF_SAMPLES_IN_EACH_TIME_WINDOW ){

			//Remove samples added earlier in timeframe if overflow
			if(overflow){
				for (int i = 0; i < numberOfSamples; ++i)
				{
					dataBuffer.pop_back();

				}
				numberOfSamples = 0;
			}
			//Create header packet, and add to header buffer.
			Packet header(currentTimeWindow, this->getAddr(), numberOfSamples, overflow, 1, currentOccupancy);
			header.sampaChipId = this->getSampaAddr();
			headerBuffer.push(header);
			//Clean up temp variables
		}
}
