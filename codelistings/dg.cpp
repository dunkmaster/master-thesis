void DataGenerator::sink_thread(void){
  if(constants::DG_SIMULTION_TYPE == 1){
    standardSink();
  } else if(constants::DG_SIMULTION_TYPE == 2){
    incrementingOccupancySink();
  } else if(constants::DG_SIMULTION_TYPE == 3){
    alternatingOccupancySink();
  } else if(constants::DG_SIMULTION_TYPE == 4){
    sendBlackEvents();
  } else {
    sendGaussianDistribution();
  }
}

void DataGenerator::standardSink(){
  int64_t packetCounter = 1;
  int currentSample = 0;
  int currentTimeWindow = 1;
  RandomGenerator randomGenerator;
  //While we still have timewindows to send
  while(currentTimeWindow <= constants::NUMBER_TIME_WINDOWS_TO_SIMULATE)
  {
    //Loop each channel
    for(int i = 0; i < constants::NUMBER_OF_SAMPA_CHIPS * constants::SAMPA_NUMBER_INPUT_PORTS; i++)
    {

      if(randomGenerator.generate(0, 100) <= constants::DG_OCCUPANCY){
        //Send real sample
      } else {
        //Send empty sample
      }
    }
    currentSample++;
    //Increments timeWindow
    if(currentSample == constants::NUMBER_OF_SAMPLES_IN_EACH_TIME_WINDOW )//1021 samples
    {
      currentTimeWindow++;
      currentSample = 0;
    }
    wait((constants::DG_WAIT_TIME), SC_NS);
  }
}

//Creates the set with the distribution of occupancies.
std::vector<int> DataGenerator::getOccupancy(){
  double mean = 28.0;
  double sum = 0.0;
  double array[100];

  array[0] = 74;
  for(int i = 1; i <= 10; i++){
    array[i] = 44;
  }
  //+-10 for a wider distribution.
  for(int i = 11; i < 100; i++){
    array[i] = generator.generate(mean-10, mean+10);
  }
  for(int i = 0; i < 100; i++)
    sum += pow(array[i] - mean, 2.0);

  double varians = sum/100;
  double deviation = sqrt(varians);

  std::default_random_engine gen(seed);
  std::normal_distribution<double> dist(mean, deviation);
  std::vector<int> result;

  //create a vector of occupancies based on the normal distribution.
  for(int i = 0; i < constants::NUMBER_TIME_WINDOWS_TO_SIMULATE; i++){
    int occ = (int)dist(gen);
    if(occ <= 0)
      result.push_back(1);
    else
      result.push_back(occ);
  }
  return result;
}

double DataGenerator::calcSpace(int occ){
  double numberOfSamples = (constants::NUMBER_OF_SAMPLES_IN_EACH_TIME_WINDOW * occ) / 100.0;
  double numberOfPeaks = numberOfSamples / 3.0;
  double numberOfEmptyTimebins = constants::NUMBER_OF_SAMPLES_IN_EACH_TIME_WINDOW - numberOfSamples;

  return (numberOfEmptyTimebins / numberOfPeaks);
}
