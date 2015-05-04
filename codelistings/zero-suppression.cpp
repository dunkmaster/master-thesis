if(sample.data > 0 && lastSample.data > 0){
  //Sample is part of a cluster, add it to the fifo
} else if(sample.data > 0 && lastSample.data <= 0){
  //Start of new cluster. Add sample, but remove if next sample is invalid.
} else if(sample.data <= 0 && lastSample.data <= 0){
  //If sample is part of cluster meta-data add to fifo.
} else if(sample.data <= 0 && lastSample.data > 0){
  //If last sample was part of valid cluster, add current sample.
  //If not, last sample should be removed from the buffer.
}

if(sample.data > 0 && lastSample.data > 0){
  firstCluster = true; //No valid clusters found until now.
  validCluster = true; //Found valid cluster.
  zeroCount = 0; //Number of invalid samples in a row.
  addSampleToBuffer(sample, numberOfClockCycles);
} else if(sample.data > 0 && lastSample.data <= 0){
  //Count as invalid sample, but add to fifo for now.
	validCluster = false;
	zeroCount++;
	addSampleToBuffer(sample, numberOfClockCycles);
} else if(sample.data <= 0 && lastSample.data <= 0){
  //If part of cluster meta-data, add to fifo.
	if(zeroCount < 2 && firstCluster){
		addSampleToBuffer(sample, numberOfClockCycles);
	}
	zeroCount++; //Count as invalid so next zero doesn't get added.
} else if(sample.data <= 0 && lastSample.data > 0){
  if(validCluster){ //End of validCluster.
    if(zeroCount < 2 && firstCluster){
      addSampleToBuffer(sample, numberOfClockCycles);
    }
  } else {
    //Last sample was not valid, and is removed from fifo.
    removeSampleFromBuffer();
    //Add if removed sample was part of cluster meta-data.
    if(zeroCount <= 2){
      Sample newSample;
      newSample.timeFrame = sample.timeFrame;
      addSampleToBuffer(newSample, numberOfClockCycles);
    }
  }
  zeroCount++;
}
