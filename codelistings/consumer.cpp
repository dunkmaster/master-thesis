SC_HAS_PROCESS(Consumer); //macro to indicate that the Module has 1 or more processes

//Constructor with name of module as parameter
Consumer::Consumer(sc_module_name name) : sc_module(name){ 
	SC_THREAD(receiveData); //Registrer the receiveData thread
	
}

//Thread which runs until the simulation is over.
//Clock frequency: 100 Mhz; 1 / 10 ^ 7 = 10 nanoseconds.
void Consumer::receiveData(){
	
	int numberOfEvens = 0; // counts number of evens
	bool receivedSignal = false; //received signal variable
	
	while(numberOfEvens < 10){ //stop lopp when received 10 evens
		
		if(inputChannel->nb_read(receivedSignal)){ //receiving signal; nb_read returns true if signal is read.  
			if(receivedSignal){
				numberOfEvens++; // if signal is true, count was even.
			}
		}
		wait(10, SC_NS); //End of a clock cycle, wait 10 nanoseconds
	}
	sc_stop(); //Force stop simulation.
}

