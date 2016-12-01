class RGBColorFade: public Animation
{
  private:
    Adafruit_NeoPixel* _pStrip;
    Mapper* _pMapper;
    Chunk* _pChunk;
    Chunk* _pColors;
    int _currentColor;
    Pixel* _pPixel;

  public:
    RGBColorFade(Adafruit_NeoPixel* pStrip, String rgbValues)
    {
      _pStrip = pStrip;
      _pColors = new Chunk(rgbValues);
      _currentColor = _pColors->numPixels();
      _pPixel = new Pixel(RGBColor(0, 0, 0));
      _pChunk = new Chunk(1);
      _pChunk->setPixel(0, _pPixel);

      _pMapper = new Mapper(_pStrip);
    }

    ~RGBColorFade()
    {
      delete _pColors;
      delete _pPixel;
      delete _pMapper;
    }

  virtual void update()
  {
    _pPixel->update();
    
    if (_pPixel->isDone())
    {
      Serial.println("u");
      _currentColor = (_currentColor + 1) % _pColors->numPixels();

      RGBColor color = _pColors->getPixel(_currentColor)->getColor();
      Serial.println(color.toString());
      _pPixel->animateToNewColor(color, 1000);
    }

    _pMapper->renderAndShow(_pChunk);
  }
};

