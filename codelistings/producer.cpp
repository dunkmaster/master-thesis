SC_HAS_PROCESS(Producer); //macro to indicate that the module has process

//Constructor with name of module as parameter
Producer::Producer(sc_module_name name) : sc_module(name){ 
	SC_THREAD(sendData); //Registrer the sendData thread
}

//Thread which runs until the simulation is over.
//Clock frequency: 100 Mhz; 1 / 10 ^ 7 = 10 nanoseconds
void Producer::sendData(){
	
	bool signal = false; //signal value
	int count = 0; // count variable
	
	while(true){ //infinite loop
		
		if(!(count % 2)){ // if count is even, signal = true
			signal = true;
		}
		
		outputChannel->nb_write(signal); //write signal to output channel
		
		signal = false; //reset signal
		count++; //increase count
		wait(10, SC_NS); //End of a clock cycle, wait 10 nanoseconds
	}
}