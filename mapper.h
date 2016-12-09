class Mapper
{
private:
    Adafruit_NeoPixel* _pStrip;
    byte _mirror;

public:
    Mapper(Adafruit_NeoPixel* pStrip)
    {
        _pStrip = pStrip;
        _mirror = false;
    }

    void renderAndShow(Chunk* pChunk)
    {
      renderAndShow(pChunk, 1);
    }

    void setMirror(byte mirror)
    {
      _mirror = mirror;
    }

    void renderAndShow(Chunk* pChunk, int chunkSize)
    {
        uint16_t numPixels = _pStrip->numPixels();
        uint16_t limit = _mirror ? numPixels / 2 : numPixels;

        for (uint16_t i = 0; i < limit; i += chunkSize)
        {
            Pixel* pPixel = pChunk->getNextPixel();

            RGBColor color = pPixel->getColor();
            if (i == 0)
            {
              //Serial.println(color.red);
            }

            for (int j = 0; j < chunkSize && i + j < limit; j++)
            {
              int offset = i + j;
              _pStrip->setPixelColor(offset, color.red, color.green, color.blue);
              if (_mirror)
              {
                _pStrip->setPixelColor(numPixels - offset - 1, color.red, color.green, color.blue);
              }
            }
        }

        _pStrip->show();
    }
};

