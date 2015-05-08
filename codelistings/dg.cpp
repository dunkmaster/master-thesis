void DataGenerator::sink_thread(void){
  if(DG_SIMULTION_TYPE == 1){
    standardSink();
  } else if(DG_SIMULTION_TYPE == 2){
    incrementingOccupancySink();
  } else if(DG_SIMULTION_TYPE == 3){
    alternatingOccupancySink();
  } else if(DG_SIMULTION_TYPE == 4){
    sendBlackEvents();
  } else {
    sendGaussianDistribution();
  }
}

void DataGenerator::standardSink(){
  //While we still have timeFrames to send
  while(currentTimeFrame <= NUMBER_TIME_FRAMES_TO_SIMULATE)
  {
    //Loop each channel
    for(int i = 0; i < NUMBER_OF_SAMPA_CHIPS * SAMPA_NUMBER_INPUT_PORTS; i++)
    {
      if(randomGenerator.generate(0, 100) <= DG_OCCUPANCY){
        //Send real sample
      } else {
        //Send empty sample
      }
    }
    currentSample++;
    //Increments timeWindow
    if(currentSample == NUMBER_OF_SAMPLES_IN_EACH_TIME_FRAME )//1021 samples
    {
      currentTimeFrame++;
      currentSample = 0;
    }
    wait((constants::DG_WAIT_TIME), SC_NS);
  }
}

//Creates the set with the distribution of occupancies.
std::vector<int> DataGenerator::getOccupancy(){

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

  double deviation = sqrt(sum/100);
  std::default_random_engine gen(seed);
  std::normal_distribution<double> dist(mean, deviation);

  //create a vector of occupancies based on the normal distribution.
  for(int i = 0; i < NUMBER_TIME_FRAMES_TO_SIMULATE; i++){
      result.push_back((int)dist(gen));
  }
  return result;
}

double DataGenerator::calcSpace(int occ){
  double numberOfSamples = (NUMBER_OF_SAMPLES_IN_EACH_TIME_FRAME * occ) / 100.0;
  double numberOfPeaks = numberOfSamples / 3.0;
  double numberOfEmptyTimebins = NUMBER_OF_SAMPLES_IN_EACH_TIME_FRAME - numberOfSamples;

  return (numberOfEmptyTimebins / numberOfPeaks);
}
