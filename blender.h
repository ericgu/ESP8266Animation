class Blender
{
  private:
    Chunk* _pChunk;
    uint16_t _totalSize;
    uint16_t _offset = 0;

  public:
    Blender(uint16_t totalSize)
    {
        _totalSize = totalSize;

        _pChunk = new Chunk(_totalSize);
    }

    ~Blender()
    {
      if (_pChunk)
      {
        delete _pChunk;
      }
    }

    Chunk* getChunk()
    {
      Chunk* pChunk = _pChunk;
      _pChunk = 0;
      return pChunk;
    }

    Blender(RGBColor items[], int count, uint16_t steps)
    {
      _pChunk = new Chunk(count * steps);

      for (int i = 0; i < count; i++)
      {
          addBlend(items[i], items[(i + 1) % count], steps);
      }
    }

    void addBlend(RGBColor color1, RGBColor color2, uint16_t steps)
    {
        uint16_t redDelta = (uint16_t) (((color2.red - color1.red) << 8)/steps);
        uint16_t greenDelta = (uint16_t) (((color2.green - color1.green) << 8)/steps);
        uint16_t blueDelta = (uint16_t) (((color2.blue - color1.blue) << 8)/steps);

        uint16_t red = (uint16_t) (color1.red << 8);
        uint16_t green = (uint16_t) (color1.green << 8);
        uint16_t blue = (uint16_t) (color1.blue << 8);

        for (uint16_t i = _offset; i < _offset + steps; i++)
        {
            _pChunk->setPixel(i, (byte) (red >> 8), (byte) (green >> 8), (byte) (blue >> 8));
            red = (uint16_t) (red + redDelta);
            green = (uint16_t) (green + greenDelta);
            blue = (uint16_t) (blue + blueDelta);
        }

        _offset = (uint16_t) (_offset + steps);
    }
};

