class AllWhite
{
  public:
    static void Set(Adafruit_NeoPixel& strip)
    {
      for(int i=0; i<strip.numPixels(); i++) 
      {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
      }
    }
 
};

