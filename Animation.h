class Animation
{
  public:
    Animation()
    {}

    Animation(Adafruit_NeoPixel* pStrip)
    {
      for (int i= 0; i < pStrip->numPixels(); i++)
      {
        pStrip->setPixelColor(i, 0,0,0);
      }
      pStrip->show();
    }
  
    virtual void update()
    {
      
    }
 
};

