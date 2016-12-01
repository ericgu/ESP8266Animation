class Chunky: public Animation
{
  private:
    Adafruit_NeoPixel* _pStrip;
    Mapper* _pMapper;
    Chunk* _pChunk;
    Animator* _pAnimator;
    int _chunkSize;

  public:
    Chunky(Adafruit_NeoPixel* pStrip, int colors, int chunkSize)
    {
        _pStrip = pStrip;

        _pMapper = new Mapper(_pStrip);
        _pChunk = new Chunk(colors);
        _chunkSize = chunkSize;
        _pAnimator = new Animator(_pMapper, _pChunk);
        _pAnimator->setOffset(0, pStrip->numPixels(), 3000000, 1, chunkSize);
    }

    ~Chunky()
    {
      delete _pChunk;
      delete _pMapper;
    }

    void setColor(int i, RGBColor color)
    {
      _pChunk->setPixel(i, color.red, color.green, color.blue);
    }
    
    virtual void update()
    {
        _pAnimator->update();
    }
};

