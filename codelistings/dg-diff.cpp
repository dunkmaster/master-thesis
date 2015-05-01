//Standard sink
if(currentSample == constants::NUMBER_OF_SAMPLES_IN_EACH_TIME_WINDOW )
{
  currentTimeWindow++;
  currentSample = 0;
}

//Increasing occupancy sink
if(currentSample == constants::NUMBER_OF_SAMPLES_IN_EACH_TIME_WINDOW ){
  //How often do we increase the occupancy?
  if(currentTimeWindow % (constants::NUMBER_TIME_WINDOWS_TO_SIMULATE / constants::TIME_WINDOW_OCCUPANCY_SPLIT) == 0){
    //Increase occupancy.
    occupancy = occupancy + constants::TIME_WINDOW_OCCUPANCY_SPLIT;
  }
  currentTimeWindow++;
  currentSample = 0;
}


//Standard sink
if(randomGenerator.generate(0, 100) <= constants::DG_OCCUPANCY){
  //Send real sample
} else {
  //Send empty sample
}

//Alternating occupancy sink
if(randomGenerator.generate(0, 100) <= occupancyPoints[currentTimeWindow - 1]){
  //Send real sample
} else {
  //Send empty sample
}
