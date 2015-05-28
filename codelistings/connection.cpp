for (int i = 0; i < NUMBER_OF_SAMPA_CHIPS * NUMBER_OUTPUT_PORTS_TO_GBT; i++)	//8
{
  if (i != 0 && i % GBT_NUMBER_INPUT_PORTS == 0)
  {
    gbt_number++;
    gbt_port = 0;
  }
  if (i != 0 && i % NUMBER_OUTPUT_PORTS_TO_GBT == 0)
  {
    sampa_number++;
    sampa_port = 0;
  }
  sampas[sampa_number]->porter_SAMPA_to_GBT[sampa_port++](*fifo_SAMPA_GBT[i]);
  gbts[gbt_number]->porter_SAMPA_to_GBT[gbt_port++](*fifo_SAMPA_GBT[i]);
}
