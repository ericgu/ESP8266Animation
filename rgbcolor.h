struct RGBColor
{
  public:
    RGBColor() {}
  
    RGBColor(uint8_t red, uint8_t green, uint8_t blue)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

    const char* advanceToCommaOrEnd(const char* pData)
    {
      while (0 != *pData && ',' != *pData)
      {
        pData++;
      }

      if (',' == *pData)
      {
        pData++;
      }
      return pData;
    }

    String toString()
    {
      return String(red) + "," + String(green) + "," + String(blue);
    }

    const char* createFromString(const char* pData)
    {
      red = atoi(pData);

      pData = advanceToCommaOrEnd(pData);

      if (0 == *pData)
      {
        return pData;
      }

      green = atoi(pData);

      pData = advanceToCommaOrEnd(pData);

      if (0 == *pData)
      {
        return pData;
      }

      blue = atoi(pData);

      pData = advanceToCommaOrEnd(pData);

      return pData;
    }

    uint8_t red;
    uint8_t green;
    uint8_t blue;
};
