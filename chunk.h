class Chunk
{
  private:
    uint16_t _numPixels;
    Pixel** _pixels;
    uint16_t _offset = 0;

  public:
    Chunk(uint16_t numPixels)
    {
        _numPixels = numPixels;
        _pixels = new Pixel*[numPixels];
    }

    Chunk(String rgbCommaSeparated)
    {
      int numbers = CountCommas(rgbCommaSeparated) + 1;
      _numPixels = numbers / 3;

      _pixels = new Pixel*[_numPixels];

      const char* pRgb = rgbCommaSeparated.c_str();

      for (int i = 0; i < _numPixels; i++)
      {
        RGBColor color;
        pRgb = color.createFromString(pRgb);
        _pixels[i] = new Pixel(color);          
        Serial.println(color.toString());
      }
    }

    int CountCommas(String s)
    {
      const char* p = s.c_str();
      int commas = 0;

      while (0 != *p)
      {
        if (*p == ',')
        {
          commas++;
        }
        p++;
        
      }

      return commas;
    }      

    ~Chunk()
    {
      delete _pixels;
    }

    uint16_t numPixels()
    {
        return _numPixels;
    }

    void dump()
    {
      Serial.println(_numPixels);
      for (int i = 0; i < _numPixels; i++)
      {
        Serial.println(_pixels[i]->getColor().red);
      }
    }

    void setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
    {
        _pixels[index] = new Pixel(RGBColor(r, g, b));
    }


    void setPixel(uint16_t index, Pixel* pPixel)
    {
        _pixels[index] = pPixel;
    }

    Pixel* getPixel(int i)
    {
      return *(_pixels + i);
    }
    
    Pixel* getNextPixel()
    {
        Pixel** pPixel = _pixels + _offset;

        _offset = (_offset + 1) % _numPixels;

        return *pPixel;
    }

    void setOffset(uint16_t offset)
    {
        _offset = offset % _numPixels;
    }
};
