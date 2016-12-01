#include "pixel.h"
#include "Chunk.h"
#include "mapper.h"
#include "Blender.h"

class Animator
{
  private:
  
    Mapper* _pMapper;
    Chunk* _pChunk;
    uint32_t _offsetCount;
    uint16_t _offsetMin;
    uint16_t _offsetMax;

    uint16_t _offset;
    uint32_t _offsetWait;
    uint16_t _offsetIncrement;
    uint16_t _chunkSize;

  public:
    Animator(Mapper* pMapper, Chunk* pChunk)
    {
        _pChunk = pChunk;
        _pMapper = pMapper;
    }

    void setOffset(uint16_t offsetMin, uint16_t offsetMax, uint32_t offsetCount, uint16_t offsetIncrement, uint16_t chunkSize)
    {
        _offsetIncrement = offsetIncrement;
        _offsetMax = offsetMax;
        _offsetMin = offsetMin;
        _offsetCount = offsetCount;
        _offset = _offsetMin;
        _offsetWait = _offsetCount;
        _chunkSize = chunkSize;
    }

    bool update()
    {
        if (_offsetWait == _offsetCount)
        {
            _offset += _offsetIncrement;
            if (_offset == _offsetMax)
            {
                _offset = _offsetMin;
                return false;
            }

            _pChunk->setOffset(_offset);
            _pMapper->renderAndShow(_pChunk, _chunkSize);

            _offsetWait = 0;
        }
        _offsetWait++;

        return true;
    }

    // set
    // starting offset
    // ending offset
    // number of cycles between change in offset. 
    //
    // code will drive chunk offset and tell strip to show (maybe mapper should add show). 

};
