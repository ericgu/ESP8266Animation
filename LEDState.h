struct LEDState
{
  public:
    String Mode;
    String RGBValues;
    int TimeInSeconds;
    int CycleCount;
    bool NewData;

    void Set(ESP8266WebServer& server)
    {
      if (server.args() > 0)
      {
        Mode = server.arg("Mode");
        RGBValues = server.arg("RGBValues");
        TimeInSeconds = server.arg("Time").toInt();
        CycleCount = server.arg("CycleCount").toInt();
        NewData = true;
      }
    }
};

