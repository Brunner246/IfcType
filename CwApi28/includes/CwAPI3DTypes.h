#pragma once

#include <stdint.h>
#include <string>

namespace CwAPI3D
{
  const uint32_t versionMajor = 28; // PQ: Do not increment this number without consulting me.
  const uint32_t versionMinor = 8;

  using elementID = uint64_t;
  using materialID = uint64_t;
  using colorID = uint32_t;
  using endtypeID = uint64_t;
  using axisID = uint64_t;
  using menuIndex = int32_t;
  using referenceSide = uint32_t;
  /**
   * \brief 3D Vector
   */
  struct vector3D
  {
    /**
     * \brief X Coordinate
     */
    double mX;
    /**
     * \brief Y Coordinate
     */
    double mY;
    /**
     * \brief Z Coordinate
     */
    double mZ;
  };
  /**
   * \brief RGB Color
   */
  struct colorRGB
  {
    /**
     * \brief Red Value
     */
    uint32_t mR;
    /**
     * \brief Green Value
     */
    uint32_t mG;
    /**
     * \brief Blue Value
     */
    uint32_t mB;
  };
  using character = wchar_t;
  using narrowCharacter = char;
  using wideCharacter = wchar_t;
  using string = std::wstring;
  using narrowString = std::string;
  using wideString = std::wstring;

  enum divisionZoneDirection
  {
    positive = 1,
    negative = -1,
    none = 0
  };
}
