int sc_main(int argc, char* argv[]) {

	Producer producer("Producer");
	Consumer consumer("Consumer");

	sc_fifo<bool> channel(20); //(First-In-First-Out) channel with depth of 20.

	//Connecting Producer-Consumer channel.
	producer.outputChannel = channel;
	consumer.inputChannel = channel;

	sc_start(); //Alternative: sc_start(30, SC_NS) - Specified simulation lenght.

	return 0;
}