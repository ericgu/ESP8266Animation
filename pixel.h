
class PixelAnimator
{
  private:
    RGBColor _targetColor;
    int _steps;
    uint16_t _redDelta;
    uint16_t _greenDelta;
    uint16_t _blueDelta;
    uint16_t _red;
    uint16_t _green;
    uint16_t _blue;

  public:
    PixelAnimator(RGBColor currentColor, RGBColor targetColor, int steps)
    {
        _steps = steps;
        _targetColor = targetColor;

        _red = (uint16_t) (currentColor.red << 8);
        _green = (uint16_t) (currentColor.green << 8);
        _blue = (uint16_t) (currentColor.blue << 8);

        _redDelta = (uint16_t) (((targetColor.red - currentColor.red) << 8)/steps);
        _greenDelta = (uint16_t) (((targetColor.green - currentColor.green) << 8)/steps);
        _blueDelta = (uint16_t) (((targetColor.blue - currentColor.blue) << 8)/steps);
    }

    RGBColor getNextColor()
    {
        _steps--;
        _red = (uint16_t) (_red + _redDelta);
        _green = (uint16_t) (_green + _greenDelta);
        _blue = (uint16_t) (_blue + _blueDelta);

        return RGBColor((uint8_t) (_red >> 8), (uint8_t) (_green >> 8), (uint8_t) (_blue >> 8));
    }

    bool isDone()
    {
        return _steps == 0;
    }
};

class Pixel
{
  private:
        PixelAnimator* _pixelAnimator;
        RGBColor _color;

  public:
        Pixel()
        {
          _pixelAnimator = 0;
        }
  
        Pixel(RGBColor color)
        {
          _color = color;
          _pixelAnimator = 0;
        }

        Pixel(uint8_t r, uint8_t g, uint8_t b)
        {
          _color.red = r;
          _color.green = g;
          _color.blue = b;
          _pixelAnimator = 0;
        }

        void animateToNewColor(RGBColor newColor, int steps)
        {
            _pixelAnimator = new PixelAnimator(_color, newColor, steps);
        }

        void update()
        {
            if (_pixelAnimator)
            {
                _color = _pixelAnimator->getNextColor();

                if (_pixelAnimator->isDone())
                {
                    delete _pixelAnimator;
                    _pixelAnimator = 0;
                }
            }
        }

        bool isDone()
        {
            return _pixelAnimator == 0;
        }

        RGBColor getColor()
        {
            return _color;
        }
    };

