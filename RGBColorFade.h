class RGBColorFade: public Animation
{
  private:
    Adafruit_NeoPixel* _pStrip;
    Mapper* _pMapper;
    Chunk* _pChunk;
    Chunk* _pColors;
    int _currentColor;
    Pixel _pixel;

  public:
    RGBColorFade(Adafruit_NeoPixel* pStrip, String rgbValues)
    {
      _pStrip = pStrip;
      _pColors = new Chunk(rgbValues);
      _currentColor = _pColors->numPixels();
      _pixel = Pixel(RGBColor(0, 0, 0));
      _pChunk = new Chunk(1);
      _pChunk->setPixel(0, _pixel);

      _pMapper = new Mapper(_pStrip);
    }

    ~RGBColorFade()
    {
      delete _pColors;
      delete _pMapper;
    }

  virtual void update()
  {
    _pixel.update();
    
    if (_pixel.isDone())
    {
      Serial.println("u");
      _currentColor = (_currentColor + 1) % _pColors->numPixels();

      RGBColor color = _pColors->getPixel(_currentColor)->getColor();
      Serial.println(color.toString());
      _pixel.animateToNewColor(color, 1000);
    }

    _pMapper->renderAndShow(_pChunk);
  }
};

