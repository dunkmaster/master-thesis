//Standard sink
if(currentSample == NUMBER_OF_SAMPLES_IN_EACH_TIME_WINDOW )
{
  currentTimeWindow++;
  currentSample = 0;
}

//Increasing occupancy sink
if(currentSample == NUMBER_OF_SAMPLES_IN_EACH_TIME_WINDOW ){
  //How often do we increase the occupancy?
  if(currentTimeWindow % (NUMBER_TIME_WINDOWS_TO_SIMULATE / TIME_WINDOW_OCCUPANCY_SPLIT) == 0){
    //Increase occupancy.
    occupancy = occupancy + TIME_WINDOW_OCCUPANCY_SPLIT;
  }
  currentTimeWindow++;
  currentSample = 0;
}


//Standard sink
if(randomGenerator.generate(0, 100) <= DG_OCCUPANCY){
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
