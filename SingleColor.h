class SingleColor: public Animation
{
  private:
    Adafruit_NeoPixel* _pStrip;
    Mapper* _pMapper;
    Pixel _pixel;
    Chunk* _pChunk;
    RGBColor _color;

  public:
    SingleColor(Adafruit_NeoPixel* pStrip, RGBColor color)
    {
        _pStrip = pStrip;
        _color = color;

        _pMapper = new Mapper(_pStrip);
        _pChunk = new Chunk(1);
        _pixel = Pixel(color);
        _pChunk->setPixel(0, _pixel);
    }

    ~SingleColor()
    {
      delete _pChunk;
      delete _pMapper;
    }

    void dimToPercentage(int percentage)
    {
      int red = (_color.red * percentage) / 100;
      int green = (_color.green * percentage) / 100;
      int blue = (_color.blue * percentage) / 100;
      
      _pixel.animateToNewColor(RGBColor(red, green, blue), 255);
    }

    virtual void update()
    {
        _pixel.update();
        _pMapper->renderAndShow(_pChunk);
    }
};

