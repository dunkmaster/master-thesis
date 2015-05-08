class Packet
{
public:
  //Class variables
  
  Packet(int _timeFrame, int _channelId, int _numberOfSamples, bool _overflow, int _sampleId, int _occupancy);
  Packet();

  inline friend std::ostream& operator << ( std::ostream &os,  Packet const &packet )
  {
    os << "Packet: time frame: " << packet.timeFrame << ", sampaId: " << packet.sampaChipId << ", channelId: " << packet.channelId << ", number of samples: " << packet.numberOfSamples;

    return os;
  };
  Packet& operator = (const Packet& _packet);
};
