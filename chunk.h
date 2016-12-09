class Chunk
{
  private:
    Pixel* _pixels;
    uint16_t _numPixels;
    uint16_t _offset = 0;

  public:
    Chunk(uint16_t numPixels)
    {
        _numPixels = numPixels;
        _pixels = new Pixel[numPixels];
    }

    Chunk(String rgbCommaSeparated)
    {
      int numbers = CountCommas(rgbCommaSeparated) + 1;
      _numPixels = numbers / 3;

      _pixels = new Pixel[_numPixels];

      const char* pRgb = rgbCommaSeparated.c_str();

      for (int i = 0; i < _numPixels; i++)
      {
        RGBColor color;
        pRgb = color.createFromString(pRgb);
        _pixels[i] = Pixel(color);          
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
        Serial.println(_pixels[i].getColor().red);
      }
    }

    void setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
    {
        _pixels[index] = Pixel(r, g, b);
    }

    void setPixel(uint16_t index, Pixel pixel)
    {
      if (index >= _numPixels)
      {
        Serial.print("setPixel index out of range was ");
        Serial.print(index);
        Serial.print(" max ");
        Serial.println(_numPixels);
      }
      
        _pixels[index] = pixel;
    }

    Pixel* getPixel(int i)
    {
      return _pixels + i;
    }
    
    Pixel* getNextPixel()
    {
        Pixel* pPixel = _pixels + _offset;

        _offset = (_offset + 1) % _numPixels;

        return pPixel;
    }

    void setOffset(uint16_t offset)
    {
        _offset = offset % _numPixels;
    }
};
