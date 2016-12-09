class Rainbow: public Animation
{
  private:
    Mapper* _pMapper;
    Chunk* _pChunk;
    Animator* _pAnimator;
    
  public:
    Rainbow(Adafruit_NeoPixel* pStrip, int length, int slowness, int mirror)
    {
      _pMapper = new Mapper(pStrip);
      _pMapper->setMirror(mirror);

      RGBColor red(255, 0, 0);
      RGBColor yellow(255, 255, 0);
      RGBColor green(0, 255, 0);
      RGBColor cyan(0, 255, 255);
      RGBColor blue(0, 0, 255);
      RGBColor magenta(255, 0, 255);
    
      Blender blender(length);
      int part = length / 6;
      blender.addBlend(red, yellow, part);
      blender.addBlend(yellow, green, part);
      blender.addBlend(green, cyan, part);
      blender.addBlend(cyan, blue, part);
      blender.addBlend(blue, magenta, part);
      blender.addBlend(magenta, red, part);

      _pChunk = blender.getChunk();

      _pAnimator = new Animator(_pMapper, _pChunk);

      _pAnimator->setOffset(0, length, slowness, 1, 1);
    }

   ~Rainbow()
   {
      delete _pMapper;
      delete _pChunk;
      delete _pAnimator;
   }

    virtual void update()
    {
      _pAnimator->update();
    }
};

